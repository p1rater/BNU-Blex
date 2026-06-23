/*
 * config/net.h – Network stack definitions
 * Copyright (C) 2026 Blex – BOSL License
 *
 * Minimal IP/ICMP/ARP stack for the ping command.
 */

#ifndef CONFIG_NET_H
#define CONFIG_NET_H

#include <stdint.h>

/* ── Ethernet ──────────────────────────────────────────── */
#define ETH_ALEN        6
#define ETH_HTONS       0x0800   /* IPv4 */
#define ETH_HTONS_ARP   0x0806

typedef struct __attribute__((packed)) {
    uint8_t  dst[ETH_ALEN];
    uint8_t  src[ETH_ALEN];
    uint16_t type;
} eth_hdr_t;

/* ── IPv4 ──────────────────────────────────────────────── */
#define IP_PROTO_ICMP   1

typedef struct __attribute__((packed)) {
    uint8_t  ver_ihl;     /* version (4) | header length (5) */
    uint8_t  dscp_ecn;
    uint16_t total_len;
    uint16_t id;
    uint16_t flags_frag;
    uint8_t  ttl;
    uint8_t  protocol;
    uint16_t checksum;
    uint32_t src;
    uint32_t dst;
} ip_hdr_t;

/* ── ICMP ──────────────────────────────────────────────── */
#define ICMP_TYPE_ECHO_REQ      8
#define ICMP_TYPE_ECHO_REPLY    0

typedef struct __attribute__((packed)) {
    uint8_t  type;
    uint8_t  code;
    uint16_t checksum;
    uint16_t id;
    uint16_t seq;
    uint8_t  data[56];   /* typical ping payload */
} icmp_hdr_t;

/* ── ARP ───────────────────────────────────────────────── */
typedef struct __attribute__((packed)) {
    uint16_t htype;       /* 1 = Ethernet */
    uint16_t ptype;       /* 0x0800 = IPv4 */
    uint8_t  hlen;        /* 6 */
    uint8_t  plen;        /* 4 */
    uint16_t oper;        /* 1 = request, 2 = reply */
    uint8_t  sha[ETH_ALEN];
    uint32_t spa;         /* sender IP */
    uint8_t  tha[ETH_ALEN];
    uint32_t tpa;         /* target IP */
} arp_pkt_t;

/* ── Packet buffer (full MTU-sized) ────────────────────── */
#define PKT_BUF_SIZE    1518

/* ── Network configuration (hardcoded for QEMU user mode) ─ */
#define NET_MAC0   0x52
#define NET_MAC1   0x54
#define NET_MAC2   0x00
#define NET_MAC3   0x12
#define NET_MAC4   0x34
#define NET_MAC5   0x56

#define NET_IP_A   10
#define NET_IP_B   0
#define NET_IP_C   2
#define NET_IP_D   15

#define NET_GW_A   10
#define NET_GW_B   0
#define NET_GW_C   2
#define NET_GW_D   2

/* ── Helpers ───────────────────────────────────────────── */
static inline uint16_t net_htons(uint16_t v) {
    return ((v >> 8) & 0xFF) | ((v & 0xFF) << 8);
}
static inline uint32_t net_htonl(uint32_t v) {
    return ((v >> 24) & 0xFF) | ((v >> 8) & 0xFF00) |
           ((v & 0xFF00) << 8) | ((v & 0xFF) << 24);
}
static inline uint32_t ip_addr(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
    return ((uint32_t)a << 24) | ((uint32_t)b << 16) |
           ((uint32_t)c << 8)  | (uint32_t)d;
}
#define NET_OUR_IP  ip_addr(NET_IP_A, NET_IP_B, NET_IP_C, NET_IP_D)
#define NET_GW_IP   ip_addr(NET_GW_A, NET_GW_B, NET_GW_C, NET_GW_D)

/* ── API ───────────────────────────────────────────────── */
int  net_init(void);                /* init e1000 + network stack */
int  net_send_pkt(const void *data, uint32_t len);
int  net_recv_pkt(void *buf, uint32_t *len);
void net_get_mac(uint8_t mac[6]);
int  net_ping(uint32_t target_ip, int timeout_ms);

#endif /* CONFIG_NET_H */
