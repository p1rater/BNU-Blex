# BlexOS — x86_64 Hobby OS

<img width="473" height="115" alt="logo_blex_clut224" src="https://github.com/user-attachments/assets/2fea42b6-5ce1-4a0f-b53e-a6f191b25fe6" />

A minimal x86_64 kernel with a framebuffer TTY, embedded filesystem, and dynamic TTF font rendering. Boots via GRUB with Multiboot2.

## Quick Start

```bash
# Prerequisites
sudo apt install gcc-i686-linux-gnu nasm grub-pc-bin xorriso qemu-system-x86

# Build & run
make run
```

This builds the kernel, packs the initramfs, creates a bootable ISO, and launches QEMU.

## Project Layout

```
├── kernel.c              # Kernel entry point & main loop
├── es1.c                 # ES1 embedded filesystem (flat in-memory FS)
├── fb.c                  # Framebuffer driver (1920×1080 TTY)
├── sata.c                # ATA/SATA PIO driver
├── bsh.c                 # Bourne-shell-like command interpreter
├── commands/             # Built-in commands (help, ls, cat, pngview, etc.)
├── drivers/              # Modular drivers
│   ├── initramfs.c       # Multiboot2 module detection + CPIO extraction
│   ├── cpio.c            # CPIO newc archive parser
│   ├── bootlog.c         # Hardware probing (CPU, PCI, memory, A20, timer)
│   ├── idt.c             # Interrupt descriptor table
│   ├── logo_display.c    # Boot logo (PPM from initramfs)
│   └── sata/ net/ virtio/ serial/ fb/  # Sub-drivers
├── fonts/                # TTF font renderer
│   ├── ttf_render.c      # FreeType-like TTF rasteriser
│   ├── ttf_render.h
│   └── *.ttf             # Bundled fonts (JetBrains Mono, Noto Emoji)
├── config/
│   └── system.h          # Kernel config (user, hostname, font sizing)
├── initramfs/            # Initramfs source tree
│   ├── init              # Startup script
│   ├── bin/              # BRUN executables (mbedit)
│   ├── etc/              # Config (os-release, log.cfg)
│   └── fonts/            # TTF fonts deployed to the filesystem
├── boot.s                # Multiboot2 header + 32-bit entry stub
├── linker.ld             # Kernel link script
├── Makefile              # Build system
├── scripts/
│   ├── ls_initramfs.py   # List initramfs.cpio.gz contents (host tool)
│   └── pci_vendor_gen.py # Generate PCI vendor lookup table from pci.ids
└── README.md
```

## Build System

| Target | Description |
|--------|-------------|
| `make`         | Build kernel + initramfs |
| `make run`     | Build, create GRUB ISO, launch QEMU |
| `make clean`   | Remove objects and build artifacts |

The toolchain targets **i686** (`i686-linux-gnu-gcc`), producing a 32-bit protected-mode binary. The kernel switches to long mode during boot.

## Initramfs

The initramfs is a **CPIO newc** archive packed from the `initramfs/` directory. At boot, the kernel detects it as a Multiboot2 module and extracts every file into the ES1 filesystem.

### Host-side Inspection

```bash
# List contents of the compressed initramfs
python3 scripts/ls_initramfs.py initramfs.cpio.gz

# Also works on the uncompressed version
python3 scripts/ls_initramfs.py initramfs.cpio
```

Example output:

```
./  (6 entries)
  drwxr-xr-x       0B  bin
  drwxr-xr-x       0B  etc
  drwxr-xr-x       0B  fonts
  -rw-r--r--     164B  init

./fonts/  (3 entries)
  -rw-r--r--    267K  JetBrainsMono-Regular.ttf
  -rw-r--r--    1.9M  NotoEmoji-VariableFont_wght.ttf
  -rw-r--r--      31B  font.cfg

Total: 19 files/dirs (2728699 bytes)
```

### Regenerating

```bash
cd initramfs && find . | cpio -o -H newc --quiet > ../initramfs.cpio
gzip -k -f initramfs.cpio
```

(Or just run `make` — it handles both steps.)

## Filesystem: ES1

ES1 is a flat, in-memory filesystem with 32 fixed-size node slots. Each node stores either inline data (≤480 bytes) or points to an external address in the CPIO archive (zero-copy). All directories and files are created at boot by `initramfs_setup()`, which extracts the CPIO archive into ES1.

## Kernel Boot Flow

```
GRUB (Multiboot2)
  │
  ├─ boot.s         ← Multiboot2 header, 32-bit stub
  │
  └─ kernel_main()  ← Switches to long mode
       │
       ├─ fb_init()              ← Framebuffer TTY (1920×1080)
       ├─ es1_init()             ← ES1 superblock + root /
       ├─ initramfs_setup()      ← Detect module, extract CPIO, load font
       ├─ ata_init()             ← Probe ATA/SATA drives
       └─ Shell loop            ← Keyboard input / command dispatch
```

## Dependencies

| Package | Purpose |
|---------|---------|
| `gcc-i686-linux-gnu` | Cross-compiler for i686 target |
| `nasm`               | Assembly (boot.s) |
| `grub-pc-bin`        | grub-mkrescue for ISO generation |
| `xorriso`            | ISO creation backend |
| `qemu-system-x86`    | Emulation (run target) |

## License

BOSL — see source headers for details.

The bundled fonts are licensed under their respective open-source licenses:
- **JetBrains Mono** — OFL
- **Noto Emoji** — OFL
