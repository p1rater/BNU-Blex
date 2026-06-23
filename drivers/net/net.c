/*
 * config/net.c – Network stack (IP + ICMP + ping)
 * Copyright (C) 2026 Blex – BOSL License
 *
 * Sits on top of virtio_net.  Provides net_ping() for the ping command.
 * ARP is skipped — QEMU user-mode gateway MAC is known statically.
 */

#include "../../kernel_utils.h"
#include "net.h"
#include "e1000.h"

/* ── Freestanding memset ────────────────────────────────── */
static void* k_memset(void *s, int c, uint32_t n) {
    uint8_t *p = (uint8_t*)s;
    for (uint32_t i = 0; i < n; i++) p[i] = (uint8_t)c;
    return s;
}
#define memset k_memset

/* ── Checksum (RFC 1071) ───────────────────────────────── */
static uint16_t net_checksum(const void *data, int len) {
    uint32_t sum = 0;
    const uint16_t *p = (const uint16_t*)data;
    for (int i = 0; i < len / 2; i++) sum += p[i];
    if (len & 1) sum += (uint16_t)((const uint8_t*)data)[len - 1];
    while (sum >> 16) sum = (sum & 0xFFFF) + (sum >> 16);
    return (uint16_t)~sum;
}

/* ── Get gateway MAC (QEMU user-mode default) ──────────── */
static void get_gw_mac(uint8_t mac[6]) {
    /* QEMU user-mode NAT always uses 52:54:00:12:34:56 on the gateway */
    mac[0] = 0x52; mac[1] = 0x54; mac[2] = 0x00;
    mac[3] = 0x12; mac[4] = 0x34; mac[5] = 0x56;
}

/* ══════════════════════════════════════════════════════
 *  PUBLIC: net_ping
 * ══════════════════════════════════════════════════════ */
int net_ping(uint32_t target_ip, int timeout_ms) {
    (void)timeout_ms;

    uint8_t gw_mac[ETH_ALEN];
    get_gw_mac(gw_mac);

    uint8_t pkt[PKT_BUF_SIZE];
    memset(pkt, 0, sizeof(pkt));

    /* ── Ethernet header ────────────────────────────── */
    eth_hdr_t *eth = (eth_hdr_t*)pkt;
    for (int i = 0; i < ETH_ALEN; i++) eth->dst[i] = gw_mac[i];
    net_get_mac(eth->src);
    eth->type = net_htons(ETH_HTONS);

    /* ── IP header ──────────────────────────────────── */
    ip_hdr_t *ip = (ip_hdr_t*)(pkt + sizeof(eth_hdr_t));
    ip->ver_ihl    = 0x45;
    ip->dscp_ecn   = 0;
    ip->total_len  = net_htons(20 + 8 + 56);
    ip->id         = net_htons(1);
    ip->flags_frag = 0;
    ip->ttl        = 64;
    ip->protocol   = IP_PROTO_ICMP;
    ip->src        = NET_OUR_IP;
    ip->dst        = target_ip;
    ip->checksum   = 0;
    ip->checksum   = net_checksum(ip, 20);

    /* ── ICMP echo request ──────────────────────────── */
    icmp_hdr_t *icmp = (icmp_hdr_t*)(pkt + sizeof(eth_hdr_t) + 20);
    icmp->type     = ICMP_TYPE_ECHO_REQ;
    icmp->code     = 0;
    icmp->id       = net_htons(0xBEEF);
    icmp->seq      = net_htons(1);
    for (int i = 0; i < 56; i++) icmp->data[i] = (uint8_t)i;
    icmp->checksum = 0;
    icmp->checksum = net_checksum(icmp, 8 + 56);

    uint32_t pkt_len = sizeof(eth_hdr_t) + 20 + 8 + 56;

    /* ── Send ────────────────────────────────────────── */
    int r = virtio_net_send(pkt, pkt_len);
    if (r < 0) return -1;

    /* Wait for TX to complete */
    virtio_net_wait_tx_done();

    /* ── Wait for ICMP echo reply ─────────────────────── */
    for (volatile int wait = 0; wait < 0x300000; wait++) {
        uint32_t recv_len = PKT_BUF_SIZE;
        r = virtio_net_recv(pkt, &recv_len);
        if (r <= 0) continue;
        if (recv_len < sizeof(eth_hdr_t) + 20 + 8) continue;

        eth = (eth_hdr_t*)pkt;
        if (net_htons(eth->type) != ETH_HTONS) continue;

        ip = (ip_hdr_t*)(pkt + sizeof(eth_hdr_t));
        if (ip->protocol != IP_PROTO_ICMP) continue;
        if (ip->src != target_ip) continue;

        icmp = (icmp_hdr_t*)(pkt + sizeof(eth_hdr_t) + 20);
        if (icmp->type == ICMP_TYPE_ECHO_REPLY &&
            icmp->id   == net_htons(0xBEEF)) {
            return 0;
        }
    }
    return -2;
}

/* ══════════════════════════════════════════════════════
 *  PUBLIC: net_init
 * ══════════════════════════════════════════════════════ */
int net_init(void) {
    return virtio_net_init();
}

/* ══════════════════════════════════════════════════════
 *  PUBLIC: net_send_pkt / net_recv_pkt
 * ══════════════════════════════════════════════════════ */
int net_send_pkt(const void *data, uint32_t len) {
    return virtio_net_send(data, len);
}

int net_recv_pkt(void *buf, uint32_t *len) {
    return virtio_net_recv(buf, len);
}
