/*
 * config/system.h – Kernel-level system configuration
 * Copyright (C) 2026 Blex – BOSL License
 *
 * Default user, hostname, shell behaviour, boot-delay timing,
 * keyboard layout selection, and editor settings.
 */

#ifndef CONFIG_SYSTEM_H
#define CONFIG_SYSTEM_H

/* ══════════════════════════════════════════════════════
 *  IDENTITY
 * ══════════════════════════════════════════════════════ */
#define SYS_DEFAULT_USER     "user"
#define SYS_DEFAULT_HOSTNAME "Blex"

/* ══════════════════════════════════════════════════════
 *  SHELL
 * ══════════════════════════════════════════════════════ */
#define SYS_SHELL_BUFFER_SIZE   64
#define SYS_HISTORY_MAX         10
#define SYS_HISTORY_ENTRY_LEN   64
#define SYS_BOOT_DELAY_LOOPS    5000000
#define SYS_KEYBOARD_POLL_DELAY 1000

/* ══════════════════════════════════════════════════════
 *  KEYBOARD LAYOUT
 * ══════════════════════════════════════════════════════ */
#define SYS_DEFAULT_KBD_LAYOUT  0   /* 0 = US (QWERTY), 1 = TR (Turkish Q) */

/* ══════════════════════════════════════════════════════
 *  FONT / TTF RENDERER
 * ══════════════════════════════════════════════════════ */
#define SYS_FONT_DEFAULT_SIZE   28
#define SYS_FALLBACK_FONT_NAME  "JetBrainsMono-Regular.ttf"
#define SYS_FONT_CFG_PATH       "fonts/font.cfg"
#define SYS_FONT_DIR            "fonts/"

/* ══════════════════════════════════════════════════════
 *  BOOT SEQUENCE
 * ══════════════════════════════════════════════════════ */
#define SYS_BANNER "\n  BlexOS x86_64 v0.0.7 \"bee\"   (c) 2026 Blex\n\n" \
                   "  Filesystem: ES1 (Embed File System 1)\n"  \
                   "  Storage:    ATA/SATA PIO driver\n\n"

/* ══════════════════════════════════════════════════════
 *  EDITOR (BlexEdit)
 * ══════════════════════════════════════════════════════ */
#define EDITOR_MAX_ROWS         48
#define EDITOR_MAX_COLS         180

#endif /* CONFIG_SYSTEM_H */
