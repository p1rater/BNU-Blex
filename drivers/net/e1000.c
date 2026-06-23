/*
 * config/e1000.c – Intel PRO/1000 (e1000) NIC driver
 * Copyright (C) 2026 Blex – BOSL License
 *
 * MMIO-based driver for the 82540EM Gigabit Ethernet Controller.
 * Exports the same API as the previous virtio driver so that
 * config/net.c and the ping command work unchanged.
 */

#include <stddef.h>
#include "../../kernel_utils.h"
#include "e1000.h"
#include "net.h"

e1000_t g_e1000;

/* ── PCI config read ──────────────────────────────────── */
static uint32_t pci_cfg_read(int bus, int slot, int func, int off) {
    return pci_read_config((uint8_t)bus, (uint8_t)slot, (uint8_t)func,
                           (uint8_t)off);
}

/* ── Find an e1000 on the PCI bus ─────────────────────── */
static int pci_find_e1000(void) {
    for (int bus = 0; bus < 8; bus++) {
        for (int slot = 0; slot < 32; slot++) {
            uint32_t id = pci_cfg_read(bus, slot, 0, 0);
            uint16_t vendor = id & 0xFFFF;
            uint16_t device = (id >> 16) & 0xFFFF;
            if (vendor == E1000_VENDOR && device == E1000_DEVICE) {
                g_e1000.pci_bus  = bus;
                g_e1000.pci_slot = slot;
                /* Enable bus master */
                uint16_t cmd = (uint16_t)(pci_cfg_read(bus, slot, 0, 0x04) & 0xFFFF);
                cmd |= 0x06;   /* I/O + memory space, bus master */
                uint32_t cmd32 = ((uint32_t)cmd) | (((uint32_t)pci_cfg_read(bus, slot, 0, 0x04) >> 16) << 16);
                pci_write_config((uint8_t)bus, (uint8_t)slot, 0, 0x04, cmd32);
                return 1;
            }
        }
    }
    return 0;
}

/* ── MMIO read/write helpers ──────────────────────────── */
static void e_write(uint32_t reg, uint32_t val) {
    *(volatile uint32_t*)(uintptr_t)(g_e1000.mmio_base + reg) = val;
}
static uint32_t e_read(uint32_t reg) {
    return *(volatile uint32_t*)(uintptr_t)(g_e1000.mmio_base + reg);
}

/* ── Read MAC from EEPROM ─────────────────────────────── */
static void e1000_read_mac(void) {
    /* MAC is stored in EEPROM words at offset 0-2 */
    for (int i = 0; i < 3; i++) {
        e_write(E1000_EERD, (uint32_t)((i << 8) | E1000_EERD_START));
        for (volatile int w = 0; w < 0x1000; w++) {
            if (e_read(E1000_EERD) & E1000_EERD_DONE) break;
        }
        uint16_t word = (uint16_t)((e_read(E1000_EERD) >> 16) & 0xFFFF);
        g_e1000.mac[i * 2]     = (uint8_t)(word & 0xFF);
        g_e1000.mac[i * 2 + 1] = (uint8_t)((word >> 8) & 0xFF);
    }
}

/* ══════════════════════════════════════════════════════
 *  PUBLIC: virtio_net_init (called net_init from kernel.c)
 * ══════════════════════════════════════════════════════ */
int virtio_net_init(void) {
    if (!pci_find_e1000()) return 0;

    /* BAR0 = MMIO base (lower 32 bits, mask off lower 4 bits) */
    uint32_t bar0 = pci_cfg_read(g_e1000.pci_bus, g_e1000.pci_slot, 0, 0x10);
    g_e1000.mmio_base = bar0 & ~0xF;
    g_e1000.mmio_phys = g_e1000.mmio_base;

    /* Reset the device */
    e_write(E1000_CTRL, E1000_CTRL_RST);
    for (volatile int w = 0; w < 0x10000; w++) { /* wait */ }

    /* Read MAC from EEPROM */
    e1000_read_mac();

    /* Initialise TX ring */
    for (int i = 0; i < E1000_NUM_DESC; i++) {
        g_e1000.tx_ring[i].addr   = (uint64_t)(uintptr_t)g_e1000.tx_buf[i];
        g_e1000.tx_ring[i].cmd    = 0;
        g_e1000.tx_ring[i].status = 0;
    }

    /* Initialise RX ring */
    for (int i = 0; i < E1000_NUM_DESC; i++) {
        g_e1000.rx_ring[i].addr   = (uint64_t)(uintptr_t)g_e1000.rx_buf[i];
        g_e1000.rx_ring[i].status = 0;
    }

    /* Clear multicast table */
    for (int i = 0; i < 128; i++)
        e_write(E1000_MTA + i * 4, 0);

    /* Set MAC address in the receive address filter */
    e_write(E1000_RA,
            (uint32_t)g_e1000.mac[0] |
            ((uint32_t)g_e1000.mac[1] << 8) |
            ((uint32_t)g_e1000.mac[2] << 16) |
            ((uint32_t)g_e1000.mac[3] << 24));
    e_write(E1000_RAH,
            ((uint32_t)g_e1000.mac[4]) |
            ((uint32_t)g_e1000.mac[5] << 8) |
            (1u << 31));  /* address valid */

    /* Set ring base addresses (physical addresses) */
    uint32_t rx_paddr = (uint32_t)(uintptr_t)&g_e1000.rx_ring[0];
    uint32_t tx_paddr = (uint32_t)(uintptr_t)&g_e1000.tx_ring[0];

    e_write(E1000_TDBAL, tx_paddr);
    e_write(E1000_TDBAH, 0);
    e_write(E1000_TDLEN, E1000_NUM_DESC * sizeof(e1000_tx_desc_t));

    e_write(E1000_RDBAL, rx_paddr);
    e_write(E1000_RDBAH, 0);
    e_write(E1000_RDLEN, E1000_NUM_DESC * sizeof(e1000_rx_desc_t));

    /* Ring heads = 0 */
    e_write(E1000_TDH, 0);
    e_write(E1000_TDT, 0);
    e_write(E1000_RDH, 0);

    /* RX tail = last descriptor index - 1 (all descriptors owned by device) */
    e_write(E1000_RDT, E1000_NUM_DESC - 1);
    g_e1000.rx_cur  = 0;
    g_e1000.rx_next = 0;
    g_e1000.tx_cur  = 0;

    /* Transmit control */
    e_write(E1000_TCTL, E1000_TCTL_EN | E1000_TCTL_PSP | E1000_TCTL_COLD);

    /* Receive control */
    e_write(E1000_RCTL, E1000_RCTL_EN | E1000_RCTL_UPE | E1000_RCTL_MPE |
            E1000_RCTL_BAM | E1000_RCTL_BSIZE_2048 | E1000_RCTL_SECRC);

    /* Set link up */
    uint32_t ctrl = e_read(E1000_CTRL);
    ctrl |= E1000_CTRL_SLU;
    e_write(E1000_CTRL, ctrl);

    /* Check link */
    g_e1000.link_up = (e_read(E1000_STATUS) & E1000_STATUS_LU) ? 1 : 0;

    return 1;
}

