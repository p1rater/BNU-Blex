/*
 * config/e1000.h – Intel PRO/1000 (e1000) NIC driver
 * Copyright (C) 2026 Blex – BOSL License
 *
 * Replaces virtio-net-pci.  Same API (net_init / net_get_mac /
 * net_send_pkt / net_recv_pkt) used by config/net.c.
 */

#ifndef CONFIG_E1000_H
#define CONFIG_E1000_H

#include <stdint.h>

/* ── PCI vendor/device ────────────────────────────────── */
#define E1000_VENDOR    0x8086   /* Intel */
#define E1000_DEVICE    0x100E   /* 82540EM Gigabit */

/* ── MMIO register offsets ────────────────────────────── */
#define E1000_CTRL       0x0000
#define E1000_STATUS     0x0008
#define E1000_EECD       0x0010
#define E1000_EERD       0x0014
#define E1000_ICR        0x00C0
#define E1000_IMS        0x00D0
#define E1000_RCTL       0x0100
#define E1000_TCTL       0x0400
#define E1000_RDBAL      0x2800
#define E1000_RDBAH      0x2804
#define E1000_RDLEN      0x2808
#define E1000_RDH        0x2810
#define E1000_RDT        0x2818
#define E1000_TDBAL      0x3800
#define E1000_TDBAH      0x3804
#define E1000_TDLEN      0x3808
#define E1000_TDH        0x3810
#define E1000_TDT        0x3818
#define E1000_MTA        0x5200
#define E1000_RA         0x5400   /* receive address (MAC) low 4 bytes */
#define E1000_RAH        0x5404   /* receive address high 2 bytes + flags */

/* ── CTRL bits ────────────────────────────────────────── */
#define E1000_CTRL_FD     (1u << 0)  /* full duplex */
#define E1000_CTRL_ASDE   (1u << 5)  /* auto-speed detection */
#define E1000_CTRL_SLU    (1u << 6)  /* set link up */
#define E1000_CTRL_RST    (1u << 26) /* reset */

/* ── STATUS bits ──────────────────────────────────────── */
#define E1000_STATUS_LU  (1u << 1)   /* link up */

/* ── RCTL bits ────────────────────────────────────────── */
#define E1000_RCTL_EN     (1u << 1)  /* receiver enable */
#define E1000_RCTL_SBP    (1u << 2)  /* store bad packets */
#define E1000_RCTL_UPE    (1u << 3)  /* unicast promiscuous */
#define E1000_RCTL_MPE    (1u << 4)  /* multicast promiscuous */
#define E1000_RCTL_BAM    (1u << 15) /* broadcast accept */
#define E1000_RCTL_BSIZE_2048 (0 << 16) /* buffer size 2048 */
#define E1000_RCTL_BSIZE_1024 (2 << 16) /* buffer size 1024 */
#define E1000_RCTL_BSIZE_512  (1 << 16) /* buffer size 512 */
#define E1000_RCTL_SECRC  (1u << 26) /* strip CRC */

/* ── TCTL bits ────────────────────────────────────────── */
#define E1000_TCTL_EN     (1u << 1)  /* transmitter enable */
#define E1000_TCTL_PSP    (1u << 3)  /* pad short packets */
#define E1000_TCTL_COLD   (0x40 << 12) /* collision distance */

/* ── EERD bits (read from EEPROM) ─────────────────────── */
#define E1000_EERD_START  (1u << 0)
#define E1000_EERD_DONE   (1u << 4)

/* ── Transmit descriptor (legacy 16-byte) ─────────────── */
typedef struct __attribute__((packed)) {
    uint64_t addr;       /* buffer physical address */
    uint16_t length;
    uint8_t  cso;        /* checksum offset */
    uint8_t  cmd;        /* command */
    uint8_t  status;
    uint8_t  css;        /* checksum start */
    uint16_t special;
} e1000_tx_desc_t;

/* TX command bits */
#define E1000_TXD_CMD_EOP  (1u << 0)  /* end of packet */
#define E1000_TXD_CMD_IFCS (1u << 1)  /* insert FCS (CRC) */
#define E1000_TXD_CMD_RS   (1u << 3)  /* report status */

/* TX status bits */
#define E1000_TXD_ST_DD    (1u << 0)  /* descriptor done */

/* ── Receive descriptor (legacy 16-byte) ──────────────── */
typedef struct __attribute__((packed)) {
    uint64_t addr;       /* buffer physical address */
    uint16_t length;
    uint16_t csum;       /* packet checksum */
    uint8_t  status;
    uint8_t  errors;
    uint16_t special;
} e1000_rx_desc_t;

/* RX status bits */
#define E1000_RXD_ST_DD    (1u << 0)  /* descriptor done */
#define E1000_RXD_ST_EOP   (1u << 1)  /* end of packet */

/* ── Ring constants ───────────────────────────────────── */
#define E1000_NUM_DESC   64
#define E1000_BUF_SIZE   2048

/* ── Driver state ─────────────────────────────────────── */
typedef struct {
    /* PCI location */
    int      pci_bus;
    int      pci_slot;

    /* MMIO base from BAR0 */
    uint32_t mmio_base;
    uint32_t mmio_phys;   /* physical address for dma_map */

    /* Rings (physically contiguous in our static struct) */
    e1000_tx_desc_t tx_ring[E1000_NUM_DESC] __attribute__((aligned(16)));
    e1000_rx_desc_t rx_ring[E1000_NUM_DESC] __attribute__((aligned(16)));

    uint8_t tx_buf[E1000_NUM_DESC][E1000_BUF_SIZE] __attribute__((aligned(16)));
    uint8_t rx_buf[E1000_NUM_DESC][E1000_BUF_SIZE] __attribute__((aligned(16)));

    /* Ring indices */
    uint16_t tx_cur;     /* next free TX descriptor */
    uint16_t rx_cur;     /* next RX descriptor to give to device */
    uint16_t rx_next;    /* next RX descriptor to consume */

    /* MAC */
    uint8_t  mac[6];
    int      link_up;
} e1000_t;

extern e1000_t g_e1000;

/* ── API (same signatures as virtio driver) ───────────── */
void net_get_mac(uint8_t mac[6]);
int  virtio_net_init(void);    /* name kept for net.c compat */
int  virtio_net_send(const void *data, uint32_t len);
int  virtio_net_recv(void *buf, uint32_t *len);
void virtio_net_wait_tx_done(void);

#endif /* CONFIG_E1000_H */
