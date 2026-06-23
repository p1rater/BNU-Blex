/*
 * config/cpio.h – CPIO newc archive parser for BlexOS
 * Copyright (C) 2026 Blex – BOSL License
 *
 * Provides functions to walk a CPIO newc-formatted archive in memory
 * and extract files.  The caller supplies the archive base address.
 *
 * cpio_extract_all() inserts every regular file found in the archive
 * into the ES1 filesystem under the path given in the CPIO entry,
 * allowing the initramfs contents to be accessed as /etc/fetchpng/…,
 * /fonts/…, /bin/…, etc.
 *
 * To skip the leading "./" that some cpio producers add, use
 * config/initramfs.h to set how much prefix to strip.
 */

#ifndef CONFIG_CPIO_H
#define CONFIG_CPIO_H

#include <stdint.h>

/* ══════════════════════════════════════════════════════
 *  CPIO NEWC HEADER (110 bytes)
 * ══════════════════════════════════════════════════════ */
struct cpio_newc_header {
    char magic[6];      /* "070701" */
    char ino[8];
    char mode[8];
    char uid[8];
    char gid[8];
    char nlink[8];
    char mtime[8];
    char filesize[8];
    char devmajor[8];
    char devminor[8];
    char rdevmajor[8];
    char rdevminor[8];
    char namesize[8];
    char check[8];
};

/* ══════════════════════════════════════════════════════
 *  CPIO EXTRACTION CONFIG
 *  Override in config/initramfs.h if needed.
 * ══════════════════════════════════════════════════════ */

/* Strip "./" prefix from CPIO entry names */
#ifndef CPIO_STRIP_DOT_SLASH
#define CPIO_STRIP_DOT_SLASH  1
#endif

/* Strip leading "/" from CPIO entry names (some cpio tools add it) */
#ifndef CPIO_STRIP_LEADING_SLASH
#define CPIO_STRIP_LEADING_SLASH 1
#endif

/* ══════════════════════════════════════════════════════
 *  API
 * ══════════════════════════════════════════════════════ */

/*
 * cpio_find_file – locate a single file in a CPIO archive.
 *
 * Parameters:
 *   archive   – pointer to the base of a CPIO newc archive
 *   filename  – exact path within the archive
 *   out_size  – (output) size of the file data in bytes
 *
 * Returns: pointer to the file data, or NULL if not found.
 */
uint8_t* cpio_find_file(const char *archive, const char *filename,
                        uint32_t *out_size);

/*
 * cpio_extract_all – walk an entire CPIO archive and insert every
 * regular file into ES1 under the path recorded in the archive.
 *
 * Parameters:
 *   archive – pointer to the base of a CPIO newc archive
 *
 * Returns: number of files extracted, or -1 if the archive magic is bad.
 */
int cpio_extract_all(const char *archive);

/*
 * cpio_extract_one – extract a single file from a CPIO archive and
 * insert it into ES1 under a given virtual path.
 *
 * Parameters:
 *   archive     – pointer to the base of a CPIO newc archive
 *   cpio_name   – the name used within the CPIO (e.g. "fonts/font.cfg")
 *   es1_path    – the target ES1 path (e.g. "/fonts/font.cfg")
 *
 * Returns: 1 on success, 0 if not found, -1 on error.
 */
int cpio_extract_one(const char *archive, const char *cpio_name,
                     const char *es1_path);

#endif /* CONFIG_CPIO_H */