/* ══════════════════════════════════════════════════════
 *  PUBLIC: virtio_net_send
 * ══════════════════════════════════════════════════════ */
int virtio_net_send(const void *data, uint32_t len) {
    if (len > E1000_BUF_SIZE) return -1;

    uint16_t cur = g_e1000.tx_cur;

    /* Copy data into TX buffer */
    uint8_t *buf = g_e1000.tx_buf[cur];
    for (uint32_t i = 0; i < len; i++)
        buf[i] = ((const uint8_t*)data)[i];

    /* Set up the descriptor */
    g_e1000.tx_ring[cur].addr   = (uint64_t)(uintptr_t)buf;
    g_e1000.tx_ring[cur].length = (uint16_t)len;
    g_e1000.tx_ring[cur].cmd    = E1000_TXD_CMD_EOP | E1000_TXD_CMD_IFCS | E1000_TXD_CMD_RS;
    g_e1000.tx_ring[cur].status = 0;
    __asm__ volatile("mfence" ::: "memory");

    /* Advance the tail to trigger transmission */
    g_e1000.tx_cur = (uint16_t)((cur + 1) % E1000_NUM_DESC);
    e_write(E1000_TDT, g_e1000.tx_cur);

    return (int)len;
}

/* ══════════════════════════════════════════════════════
 *  PUBLIC: virtio_net_wait_tx_done
 * ══════════════════════════════════════════════════════ */
void virtio_net_wait_tx_done(void) {
    /* Spin until the TX head catches up to our last submitted descriptor */
    for (volatile int wait = 0; wait < 0xFFFFFF; wait++) {
        uint16_t tdh = (uint16_t)(e_read(E1000_TDH) & 0xFFFF);
        if (tdh == g_e1000.tx_cur) return;
    }
}

/* ══════════════════════════════════════════════════════
 *  PUBLIC: virtio_net_recv
 * ══════════════════════════════════════════════════════ */
int virtio_net_recv(void *buf, uint32_t *len) {
    uint16_t next = g_e1000.rx_next;

    /* Check if the next descriptor is done */
    __asm__ volatile("mfence" ::: "memory");
    if (!(g_e1000.rx_ring[next].status & E1000_RXD_ST_DD))
        return 0;

    uint16_t pkt_len = g_e1000.rx_ring[next].length;
    if (pkt_len > 0 && pkt_len <= *len) {
        uint8_t *src = g_e1000.rx_buf[next];
        for (uint32_t i = 0; i < pkt_len && i < *len; i++)
            ((uint8_t*)buf)[i] = src[i];
    }
    if (len) *len = pkt_len;

    /* Give the descriptor back to the device.
     * RDT must point to the LAST descriptor available to the device.
     * Since we're returning descriptor `next`, write RDT = next. */
    g_e1000.rx_ring[next].status = 0;
    __asm__ volatile("mfence" ::: "memory");

    g_e1000.rx_next = (uint16_t)((next + 1) % E1000_NUM_DESC);
    e_write(E1000_RDT, next);

    return (int)pkt_len;
}

/* ══════════════════════════════════════════════════════
 *  PUBLIC: net_get_mac
 * ══════════════════════════════════════════════════════ */
void net_get_mac(uint8_t mac[6]) {
    for (int i = 0; i < 6; i++) mac[i] = g_e1000.mac[i];
}
