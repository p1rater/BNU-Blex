/*
 * config/fs.h – Filesystem and ATA configuration
 * Copyright (C) 2026 Blex – BOSL License
 *
 * ES1 (Embed File System 1) and FAT32 ramdisk sizes,
 * default directory tree, and ATA/SATA drive limits.
 */

#ifndef CONFIG_FS_H
#define CONFIG_FS_H

#include <stdint.h>

/* ══════════════════════════════════════════════════════
 *  ES1 FILESYSTEM
 * ══════════════════════════════════════════════════════ */
#define ES1_MAX_NODES      32
#define ES1_NAME_LEN       64
#define ES1_INLINE_SIZE    480
#define ES1_MAX_EXTENTS    8
#define ES1_EXTENT_SIZE    4096
#define ES1_LABEL          "BlexOS-ES1"

/* ══════════════════════════════════════════════════════
 *  ES1 – only root / is created by es1_init.
 *  All other directories and files come from the
 *  initramfs CPIO archive extracted at boot.
 * ══════════════════════════════════════════════════════ */

/* ══════════════════════════════════════════════════════
 *  FAT32 RAMDISK
 * ══════════════════════════════════════════════════════ */
#define FAT32_SECTOR_SZ      512
#define FAT32_TOTAL_SECTS    1024
#define FAT32_DISK_SIZE      (FAT32_TOTAL_SECTS * FAT32_SECTOR_SZ)
#define FAT32_SECTS_PER_CLUS 1
#define FAT32_NUM_FATS       2
#define FAT32_FAT_SZ_SECTS   32
#define FAT32_RSVD_SECTS     1
#define FAT32_ROOT_CLUS      2

#define FAT32_FAT1_START     FAT32_RSVD_SECTS
#define FAT32_FAT2_START     (FAT32_FAT1_START + FAT32_FAT_SZ_SECTS)
#define FAT32_DATA_START     (FAT32_FAT2_START + FAT32_FAT_SZ_SECTS)

#define FAT32_EOC   0x0FFFFFF8u
#define FAT32_FREE  0x00000000u
#define FAT32_BAD   0x0FFFFFF7u

/* ══════════════════════════════════════════════════════
 *  ATA / SATA DRIVER
 * ══════════════════════════════════════════════════════ */
#define ATA_MAX_DRIVES       4

/* ATA I/O port bases */
#define ATA_PRIMARY_BASE    0x1F0
#define ATA_PRIMARY_CTRL    0x3F6
#define ATA_SECONDARY_BASE  0x170
#define ATA_SECONDARY_CTRL  0x376

/* ATA register offsets from base */
#define ATA_REG_DATA        0x00
#define ATA_REG_ERROR       0x01
#define ATA_REG_FEATURES    0x01
#define ATA_REG_SECCOUNT    0x02
#define ATA_REG_LBA_LO      0x03
#define ATA_REG_LBA_MID     0x04
#define ATA_REG_LBA_HI      0x05
#define ATA_REG_DRIVE       0x06
#define ATA_REG_STATUS      0x07
#define ATA_REG_COMMAND     0x07

#define ATA_STATUS_BSY      0x80
#define ATA_STATUS_DRQ      0x08
#define ATA_STATUS_ERR      0x01

#define ATA_CMD_IDENTIFY    0xEC
#define ATA_CMD_READ_PIO    0x20
#define ATA_CMD_WRITE_PIO   0x30

#endif /* CONFIG_FS_H */
