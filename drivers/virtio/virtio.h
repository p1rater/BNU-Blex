/*
 * config/virtio.h – Virtio-PCI definitions (modern / transitional)
 * Copyright (C) 2026 Blex – BOSL License
 *
 * Supports transitional virtio-pci (common fallback) and modern
 * virtio-pci with PCI capabilities.  Implements virtqueue handling.
 */

#ifndef CONFIG_VIRTIO_H
#define CONFIG_VIRTIO_H

#include <stdint.h>

/* ── PCI vendor/device IDs ─────────────────────────────── */
#define VIRTIO_PCI_VENDOR   0x1AF4
#define VIRTIO_PCI_NET      0x1041   /* transitional virtio-net */

/* ── Virtio-PCI capability IDs (PCI Express Extended) ──── */
#define VIRTIO_PCI_CAP_COMMON       1
#define VIRTIO_PCI_CAP_NOTIFY       2
#define VIRTIO_PCI_CAP_ISR          3
#define VIRTIO_PCI_CAP_DEVICE       4
#define VIRTIO_PCI_CAP_PCI_CFG      5

/* ── Legacy I/O port offsets (transitional fallback) ──── */
#define VIRTIO_LEGACY_DEVICE_FEATURES   0x00
#define VIRTIO_LEGACY_GUEST_FEATURES    0x04
#define VIRTIO_LEGACY_QUEUE_ADDR        0x08
#define VIRTIO_LEGACY_QUEUE_SIZE        0x0C
#define VIRTIO_LEGACY_QUEUE_SEL         0x0E
#define VIRTIO_LEGACY_QUEUE_NOTIFY      0x10
#define VIRTIO_LEGACY_DEVICE_STATUS     0x12
#define VIRTIO_LEGACY_ISR               0x13
#define VIRTIO_LEGACY_DEVICE_CONFIG     0x14

/* ── Virtio device status flags ────────────────────────── */
#define VIRTIO_STATUS_ACK        1
#define VIRTIO_STATUS_DRIVER     2
#define VIRTIO_STATUS_DRIVER_OK  4
#define VIRTIO_STATUS_FEATURES_OK  8

/* ── Virtio-net feature bits ───────────────────────────── */
#define VIRTIO_NET_F_MAC         (1u << 5)
#define VIRTIO_NET_F_STATUS      (1u << 16)

/* ── Virtqueue descriptor flags ────────────────────────── */
#define VRING_DESC_F_NEXT        1
#define VRING_DESC_F_WRITE       2

/* ── Virtqueue used element flags ──────────────────────── */
#define VRING_USED_F_NO_NOTIFY   1

/* ── Virtio-net header (device-writable prefix) ────────── */
typedef struct __attribute__((packed)) {
    uint8_t  flags;
    uint8_t  gso_type;
    uint16_t hdr_len;
    uint16_t gso_size;
    uint16_t csum_start;
    uint16_t csum_offset;
    uint16_t num_buffers;
} virtio_net_hdr_t;

/* ── Virtqueue descriptor ──────────────────────────────── */
typedef struct __attribute__((packed)) {
    uint64_t addr;
    uint32_t len;
    uint16_t flags;
    uint16_t next;
} vring_desc_t;

/* ── Virtqueue available ring ──────────────────────────── */
typedef struct __attribute__((packed)) {
    uint16_t flags;
    uint16_t idx;
    uint16_t ring[];
} vring_avail_t;

/* ── Virtqueue used element ────────────────────────────── */
typedef struct __attribute__((packed)) {
    uint32_t id;
    uint32_t len;
} vring_used_elem_t;

/* ── Virtqueue used ring ────────────────────────────────── */
typedef struct __attribute__((packed)) {
    uint16_t flags;
    uint16_t idx;
    vring_used_elem_t ring[];
} vring_used_t;

/* ── Virtqueue ─────────────────────────────────────────── */
#define VIRTQ_MAX_DESC   256   /* must match device's queue size */
#define VIRTQ_DESC_SZ    16
#define VIRTQ_AVAIL_SZ(N) (2 + 2 + (N)*2 + 2)
#define VIRTQ_USED_SZ(N) (2 + 2 + (N)*8 + 2)
#define VIRTQ_RING_ALIGN 4096

/* Flat ring memory layout (legacy virtio):
 *   [0..N*16)         desc table
 *   [N*16 .. avail_end)  avail ring (flags+idx+ring[N]+used_event)
 *   [used_off .. end)     used ring (page-aligned after avail)
 *
 * Must be big enough for VIRTQ_MAX_DESC (worst case).
 */
#define VIRTQ_AVAIL_END(N)  ((uint32_t)(N)*VIRTQ_DESC_SZ + VIRTQ_AVAIL_SZ(N))
#define VIRTQ_USED_OFF(N)   (((VIRTQ_AVAIL_END(N) + (VIRTQ_RING_ALIGN-1)) & ~(VIRTQ_RING_ALIGN-1)))
#define VIRTQ_RING_SIZE_MAX  (VIRTQ_USED_OFF(VIRTQ_MAX_DESC) + VIRTQ_USED_SZ(VIRTQ_MAX_DESC))

#define VIRTQ_PKT_SIZE   2048

typedef struct {
    /* Contiguous ring memory (written to Queue Address register) */
    uint8_t ring_mem[VIRTQ_RING_SIZE_MAX] __attribute__((aligned(VIRTQ_RING_ALIGN)));

    /* Convenience pointers into ring_mem (set at init time) */
    vring_desc_t      *desc;        /* points into ring_mem */
    volatile uint16_t *avail_flags; /* points into ring_mem */
    volatile uint16_t *avail_idx;
    uint16_t          *avail_ring;
    volatile uint16_t *used_flags;
    volatile uint16_t *used_idx;
    vring_used_elem_t *used_ring;

    /* Driver state */
    uint16_t          queue_size;    /* actual size from device */
    uint16_t          free_head;
    uint16_t          last_used_idx;
    int                num_free;

    /* Packet buffers (for data, not part of ring) */
    uint8_t pkt_buf[VIRTQ_MAX_DESC][VIRTQ_PKT_SIZE]
                            __attribute__((aligned(4096)));
} virtqueue_t;

/* ── Virtio device state ───────────────────────────────── */
typedef struct {
    /* PCI location */
    int      pci_bus;
    int      pci_slot;

    /* Capability BARs (from PCI capabilities) */
    uint32_t common_bar_base;    /* I/O or MMIO base for common cfg */
    uint32_t notify_bar_base;
    uint32_t isr_bar_base;
    uint32_t device_bar_base;
    int      common_is_io;       /* 1 = legacy I/O, 0 = modern MMIO */
    uint32_t notify_off_multiplier;

    /* Device info */
    uint8_t  mac[6];
    int      link_up;

    /* Queues */
    virtqueue_t rx_vq;
    virtqueue_t tx_vq;
} virtio_net_t;

extern virtio_net_t g_virtio_net;

/* ── API ───────────────────────────────────────────────── */
int  virtio_net_init(void);
int  virtio_net_send(const void *data, uint32_t len);
int  virtio_net_recv(void *buf, uint32_t *len);
void virtio_net_wait_tx_done(void);

#endif /* CONFIG_VIRTIO_H */
