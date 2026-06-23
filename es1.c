/*
 * es1.c – Embed File System 1 (ES1)
 * Copyright (C) 2026 Blex – BOSL License
 *
 * Flat, in-memory filesystem for BlexOS.
 * All nodes are fixed-size records; no heap allocation needed.
 */

#include "kernel_utils.h"
#include <stdint.h>
#include <stddef.h>

/* ── Global filesystem state ─────────────────────────── */
es1_superblock_t es1_sb;
es1_node_t       es1_nodes[ES1_MAX_NODES];

/* ── String & Memory helpers ─────────────────────────── */
static int es1_streq(const char *a, const char *b) {
    int i = 0;
    while (a[i] && b[i]) { if (a[i] != b[i]) return 0; i++; }
    return (a[i] == '\0' && b[i] == '\0');
}
static void es1_strcpy(char *d, const char *s) {
    int i = 0; while (s[i]) { d[i] = s[i]; i++; } d[i] = '\0';
}
static void es1_memcpy(void *d, const void *s, uint32_t n) {
    uint8_t *dd = (uint8_t*)d;
    const uint8_t *ss = (const uint8_t*)s;
    for (uint32_t i = 0; i < n; i++) dd[i] = ss[i];
}
static void es1_memzero(void *d, uint32_t n) {
    uint8_t *dd = (uint8_t*)d;
    for (uint32_t i = 0; i < n; i++) dd[i] = 0;
}

/* ── Fonksiyon Prototipleri (Aşağıda tanımlı) ────────── */
es1_node_t *es1_alloc(const char *path, uint32_t flags);
es1_node_t *es1_find(const char *path);
int es1_write(const char *path, const char *data, uint32_t len);

/* ── Initialise the superblock — CPIO archive fills in the rest ── */
void es1_init(void) {
    es1_memzero(&es1_sb, sizeof(es1_sb));
    es1_sb.magic      = ES1_MAGIC;
    es1_sb.version    = ES1_VERSION;
    es1_sb.node_count = ES1_MAX_NODES;
    es1_sb.used_nodes = 0;
    es1_sb.total_bytes= 0;
    es1_strcpy(es1_sb.label, "BlexOS-ES1");

    es1_memzero(es1_nodes, sizeof(es1_nodes));

    /* Minimal root — all directories and files come from initramfs CPIO */
    es1_node_t *n = es1_alloc("/", ES1_FL_USED | ES1_FL_DIR);
    if (n) {
        es1_strcpy(n->owner, "root");
        es1_strcpy(n->perms, "rwxr-xr-x");
    }
}

/* ── Find a node by exact path ───────────────────────── */
es1_node_t *es1_find(const char *path) {
    for (int i = 0; i < ES1_MAX_NODES; i++) {
        if ((es1_nodes[i].flags & ES1_FL_USED) &&
             es1_streq(es1_nodes[i].path, path))
            return &es1_nodes[i];
    }
    return (es1_node_t*)0;
}

/* ── Allocate a new node ─────────────────────────────── */
es1_node_t *es1_alloc(const char *path, uint32_t flags) {
    for (int i = 0; i < ES1_MAX_NODES; i++) {
        if (!(es1_nodes[i].flags & ES1_FL_USED)) {
            es1_memzero(&es1_nodes[i], sizeof(es1_node_t));
            es1_nodes[i].flags = flags;
            es1_strcpy(es1_nodes[i].path, path);
            es1_sb.used_nodes++;
            return &es1_nodes[i];
        }
    }
    return (es1_node_t*)0;
}

/* ── Free a node by path ─────────────────────────────── */
int es1_free(const char *path) {
    es1_node_t *n = es1_find(path);
    if (!n) return -1;
    if (es1_sb.total_bytes >= n->size) es1_sb.total_bytes -= n->size;
    if (es1_sb.used_nodes > 0)         es1_sb.used_nodes--;
    es1_memzero(n, sizeof(es1_node_t));
    return 0;
}

/* ── Write data into a node ──────────────────────────── */
int es1_write(const char *path, const char *data, uint32_t len) {
    es1_node_t *n = es1_find(path);
    if (!n) return -1;
    if (n->flags & ES1_FL_DIR) return -2;
    if (len > ES1_INLINE_SIZE) len = ES1_INLINE_SIZE;
    if (es1_sb.total_bytes >= n->size) es1_sb.total_bytes -= n->size;
    es1_memcpy(n->inline_data, data, len);
    n->inline_data[len] = '\0';
    n->size = len;
    es1_sb.total_bytes += len;
    return (int)len;
}

/* ── Read data from a node ───────────────────────────── */
int es1_read(const char *path, char *buf, uint32_t bufsz) {
    es1_node_t *n = es1_find(path);
    if (!n) return -1;
    if (n->flags & ES1_FL_DIR) return -2;
    uint32_t len = n->size < bufsz ? n->size : bufsz - 1;
    es1_memcpy(buf, n->inline_data, len);
    buf[len] = '\0';
    return (int)len;
}
