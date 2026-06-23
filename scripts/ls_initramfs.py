#!/usr/bin/env python3
"""
ls_initramfs.py – List contents of a gzipped CPIO initramfs archive.

Usage:
    python3 ls_initramfs.py initramfs.cpio.gz
    python3 ls_initramfs.py initramfs.cpio          # uncompressed also works

Output is similar to `ls -lR` – file mode, size, and name for each entry.
"""

import struct
import gzip
import sys
import os


CPIO_MAGIC_NEWC = b"070701"


def parse_hex_field(data: bytes, offset: int, length: int) -> int:
    """Parse an ASCII-hex field from a fixed position."""
    return int(data[offset:offset + length], 16)


def list_cpio(data: bytes) -> list[dict]:
    """Walk a CPIO newc archive and return a list of entry dicts."""
    entries = []
    pos = 0
    while pos + 110 <= len(data):
        magic = data[pos:pos + 6]
        if magic != CPIO_MAGIC_NEWC:
            break

        ino     = parse_hex_field(data, pos +  6,  8)
        mode    = parse_hex_field(data, pos + 14,  8)
        uid     = parse_hex_field(data, pos + 22,  8)
        gid     = parse_hex_field(data, pos + 30,  8)
        nlink   = parse_hex_field(data, pos + 38,  8)
        mtime   = parse_hex_field(data, pos + 46,  8)
        filesize= parse_hex_field(data, pos + 54,  8)
        devmajor= parse_hex_field(data, pos + 62,  8)
        devminor= parse_hex_field(data, pos + 70,  8)
        rdevmajor=parse_hex_field(data, pos + 78,  8)
        rdevminor=parse_hex_field(data, pos + 86,  8)
        namesize= parse_hex_field(data, pos + 94,  8)
        check   = parse_hex_field(data, pos + 102, 8)

        # Read name
        name_bytes = data[pos + 110:pos + 110 + namesize]
        # Strip trailing NUL(s)
        name = name_bytes.rstrip(b"\x00").decode("utf-8", errors="replace")

        if name == "TRAILER!!!":
            break

        # Align to 4 bytes after header+name
        hdr_name_len = 110 + namesize
        aligned_hdr = (hdr_name_len + 3) & ~3
        file_data_start = pos + aligned_hdr

        # Align file data to 4 bytes
        aligned_file = (file_data_start + filesize + 3) & ~3
        next_pos = aligned_file

        entries.append({
            "name": name,
            "mode": mode,
            "size": filesize,
            "uid": uid,
            "gid": gid,
            "ino": ino,
            "nlink": nlink,
            "mtime": mtime,
            "devmajor": devmajor,
            "devminor": devminor,
        })

        pos = next_pos
        if pos >= len(data):
            break

    return entries


def mode_str(mode: int) -> str:
    """Convert CPIO mode bits to a human-readable string like '-rwxr-xr-x'."""
    S_IFMT   = 0o170000
    S_IFSOCK = 0o140000
    S_IFLNK  = 0o120000
    S_IFREG  = 0o100000
    S_IFBLK  = 0o060000
    S_IFDIR  = 0o040000
    S_IFCHR  = 0o020000
    S_IFIFO  = 0o010000

    ft = mode & S_IFMT
    if ft == S_IFDIR:  t = "d"
    elif ft == S_IFLNK: t = "l"
    elif ft == S_IFBLK: t = "b"
    elif ft == S_IFCHR: t = "c"
    elif ft == S_IFIFO: t = "p"
    elif ft == S_IFSOCK:t = "s"
    else:               t = "-"

    perm = ""
    for i in range(2, -1, -1):
        perm += "r" if (mode >> (i * 3 + 2)) & 1 else "-"
        perm += "w" if (mode >> (i * 3 + 1)) & 1 else "-"
        xbit = (mode >> (i * 3)) & 1
        perm += "x" if xbit else "-"

    return t + perm


def format_size(size: int) -> str:
    if size < 1024:
        return f"{size:>6}B"
    elif size < 1024 * 1024:
        return f"{size / 1024:>5.0f}K"
    else:
        return f"{size / (1024 * 1024):>5.1f}M"


def format_name(name: str) -> str:
    """Normalize CPIO name: strip leading ./ or / for cleaner display."""
    n = name
    if n.startswith("./"):
        n = n[2:]
    if n.startswith("/"):
        n = n[1:]
    if n == "":
        n = "."
    return n


def main():
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <initramfs.cpio.gz>", file=sys.stderr)
        sys.exit(1)

    path = sys.argv[1]

    # Read raw bytes – decompress gzip if needed
    with open(path, "rb") as f:
        raw = f.read()

    # Detect gzip magic
    if raw[:2] == b"\x1f\x8b":
        data = gzip.decompress(raw)
    else:
        data = raw

    entries = list_cpio(data)

    if not entries:
        print("(empty archive)")
        return

    # Group by directory tree for ls-like output
    dirs: dict[str, list[dict]] = {}
    for e in entries:
        name = format_name(e["name"])
        if not name or name == ".":
            continue
        # Determine parent directory
        if "/" in name.rstrip("/"):
            parent, leaf = name.rsplit("/", 1)
        else:
            parent, leaf = ".", name

        if parent not in dirs:
            dirs[parent] = []
        dirs[parent].append(e | {"display_name": leaf})

    # Print organised listing
    for parent in sorted(dirs.keys()):
        if parent == ".":
            print(f"./  ({len(dirs[parent])} entries)")
        else:
            print(f"./{parent}/  ({len(dirs[parent])} entries)")
        for e in sorted(dirs[parent], key=lambda x: x["display_name"]):
            mod = mode_str(e["mode"])
            sz = format_size(e["size"])
            print(f"  {mod}  {sz}  {e['display_name']}")
        print()

    print(f"Total: {len(entries)} files/dirs ({sum(e['size'] for e in entries)} bytes)")


if __name__ == "__main__":
    main()
