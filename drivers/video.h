/*
 * config/video.h – Video mode and TTY layout configuration
 * Copyright (C) 2026 Blex – BOSL License
 *
 * Change these constants to alter the display resolution,
 * font cell size, padding, and fetch-image placement
 * without touching any logic code.
 */

#ifndef CONFIG_VIDEO_H
#define CONFIG_VIDEO_H

#include <stdint.h>

/* ══════════════════════════════════════════════════════
 *  FRAMEBUFFER RESOLUTION
 * ══════════════════════════════════════════════════════ */
#define VIDEO_WIDTH       1920   /* requested framebuffer width  (px) */
#define VIDEO_HEIGHT      1080   /* requested framebuffer height (px) */
#define VIDEO_BPP         32     /* bits per pixel                */
#define VIDEO_FALLBACK_ADDR  0xFD000000u  /* VESA LFB fallback    */

/* ══════════════════════════════════════════════════════
 *  TTY FONT CELL (character grid advance)
 * ══════════════════════════════════════════════════════ */
#define FONT_W            8      /* character cell width  (px) */
#define FONT_H            16     /* character cell height (px) */

/* ══════════════════════════════════════════════════════
 *  TTY SCREEN PADDING (margins from frame edges)
 * ══════════════════════════════════════════════════════ */
#define TTY_PAD_X          8     /* left / right margin   (px) */
#define TTY_PAD_Y          4     /* top margin            (px) */

/* ══════════════════════════════════════════════════════
 *  FETCH (neofetch-style) IMAGE PLACEMENT
 * ══════════════════════════════════════════════════════ */
#define FETCH_IMG_X       1100   /* left edge of fetched image  (px) */
#define FETCH_IMG_Y        140   /* top  edge of fetched image  (px) */
#define FETCH_IMG_W        450   /* rendered width     (px) */
#define FETCH_IMG_H        450   /* rendered height    (px) */
#define FETCH_PNG_DIR     "/etc/fetchpng"
#define FETCH_PNG_PATH    "/etc/fetchpng/itsblex.png"

/* ══════════════════════════════════════════════════════
 *  BOOT.S MIRROR (NASM equates for the same values)
 *  Keep config/video_nasm.inc in sync when changing above.
 * ══════════════════════════════════════════════════════ */

#endif /* CONFIG_VIDEO_H */
