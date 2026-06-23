/*
 * config/cpio.c – CPIO newc archive parser implementation
 * Copyright (C) 2026 Blex – BOSL License
 *
 * Implements the functions declared in config/cpio.h.
 * ES1 creation helpers (es1_alloc, es1_write) are declared in kernel_utils.h.
 */

#include "cpio.h"
#include "../kernel_utils.h"
#include "../config/system.h"   /* bootlog_ok, bootlog_warn references */

/* ── String helpers (freestanding, no libc) ─────────────── */
static int cpio_strcmp(const char *a, const char *b) {
    while (*a && *b && *a == *b) { a++; b++; }
    return (unsigned char)*a - (unsigned char)*b;
}

static int cpio_strncmp(const char *a, const char *b, int n) {
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) return (unsigned char)a[i] - (unsigned char)b[i];
        if (a[i] == '\0') break;
    }
    return 0;
}

static void cpio_strcpy(char *d, const char *s) {
    int i = 0; while (s[i]) { d[i] = s[i]; i++; } d[i] = '\0';
}

static int cpio_strlen(const char *s) {
    int i = 0; while (s[i]) i++; return i;
}

static void cpio_memcpy(void *d, const void *s, uint32_t n) {
    uint8_t *dd = (uint8_t*)d;
    const uint8_t *ss = (const uint8_t*)s;
    for (uint32_t i = 0; i < n; i++) dd[i] = ss[i];
}

static void cpio_memzero(void *d, uint32_t n) {
    uint8_t *dd = (uint8_t*)d;
    for (uint32_t i = 0; i < n; i++) dd[i] = 0;
}

/* ── Hex parser (from CPIO ASCII-encoded header fields) ── */
static uint32_t parse_hex(const char *s, int len) {
    uint32_t val = 0;
    for (int i = 0; i < len; i++) {
        char c = s[i];
        val <<= 4;
        if      (c >= '0' && c <= '9') val += (uint32_t)(c - '0');
        else if (c >= 'A' && c <= 'F') val += (uint32_t)(c - 'A' + 10);
        else if (c >= 'a' && c <= 'f') val += (uint32_t)(c - 'a' + 10);
    }
    return val;
}

/* ── Normalise CPIO entry name (strip ./ and leading /) ── */
static const char* cpio_normalise_name(const char *raw) {
    const char *n = raw;
#if CPIO_STRIP_DOT_SLASH
    if (n[0] == '.' && n[1] == '/') n += 2;
#endif
#if CPIO_STRIP_LEADING_SLASH
    if (n[0] == '/') n += 1;
#endif
    return n;
}

/* ── Build an ES1 absolute path from a normalised CPIO name ──
 *  CPIO paths like "fonts/JetBrainsMono.ttf" become
 *  "/fonts/JetBrainsMono.ttf".  `buf` must be at least
 *  128 bytes. */
static void cpio_to_es1_path(char *buf, const char *normal) {
    buf[0] = '/';
    if (normal[0] == '\0') {
        buf[1] = '\0';
    } else {
        int i = 0;
        while (normal[i] && i < 125) {
            buf[i + 1] = normal[i];
            i++;
        }
        buf[i + 1] = '\0';
    }
}

/* ── Walk to next CPIO entry (header + name + data, 4-byte aligned) ── */
static const char* cpio_next(const char *ptr) {
    struct cpio_newc_header *h = (struct cpio_newc_header*)ptr;
    uint32_t namesize = parse_hex(h->namesize, 8);
    uint32_t filesize = parse_hex(h->filesize, 8);

    /* Name + header padding to 4 bytes */
    uint32_t off = sizeof(struct cpio_newc_header) + namesize;
    off = (off + 3) & ~3u;

    /* Data padded to 4 bytes */
    off += filesize;
    off  = (off + 3) & ~3u;

    return ptr + off;
}

/* ══════════════════════════════════════════════════════
 *  PUBLIC: cpio_find_file
 * ══════════════════════════════════════════════════════ */
uint8_t* cpio_find_file(const char *archive, const char *filename,
                        uint32_t *out_size) {
    const char *ptr = archive;

    while (1) {
        struct cpio_newc_header *head = (struct cpio_newc_header*)ptr;
        if (cpio_strncmp(head->magic, "070701", 6) != 0) break;

        uint32_t filesize = parse_hex(head->filesize, 8);
        uint32_t namesize = parse_hex(head->namesize, 8);

        const char *name = ptr + sizeof(struct cpio_newc_header);
        const char *normal = cpio_normalise_name(name);

        /* TRAILER marks the end */
        if (cpio_strncmp(normal, "TRAILER!!!", 10) == 0) break;

        if (cpio_strcmp(normal, filename) == 0) {
            uint32_t offset = sizeof(struct cpio_newc_header) + namesize;
            offset = (offset + 3) & ~3u;
            *out_size = filesize;
            return (uint8_t*)ptr + offset;
        }

        ptr = cpio_next(ptr);
    }
    return 0;
}

