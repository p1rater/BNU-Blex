/*
 * logo_display.c – Boot logo (PPM) display + log level system
 * Copyright (C) 2026 Blex – BOSL License
 *
 * Displays /drivers/video/logo/logo_blex_clut224.ppm at boot time,
 * with boot logs streaming below the logo area.
 * Log levels are configurable via /etc/log.cfg in initramfs.
 */

#include "logo_display.h"
#include "../kernel_utils.h"
#include "fb/fb.h"
#include <stdint.h>

/* ── Log level names ─────────────────────────────────── */
const char *log_level_names[9] = {
    "EMERG", "ALERT", "CRIT", "ERR",
    "WARN", "NOTICE", "INFO", "DEBUG", "TRACE"
};

/* ── Defaults (overridden by log_init_from_cfg) ──────── */
int current_log_level  = LOG_INFO;   /* show INFO and above by default */
int log_to_serial      = 1;
int show_boot_logo     = 1;
int logo_duration_secs = 3;

/* ── Parse a decimal integer from a string ───────────── */
static int parse_int(const char *s) {
    int val = 0;
    while (*s >= '0' && *s <= '9') {
        val = val * 10 + (*s - '0');
        s++;
    }
    return val;
}

/* ── Check if line starts with prefix ────────────────── */
static int starts_with(const char *s, const char *prefix) {
    while (*prefix) {
        if (*s != *prefix) return 0;
        s++; prefix++;
    }
    return 1;
}

/* ── Skip whitespace ─────────────────────────────────── */
static const char* skip_ws(const char *s) {
    while (*s == ' ' || *s == '\t') s++;
    return s;
}

/* ── Read log.cfg from ES1 filesystem ────────────────── */
void log_init_from_cfg(void) {
    es1_node_t *node = es1_find("/etc/log.cfg");
    if (!node || (node->flags & ES1_FL_DIR)) {
        /* No config file — use defaults */
        return;
    }

    const char *data = es1_get_data(node);
    uint32_t sz = node->size;
    const char *p = data;
    const char *end = data + sz;

    while (p < end) {
        const char *line_start = p;
        while (p < end && *p != '\n') p++;
        const char *line_end = p;
        if (p < end && *p == '\n') p++;

        int line_len = (int)(line_end - line_start);
        if (line_len == 0) continue;

        char buf[64];
        int copy_len = (line_len < 63) ? line_len : 63;
        for (int i = 0; i < copy_len; i++) buf[i] = line_start[i];
        buf[copy_len] = '\0';

        const char *s = skip_ws(buf);
        if (s[0] == '#' || s[0] == '\0') continue;

        if (starts_with(s, "LOG_LEVEL=")) {
            const char *val = skip_ws(s + 10);
            current_log_level = parse_int(val);
            if (current_log_level < 0) current_log_level = 0;
            if (current_log_level > 8) current_log_level = 8;
        }
        else if (starts_with(s, "LOG_SERIAL=")) {
            const char *val = skip_ws(s + 11);
            log_to_serial = parse_int(val) ? 1 : 0;
        }
        else if (starts_with(s, "BOOT_LOGO=")) {
            const char *val = skip_ws(s + 10);
            show_boot_logo = parse_int(val) ? 1 : 0;
        }
        else if (starts_with(s, "LOGO_DURATION=")) {
            const char *val = skip_ws(s + 14);
            logo_duration_secs = parse_int(val);
            if (logo_duration_secs < 0) logo_duration_secs = 0;
            if (logo_duration_secs > 30) logo_duration_secs = 30;
        }
    }
}

/* ── Boot log message with level filtering ───────────── */
void boot_log(int level, const char *tag, const char *msg) {
    if (level > current_log_level) return;

    /* Save to dmesg ring buffer */
    dmesg_write(tag, msg);

    /* Choose colour based on level */
    uint32_t col;
    switch (level) {
        case LOG_EMERG:
        case LOG_ALERT:
        case LOG_CRIT:
        case LOG_ERR:    col = PAL_RED;    break;
        case LOG_WARN:   col = PAL_YELLOW; break;
        case LOG_NOTICE: col = PAL_CYAN;   break;
        case LOG_DEBUG:
        case LOG_TRACE:  col = COL_TEXT_DIM; break;
        default:         col = PAL_GREEN;  break;
    }

    tty_print_color("[", PAL_GREEN);
    tty_print_color(tag, col);
    tty_print_color("] ", PAL_GREEN);
    tty_print_color(msg, COL_TEXT_FG);
}

void boot_log_fmt(int level, const char *tag, const char *fmt, int val) {
    if (level > current_log_level) return;
    boot_log(level, tag, fmt);
    /* print_int doesn't support concatenation, so we just pass as part of message */
}

/* ── DMESG ring buffer ─────────────────────────────── */
char dmesg_buffer[DMESG_BUF_LINES][128];
int  dmesg_count = 0;

void dmesg_write(const char *tag, const char *msg) {
    int idx = dmesg_count % DMESG_BUF_LINES;
    int p = 0;
    if (tag) {
        while (*tag && p < 120) {
            dmesg_buffer[idx][p++] = *tag;
            tag++;
        }
        dmesg_buffer[idx][p++] = ':';
        dmesg_buffer[idx][p++] = ' ';
    }
    if (msg) {
        while (*msg && p < 126) {
            dmesg_buffer[idx][p++] = *msg;
            msg++;
        }
    }
    /* Strip trailing newline for cleaner dmesg output */
    while (p > 0 && (dmesg_buffer[idx][p-1] == '\n' || dmesg_buffer[idx][p-1] == '\r'))
        p--;
    dmesg_buffer[idx][p] = '\0';
    dmesg_count++;
}

