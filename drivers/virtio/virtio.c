/*
 * config/virtio.c – Virtio-PCI net driver
 * Copyright (C) 2026 Blex – BOSL License
 *
 * Detects a virtio-net-pci device on the PCI bus, sets up
 * transmit and receive virtqueues, and implements raw packet
 * send/receive.
 */

#include <stddef.h>
#include "../../kernel_utils.h"
#include "virtio.h"
#include "../net/net.h"

virtio_net_t g_virtio_net;

/* ── PCI config read wrapper ───────────────────────────── */
static uint32_t pci_cfg_read(int bus, int slot, int func, int off) {
    return pci_read_config((uint8_t)bus, (uint8_t)slot, (uint8_t)func,
                           (uint8_t)off);
}

/* ── Find a virtio-net PCI device ──────────────────────── */
static int pci_find_virtio_net(void) {
    for (int bus = 0; bus < 8; bus++) {
        for (int slot = 0; slot < 32; slot++) {
            uint32_t id = pci_cfg_read(bus, slot, 0, 0);
            uint16_t vendor = id & 0xFFFF;
            uint16_t device = (id >> 16) & 0xFFFF;
            if (vendor == VIRTIO_PCI_VENDOR && device == VIRTIO_PCI_NET) {
                g_virtio_net.pci_bus  = bus;
                g_virtio_net.pci_slot = slot;
                return 1;
            }
        }
    }
    return 0;
}

/* ── I/O register helpers (legacy virtio-pci via port I/O) ── */
#define LEGACY_IO_BASE  g_virtio_net.common_bar_base

static void vp_write32(int off, uint32_t val) { outl((uint16_t)(LEGACY_IO_BASE + off), val); }
static uint32_t vp_read32(int off) { return inl((uint16_t)(LEGACY_IO_BASE + off)); }
static void vp_write16(int off, uint16_t val) { outw((uint16_t)(LEGACY_IO_BASE + off), val); }
static uint16_t vp_read16(int off) {
    return (uint16_t)inb((uint16_t)(LEGACY_IO_BASE + off)) |
           ((uint16_t)inb((uint16_t)(LEGACY_IO_BASE + off + 1)) << 8);
}
static void vp_write8(int off, uint8_t val) { outb((uint16_t)(LEGACY_IO_BASE + off), val); }
static uint8_t vp_read8(int off) { return inb((uint16_t)(LEGACY_IO_BASE + off)); }

/* ── Device reset ──────────────────────────────────────── */
static void vp_reset(void)     { vp_write8(VIRTIO_LEGACY_DEVICE_STATUS, 0); }
static void vp_set_status(uint8_t s) { vp_write8(VIRTIO_LEGACY_DEVICE_STATUS, s); }
static uint8_t vp_get_status(void) { return vp_read8(VIRTIO_LEGACY_DEVICE_STATUS); }

/* ══════════════════════════════════════════════════════
 *  Virtqueue helpers
 * ══════════════════════════════════════════════════════ */

/* Initialise a virtqueue's ring memory and set up pointers.
 * ring_addr is written to the Queue Address register. */
static void vq_init(virtqueue_t *vq) {
    uint16_t n = vq->queue_size;
    if (n == 0 || n > VIRTQ_MAX_DESC) n = VIRTQ_MAX_DESC;

    /* Pointers into ring_mem:
     *   desc:    offset 0
     *   avail:   offset n * 16  (2-byte aligned naturally)
     *   used:    page-align after avail section */
    uint32_t avail_off = (uint32_t)n * VIRTQ_DESC_SZ;
    uint32_t avail_end = avail_off + VIRTQ_AVAIL_SZ(n);
    uint32_t used_off  = (avail_end + (VIRTQ_RING_ALIGN - 1)) & ~(VIRTQ_RING_ALIGN - 1);

    vq->desc        = (vring_desc_t*)&vq->ring_mem[0];
    vq->avail_flags = (uint16_t*)&vq->ring_mem[avail_off];
    vq->avail_idx   = (uint16_t*)&vq->ring_mem[avail_off + 2];
    vq->avail_ring  = (uint16_t*)&vq->ring_mem[avail_off + 4];
    vq->used_flags  = (uint16_t*)&vq->ring_mem[used_off];
    vq->used_idx    = (uint16_t*)&vq->ring_mem[used_off + 2];
    vq->used_ring   = (vring_used_elem_t*)&vq->ring_mem[used_off + 4];

    /* Zero the ring memory */
    for (uint32_t i = 0; i < sizeof(vq->ring_mem); i++)
        vq->ring_mem[i] = 0;

    /* Link descriptors into a free chain */
    vq->free_head     = 0;
    vq->last_used_idx = 0;
    vq->num_free      = (int)n;

    for (int i = 0; i < (int)n - 1; i++) {
        vq->desc[i].addr  = 0;
        vq->desc[i].len   = 0;
        vq->desc[i].flags = VRING_DESC_F_NEXT;
        vq->desc[i].next  = (uint16_t)(i + 1);
    }
    vq->desc[n - 1].addr  = 0;
    vq->desc[n - 1].len   = 0;
    vq->desc[n - 1].flags = 0;  /* end of chain */
    vq->desc[n - 1].next  = 0;
}

