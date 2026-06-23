/*
 * config/initramfs.h – Initramfs module configuration
 * Copyright (C) 2026 Blex – BOSL License
 *
 * Declares the global initramfs memory region variables and provides
 * configuration for how they are utilised during kernel boot.
 */

#ifndef CONFIG_INITRAMFS_H
#define CONFIG_INITRAMFS_H

#include <stdint.h>

/* ══════════════════════════════════════════════════════
 *  INITRAMFS MEMORY REGION
 *  Populated by detect_initramfs() from the Multiboot2
 *  module tag.  The kernel uses these addresses to locate
 *  the CPIO archive loaded by GRUB's module2 directive.
 * ══════════════════════════════════════════════════════ */
extern uint32_t initramfs_mod_start;
extern uint32_t initramfs_mod_end;

/*
 * initramfs_setup() – convenience wrapper that calls
 * detect_initramfs() on the Multiboot2 info, then
 * extracts the CPIO archive into ES1, and finally loads
 * the dynamic font if present.
 */
void initramfs_setup(uint32_t mb2_magic, void *mb2_info);

#endif /* CONFIG_INITRAMFS_H */
