/*
 * config/initramfs.c – Initramfs boot-time setup
 * Copyright (C) 2026 Blex – BOSL License
 *
 * Orchestrates:
 *   1. Multiboot2 module detection
 *   2. CPIO archive extraction into ES1
 *   3. Dynamic font loading (TTF from CPIO)
 *
 * Replaces the ad-hoc initramfs/font logic that was formerly
 * scattered across kernel.c and es1.c.
 */

#include "../kernel_utils.h"
#include "initramfs.h"
#include "cpio.h"
#include "../config/system.h"
#include "../fonts/ttf_render.h"

/* ══════════════════════════════════════════════════════
 *  INITRAMFS MODULE ADDRESSES
 *  (filled in by detect_initramfs, used by cpio)
 * ══════════════════════════════════════════════════════ */
uint32_t initramfs_mod_start = 0;
uint32_t initramfs_mod_end   = 0;

/* ── String helpers ────────────────────────────────────── */
static int ifs_strlen(const char *s) { int i=0; while(s[i]) i++; return i; }
static int ifs_strncmp(const char *a, const char *b, int n) {
    for (int i=0; i<n; i++) { if (a[i]!=b[i]) return (unsigned char)a[i]-(unsigned char)b[i]; if (a[i]=='\0') break; } return 0;
}
static void ifs_strcpy(char *d, const char *s) { int i=0; while(s[i]) { d[i]=s[i]; i++; } d[i]='\0'; }
static char* ifs_strstr(const char *haystack, const char *needle) {
    if (!*needle) return (char*)haystack;
    int nl = ifs_strlen(needle);
    for (; *haystack; haystack++) {
        if (ifs_strncmp(haystack, needle, nl) == 0) return (char*)haystack;
    }
    return 0;
}
static void ifs_strcat(char *dest, const char *src) {
    while (*dest) dest++;
    while ((*dest++ = *src++));
}

/* ── Output is handled by print_str → putchar → fb + serial ── */

/* ══════════════════════════════════════════════════════
 *  MULTIBOOT2 TAG WALKER
 * ══════════════════════════════════════════════════════ */

#define MB2_MAGIC_EXPECTED 0x36D76289u

typedef struct { uint32_t type; uint32_t size; } mb2_tag_t;
typedef struct {
    uint32_t type;
    uint32_t size;
    uint32_t mod_start;
    uint32_t mod_end;
    char     cmdline[];
} mb2_module_tag_t;

static void detect_initramfs(uint32_t mb2_magic, void* mb2_info) {
    if (mb2_magic != MB2_MAGIC_EXPECTED) {
        print_str("[initramfs] no Multiboot2 module\n");
        return;
    }
    uint8_t *p     = (uint8_t*)mb2_info + 8;
    uint32_t total = *(uint32_t*)mb2_info;
    uint8_t *end   = (uint8_t*)mb2_info + total;

    int found = 0;
    while (p < end) {
        mb2_tag_t *tag = (mb2_tag_t*)p;
        if (tag->type == 0) break;
        if (tag->type == 3) {
            mb2_module_tag_t *mt = (mb2_module_tag_t*)p;
            initramfs_mod_start = mt->mod_start;
            initramfs_mod_end   = mt->mod_end;
            print_str("[initramfs] module mapped\n");
            found++;
        }
        uint32_t aligned = (tag->size + 7) & ~7u;
        p += aligned;
    }
    if (!found) print_str("[initramfs] no module\n");
}

/* ══════════════════════════════════════════════════════
 *  DYNAMIC FONT LOADING
 * ══════════════════════════════════════════════════════ */

static void load_dynamic_font(void) {
    if (initramfs_mod_start == 0) {
        return;
    }

    const char *archive = (const char*)(uintptr_t)initramfs_mod_start;

    /* Read font.cfg to determine which TTF to load */
    uint32_t cfg_size = 0;
    char *cfg_data = (char*)cpio_find_file(archive, "fonts/font.cfg", &cfg_size);

    char font_name[64] = SYS_FALLBACK_FONT_NAME;

    if (cfg_data && cfg_size > 0) {
        char *line = ifs_strstr(cfg_data, "FONT=");
        if (line) {
            line += 5;
            int i = 0;
            while (line[i] != '\n' && line[i] != '\r' && line[i] != '\0' && i < 63) {
                font_name[i] = line[i];
                i++;
            }
            font_name[i] = '\0';
        }
    }

    /* Load the TTF font data */
    uint32_t font_size = 0;
    char font_path[128] = SYS_FONT_DIR;
    ifs_strcat(font_path, font_name);

    uint8_t *font_data = cpio_find_file(archive, font_path, &font_size);

    if (font_data && font_size > 0) {
        print_str("[initramfs] loading font\n");
        ttf_init(font_data, font_size);
        ttf_set_size(SYS_FONT_DEFAULT_SIZE);
        print_str("[initramfs] font loaded\n");
    } else {
        print_str("[initramfs] font fallback\n");
    }
}

/* ══════════════════════════════════════════════════════
 *  PUBLIC: initramfs_setup
 * ══════════════════════════════════════════════════════ */

void initramfs_setup(uint32_t mb2_magic, void *mb2_info) {
    /* 1. Locate the initramfs module from Multiboot2 tags */
    detect_initramfs(mb2_magic, mb2_info);

    /* 2. Extract every file from the CPIO archive into ES1 */
    if (initramfs_mod_start != 0) {
        const char *archive = (const char*)(uintptr_t)initramfs_mod_start;
        int n = cpio_extract_all(archive);
        if (n > 0) {
            print_str("[initramfs] extracted\n");
        } else if (n == 0) {
            print_str("[initramfs] empty archive\n");
        } else {
            print_str("[initramfs] bad CPIO\n");
        }
    } else {
        print_str("[initramfs] no data\n");
    }

    /* 3. Load the dynamic font (needs CPIO data before ES1 font path) */
    load_dynamic_font();
}
