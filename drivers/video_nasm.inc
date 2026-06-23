;; config/video_nasm.inc – Video mode constants for boot.s
;; Copyright (C) 2026 Blex – BOSL License
;;
;; Must stay in sync with config/video.h
;; Included by boot.s via nasm's %include directive.

;; ── Framebuffer resolution ─────────────────────────────
VIDEO_WIDTH  equ 1920
VIDEO_HEIGHT equ 1080
VIDEO_BPP    equ 32