/* Allocate a descriptor chain. Returns first index or -1. */
static int vq_alloc_desc(virtqueue_t *vq, int count) {
    if (count <= 0 || count > vq->num_free) return -1;
    int head = (int)vq->free_head;
    int cur  = head;
    for (int i = 0; i < count - 1; i++)
        cur = (int)vq->desc[cur].next;
    vq->free_head = vq->desc[cur].next;
    vq->desc[cur].flags &= ~VRING_DESC_F_NEXT;
    vq->num_free -= count;
    return head;
}

/* Free a descriptor chain */
static void vq_free_desc(virtqueue_t *vq, int head) {
    int cur = head;
    int count = 1;
    while (vq->desc[cur].flags & VRING_DESC_F_NEXT) {
        cur = (int)vq->desc[cur].next;
        count++;
    }
    vq->desc[cur].next = vq->free_head;
    vq->free_head = (uint16_t)head;
    vq->num_free += count;
}

/* Submit to available ring */
static void vq_submit(virtqueue_t *vq, int head) {
    int idx = (int)(*vq->avail_idx & 0xFFFF);
    vq->avail_ring[idx % VIRTQ_MAX_DESC] = (uint16_t)head;
    __asm__ volatile("mfence" ::: "memory");
    (*vq->avail_idx)++;
}

/* Get completed buffer from used ring. Returns desc id or -1. */
static int vq_get_used(virtqueue_t *vq, uint32_t *len) {
    __asm__ volatile("mfence" ::: "memory");
    if (vq->last_used_idx == *vq->used_idx) return -1;
    int i = vq->last_used_idx % VIRTQ_MAX_DESC;
    int id = (int)vq->used_ring[i].id;
    if (len) *len = vq->used_ring[i].len;
    vq->last_used_idx++;
    return id;
}

/* ══════════════════════════════════════════════════════
 *  Virtio-PCI setup
 * ══════════════════════════════════════════════════════ */

static uint16_t vp_setup_queue(int qid, virtqueue_t *vq) {
    /* Select queue */
    vp_write16(VIRTIO_LEGACY_QUEUE_SEL, (uint16_t)qid);
    uint16_t qsz = vp_read16(VIRTIO_LEGACY_QUEUE_SIZE);
    if (qsz == 0) return 0;

    vq->queue_size = (qsz > VIRTQ_MAX_DESC) ? VIRTQ_MAX_DESC : qsz;
    vq_init(vq);

    /* Give the device the physical address of the ring memory */
    uint32_t paddr = (uint32_t)(uintptr_t)&vq->ring_mem[0];
    vp_write32(VIRTIO_LEGACY_QUEUE_ADDR, paddr);

    return vq->queue_size;
}

static void vp_notify_queue(int qid) {
    vp_write16(VIRTIO_LEGACY_QUEUE_NOTIFY, (uint16_t)qid);
}

static uint8_t vp_isr_status(void) {
    return vp_read8(VIRTIO_LEGACY_ISR);
}

static void vp_read_mac(void) {
    for (int i = 0; i < 6; i++)
        g_virtio_net.mac[i] = vp_read8(VIRTIO_LEGACY_DEVICE_CONFIG + i);
}

static int vp_link_status(void) {
    uint16_t st = vp_read16(VIRTIO_LEGACY_DEVICE_CONFIG + 0x10);
    return (st & 1) ? 1 : 0;
}

/* ══════════════════════════════════════════════════════
 *  PUBLIC: virtio_net_init
 * ══════════════════════════════════════════════════════ */
int virtio_net_init(void) {
    if (!pci_find_virtio_net()) return 0;

    /* BAR0 = legacy I/O base */
    uint32_t bar0 = pci_cfg_read(g_virtio_net.pci_bus, g_virtio_net.pci_slot,
                                  0, 0x10);
    if ((bar0 & 1) == 0) return 0;
    g_virtio_net.common_bar_base = bar0 & ~0x3;

    vp_reset();
    vp_set_status(VIRTIO_STATUS_ACK);
    vp_set_status(VIRTIO_STATUS_ACK | VIRTIO_STATUS_DRIVER);

    /* Negotiate features */
    uint32_t features = vp_read32(VIRTIO_LEGACY_DEVICE_FEATURES);
    uint32_t guest_features = features & (VIRTIO_NET_F_MAC | VIRTIO_NET_F_STATUS);
    vp_write32(VIRTIO_LEGACY_GUEST_FEATURES, guest_features);
    vp_set_status(VIRTIO_STATUS_ACK | VIRTIO_STATUS_DRIVER |
                  VIRTIO_STATUS_FEATURES_OK);

    vp_read_mac();

    /* Set up RX and TX queues */
    uint16_t rx_sz = vp_setup_queue(0, &g_virtio_net.rx_vq);
    uint16_t tx_sz = vp_setup_queue(1, &g_virtio_net.tx_vq);
    if (rx_sz == 0 || tx_sz == 0) { vp_reset(); return 0; }

    /* Pre-allocate RX buffers */
    for (int i = 0; i < (int)rx_sz; i++) {
        int h = vq_alloc_desc(&g_virtio_net.rx_vq, 1);
        if (h < 0) break;
        g_virtio_net.rx_vq.desc[h].addr  = (uint64_t)(uintptr_t)
            g_virtio_net.rx_vq.pkt_buf[i];
        g_virtio_net.rx_vq.desc[h].len   = VIRTQ_PKT_SIZE;
        g_virtio_net.rx_vq.desc[h].flags = VRING_DESC_F_WRITE;
        vq_submit(&g_virtio_net.rx_vq, h);
    }
    vp_notify_queue(0);

    vp_set_status(VIRTIO_STATUS_ACK | VIRTIO_STATUS_DRIVER |
                  VIRTIO_STATUS_FEATURES_OK | VIRTIO_STATUS_DRIVER_OK);

    g_virtio_net.link_up = vp_link_status();
    return 1;
}