/* ══════════════════════════════════════════════════════
 *  PPM IMAGE DISPLAY
 *
 *  Displays a PPM (P6 binary) image on the framebuffer at
 *  a fixed position near the top of the screen.
 *  P3 ASCII format PPMs are converted to P6 at build time.
 * ══════════════════════════════════════════════════════ */

/* Known path to logo file */
#define LOGO_PPM_PATH "/drivers/video/logo/logo_blex_clut224.ppm"

/* ── Fast PPM header parser ─────────────────────────── */
/* Reads an integer from the PPM header (ASCII decimal).  */
static int ppm_read_int(const char **p, const char *end) {
    /* Skip whitespace & comments */
    while (*p < end) {
        if (**p == '#') {
            while (*p < end && **p != '\n') (*p)++;
            if (*p < end) (*p)++;
            continue;
        }
        if (**p == ' ' || **p == '\t' || **p == '\n' || **p == '\r')
            (*p)++;
        else
            break;
    }
    if (*p >= end || **p < '0' || **p > '9') return -1;
    int val = 0;
    while (*p < end && **p >= '0' && **p <= '9') {
        val = val * 10 + (**p - '0');
        (*p)++;
    }
    return val;
}

/* ── Main PPM display function ──────────────────────── */
int logo_display_ppm(void) {
    if (!show_boot_logo) return 0;

    /* Find the PPM file in the initramfs CPIO via ES1 */
    es1_node_t *node = es1_find(LOGO_PPM_PATH);
    if (!node || (node->flags & ES1_FL_DIR)) return -1;

    const char *data = es1_get_data(node);
    uint32_t size = node->size;
    if (!data || size < 20) return -2;

    const char *p = data;
    const char *end = data + size;

    /* Parse PPM header */
    if (end - p < 2 || p[0] != 'P') return -3;
    int is_binary = (p[1] == '6');  /* P6 = binary, P3 = ASCII */
    p += 2;

    int width  = ppm_read_int(&p, end);
    int height = ppm_read_int(&p, end);
    int maxval = ppm_read_int(&p, end);

    if (width <= 0 || height <= 0 || maxval <= 0) return -5;
    if (width > 1920 || height > 1080) return -6;

    /* Skip exactly one whitespace character after maxval */
    if (p < end && (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')) p++;

    /* Calculate centering position */
    int fb_w = (int)fb.width;
    int dst_x = (fb_w - width) / 2;   /* center horizontally */
    int dst_y = LOGO_AREA_Y;          /* fixed vertical position */
    if (dst_x < 0) dst_x = 0;

    /* ── Blit pixels to framebuffer (direct access) ── */
    if (is_binary) {
        /* P6 — binary RGB: direct framebuffer write, no bounds check per pixel */
        int h = height;
        int w = width;
        int max_y = (int)fb.height;
        int max_x = fb_w;
        if (dst_y + h > max_y) h = max_y - dst_y;
        if (dst_x + w > max_x) w = max_x - dst_x;
        if (h <= 0 || w <= 0) return 0;

        for (int y = 0; y < h; y++) {
            uint32_t *row = (uint32_t*)((uint8_t*)fb.addr +
                             (uint32_t)(dst_y + y) * fb.pitch);
            const unsigned char *src = (const unsigned char*)p + (y * width * 3);
            for (int x = 0; x < w; x++) {
                row[dst_x + x] = ((uint32_t)src[x*3] << 16) |
                                 ((uint32_t)src[x*3+1] << 8) |
                                  (uint32_t)src[x*3+2];
            }
        }
    } else {
        /* P3 — ASCII decimal RGB triplets */
        int max_y = (int)fb.height;
        int max_x = fb_w;
        for (int px_idx = 0; px_idx < width * height; px_idx++) {
            int r = ppm_read_int(&p, end);
            int g = ppm_read_int(&p, end);
            int b = ppm_read_int(&p, end);
            if (r < 0 || g < 0 || b < 0) break;
            if (maxval != 255) {
                r = (r * 255) / maxval;
                g = (g * 255) / maxval;
                b = (b * 255) / maxval;
            }
            int out_x = dst_x + (px_idx % width);
            int out_y = dst_y + (px_idx / width);
            if (out_x < max_x && out_y < max_y) {
                uint32_t *fb_ptr = (uint32_t*)((uint8_t*)fb.addr +
                                    (uint32_t)out_y * fb.pitch) + out_x;
                *fb_ptr = ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
            }
        }
    }

    return 0;
}

/* ── Clear the logo area ────────────────────────────── */
int logo_clear(void) {
    fb_fill_rect(0, LOGO_AREA_Y, (int)fb.width, LOGO_AREA_H + 10,
                 COL_SHELL_BG);
    return 0;
}

/* ── Wait for a few seconds, then clear logo ────────── */
void logo_wait_and_clear(int seconds) {
    if (seconds <= 0 || !show_boot_logo) return;

    /* Busy-wait loop (no timer interrupts available — PIC is masked).
     * Calibrated for QEMU without KVM: ~3M PAUSE iterations ≈ 1 sec. */
    for (volatile int s = 0; s < seconds; s++) {
        for (volatile int i = 0; i < 3000000; i++) {
            __asm__ volatile ("pause");
        }
    }
    logo_clear();
}