/* ══════════════════════════════════════════════════════
 *  PUBLIC: cpio_extract_one
 * ══════════════════════════════════════════════════════ */
int cpio_extract_one(const char *archive, const char *cpio_name,
                     const char *es1_path) {
    uint32_t size;
    uint8_t *data = cpio_find_file(archive, cpio_name, &size);
    if (!data) return 0;

    /* Ensure the target directory exists */
    es1_node_t *parent = es1_find(es1_path);

    /* If node doesn't exist yet, touch it */
    if (!parent) {
        es1_node_t *n = es1_alloc(es1_path, ES1_FL_USED);
        if (!n) return -1;
        cpio_strcpy(n->owner, "root");
        cpio_strcpy(n->perms, "rw-r--r--");
    }

    /* Write the extracted data */
    int r = es1_write(es1_path, (const char*)data, size);
    return (r >= 0) ? 1 : -1;
}

/* ══════════════════════════════════════════════════════
 *  PUBLIC: cpio_extract_all
 *
 *  Walks the entire CPIO archive and creates an ES1 node
 *  for each regular file.  Directories are created as needed.
 * ══════════════════════════════════════════════════════ */
int cpio_extract_all(const char *archive) {
    if (!archive) return -1;

    const char *ptr = archive;
    int count = 0;

    /* First pass: check magic */
    struct cpio_newc_header *first = (struct cpio_newc_header*)ptr;
    if (cpio_strncmp(first->magic, "070701", 6) != 0) return -1;

    while (1) {
        struct cpio_newc_header *head = (struct cpio_newc_header*)ptr;
        if (cpio_strncmp(head->magic, "070701", 6) != 0) break;

        uint32_t mode   = parse_hex(head->mode, 8);
        uint32_t filesize = parse_hex(head->filesize, 8);
        uint32_t namesize = parse_hex(head->namesize, 8);

        const char *name = ptr + sizeof(struct cpio_newc_header);
        const char *normal = cpio_normalise_name(name);

        if (cpio_strncmp(normal, "TRAILER!!!", 10) == 0) break;

        /* Build absolute ES1 path (add leading /) */
        char es1_path[128];
        cpio_to_es1_path(es1_path, normal);

        /* Data offset */
        uint32_t data_off = sizeof(struct cpio_newc_header) + namesize;
        data_off = (data_off + 3) & ~3u;
        const char *data = ptr + data_off;

        /* Determine if this is a directory (S_IFDIR = 040000) */
        int is_dir = ((mode >> 12) & 0xF) == 4; /* S_IFDIR */
        int is_reg = ((mode >> 12) & 0xF) == 8 ||  /* S_IFREG */
                     ((mode >> 12) & 0xF) == 10;    /* S_IFLNK regular-ish */

        if (is_dir || (is_reg && filesize == 0)) {
            /* Create the directory node */
            if (!es1_find(es1_path)) {
                es1_node_t *n = es1_alloc(es1_path, ES1_FL_USED | ES1_FL_DIR);
                if (n) {
                    cpio_strcpy(n->owner, "root");
                    cpio_strcpy(n->perms, "rwxr-xr-x");
                }
            }
        } else if (is_reg && filesize > 0) {
            /* Point the ES1 node directly at the CPIO memory (no copying) */
            es1_node_t *n = es1_find(es1_path);
            if (!n) {
                n = es1_alloc(es1_path, ES1_FL_USED | ES1_FL_EXTDATA);
                if (n) {
                    cpio_strcpy(n->owner, "root");
                    cpio_strcpy(n->perms, "rw-r--r--");
                }
            } else {
                /* Node exists (e.g. from ES1 init dirs); flag it as external */
                n->flags |= ES1_FL_EXTDATA;
            }
            if (n) {
                n->ext_data = (uint32_t)(uintptr_t)data;
                n->ext_size = filesize;
                n->size     = filesize;
                es1_sb.total_bytes += filesize;
            }
            count++;
        }

        ptr = cpio_next(ptr);
    }

    return count;
}