/* ══════════════════════════════════════════════════════
 *  PUBLIC: virtio_net_send
 * ══════════════════════════════════════════════════════ */
int virtio_net_send(const void *data, uint32_t len) {
    if (len > VIRTQ_PKT_SIZE - sizeof(virtio_net_hdr_t)) return -1;

    int h = vq_alloc_desc(&g_virtio_net.tx_vq, 1);
    if (h < 0) return -2;

    uint8_t *buf = g_virtio_net.tx_vq.pkt_buf[0];
    virtio_net_hdr_t *vhdr = (virtio_net_hdr_t*)buf;
    vhdr->flags = 0; vhdr->gso_type = 0; vhdr->hdr_len = 0;
    vhdr->gso_size = 0; vhdr->csum_start = 0;
    vhdr->csum_offset = 0; vhdr->num_buffers = 0;

    uint32_t payload_len = len;
    if (payload_len > VIRTQ_PKT_SIZE - sizeof(virtio_net_hdr_t))
        payload_len = VIRTQ_PKT_SIZE - sizeof(virtio_net_hdr_t);
    for (uint32_t i = 0; i < payload_len; i++)
        buf[sizeof(virtio_net_hdr_t) + i] = ((const uint8_t*)data)[i];

    g_virtio_net.tx_vq.desc[h].addr  = (uint64_t)(uintptr_t)buf;
    g_virtio_net.tx_vq.desc[h].len   = sizeof(virtio_net_hdr_t) + payload_len;
    g_virtio_net.tx_vq.desc[h].flags = 0;

    vq_submit(&g_virtio_net.tx_vq, h);
    vp_notify_queue(1);
    return (int)payload_len;
}

/* ══════════════════════════════════════════════════════
 *  PUBLIC: virtio_net_recv
 * ══════════════════════════════════════════════════════ */
int virtio_net_recv(void *buf, uint32_t *len) {
    (void)vp_isr_status();

    uint32_t used_len;
    int id = vq_get_used(&g_virtio_net.rx_vq, &used_len);
    if (id < 0) return 0;

    uint32_t payload = (used_len > sizeof(virtio_net_hdr_t))
                       ? used_len - sizeof(virtio_net_hdr_t) : 0;
    uint8_t *src = g_virtio_net.rx_vq.pkt_buf[id];
    for (uint32_t i = 0; i < payload && i < *len; i++)
        ((uint8_t*)buf)[i] = src[sizeof(virtio_net_hdr_t) + i];

    if (len) *len = payload;

    /* Recycle descriptor */
    g_virtio_net.rx_vq.desc[id].addr  = (uint64_t)(uintptr_t)
        g_virtio_net.rx_vq.pkt_buf[id];
    g_virtio_net.rx_vq.desc[id].len   = VIRTQ_PKT_SIZE;
    g_virtio_net.rx_vq.desc[id].flags = VRING_DESC_F_WRITE;
    vq_submit(&g_virtio_net.rx_vq, id);
    vp_notify_queue(0);
    return (int)payload;
}

/* ══════════════════════════════════════════════════════
 *  PUBLIC: virtio_net_wait_tx_done
 * ══════════════════════════════════════════════════════ */
void virtio_net_wait_tx_done(void) {
    for (volatile int wait = 0; wait < 0xFFFFFF; wait++) {
        int id = vq_get_used(&g_virtio_net.tx_vq, NULL);
        if (id >= 0) {
            vq_free_desc(&g_virtio_net.tx_vq, id);
            return;
        }
    }
}

/* ══════════════════════════════════════════════════════
 *  PUBLIC: net_get_mac
 * ══════════════════════════════════════════════════════ */
void net_get_mac(uint8_t mac[6]) {
    for (int i = 0; i < 6; i++) mac[i] = g_virtio_net.mac[i];
}
