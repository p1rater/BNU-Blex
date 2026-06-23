/*
 * config/palette.h – Color palette configuration
 * Copyright (C) 2026 Blex – BOSL License
 *
 * Catppuccin Mocha palette.  Change these to your preferred
 * colour scheme and all framebuffer/TTY code picks it up.
 */

#ifndef CONFIG_PALETTE_H
#define CONFIG_PALETTE_H

#include <stdint.h>

/* ══════════════════════════════════════════════════════
 *  RGB HELPER
 * ══════════════════════════════════════════════════════ */
#define RGB(r,g,b)  ((uint32_t)(((r)<<16)|((g)<<8)|(b)))

/* ══════════════════════════════════════════════════════
 *  DESKTOP / TASKBAR
 * ══════════════════════════════════════════════════════ */
#define COL_DESKTOP      RGB(17,  17,  27)
#define COL_TASKBAR      RGB(24,  24,  37)
#define COL_TASKBAR_SEP  RGB(49,  50,  68)

/* ══════════════════════════════════════════════════════
 *  WINDOW TITLE / BORDERS
 * ══════════════════════════════════════════════════════ */
#define COL_TITLE_ACT_L  RGB(137, 180, 250)
#define COL_TITLE_ACT_R  RGB(203, 166, 247)
#define COL_TITLE_INACT  RGB(49,  50,  68)
#define COL_BORD_ACT     RGB(137, 180, 250)
#define COL_BORD_INACT   RGB(49,  50,  68)

/* ══════════════════════════════════════════════════════
 *  WINDOW BODY / TERMINAL BACKGROUNDS
 * ══════════════════════════════════════════════════════ */
#define COL_WIN_BODY     RGB(18,  18,  28)
#define COL_SHELL_BG     RGB(10,  14,  22)

/* ══════════════════════════════════════════════════════
 *  TEXT COLOURS
 * ══════════════════════════════════════════════════════ */
#define COL_TEXT_FG      RGB(205, 214, 244)
#define COL_TEXT_DIM     RGB(108, 112, 134)

/* ══════════════════════════════════════════════════════
 *  BUTTON COLOURS (close / minimise / maximise)
 * ══════════════════════════════════════════════════════ */
#define COL_BTN_CLOSE    RGB(243, 139, 168)
#define COL_BTN_MIN      RGB(249, 226, 175)
#define COL_BTN_MAX      RGB(166, 227, 161)

/* ══════════════════════════════════════════════════════
 *  SEMANTIC COLOURS (ok / info / warn / error …)
 *  PAL_ prefix avoids clash with legacy VGA colour indices
 *  (COL_GREEN=2, etc.) used in VGA_ATTR() calls.
 * ══════════════════════════════════════════════════════ */
#define PAL_GREEN        RGB(166, 227, 161)
#define PAL_CYAN         RGB(137, 220, 235)
#define PAL_YELLOW       RGB(249, 226, 175)
#define PAL_RED          RGB(243, 139, 168)
#define PAL_WHITE        RGB(205, 214, 244)

/* ══════════════════════════════════════════════════════
 *  UI ELEMENTS
 * ══════════════════════════════════════════════════════ */
#define COL_CURSOR       RGB(137, 180, 250)
#define COL_DESK_TL      RGB(17,  17,  27)
#define COL_DESK_BR      RGB(30,  20,  45)

/* (VGA_ATTR macro lives in kernel_utils.h, not here) */

#endif /* CONFIG_PALETTE_H */
