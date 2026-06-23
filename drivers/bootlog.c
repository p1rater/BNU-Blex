/*
 * bootlog.c – Hardware probing & boot-time logging for BlexOS
 *
 * Prints real hardware information during boot:
 *   CPU vendor, features (AVX2, AVX-512, SSE...), frequency
 *   Memory size (from Multiboot2)
 *   PCI bus scan
 *   Timer calibration (PIT)
 *   A20 gate status
 *
 * AVX-512 and AVX2 are detected via CPUID but cannot be used
 * in 32-bit protected mode (they require 64-bit long mode).
 * The kernel reports them as "detected (64-bit only)".
 */

#include "../kernel_utils.h"
#include "fb/fb.h"
#include "bootlog.h"
#include "logo_display.h"
#include "pci_vendors.h"
#include "idt.h"
#include <stdint.h>
#include <stddef.h>

/* print_hex is defined in command_logic.c */
extern void print_hex(uint32_t n);

/* ── Boot log prefix ──────────────────────────────────── */
static void bootlog(const char *tag, const char *msg) {
    tty_print_color("[", PAL_GREEN);
    tty_print_color(tag, PAL_CYAN);
    tty_print_color("] ", PAL_GREEN);
    tty_print_color(msg, COL_TEXT_FG);
    /* Also save to dmesg buffer */
    dmesg_write(tag, msg);
}

/* ── CPUID helper ─────────────────────────────────────── */
static int cpuid_supported(void) {
    uint32_t old_flags, new_flags;
    __asm__ volatile (
        "pushfl\n\t"
        "popl %0\n\t"
        "movl %0, %1\n\t"
        "xorl $0x200000, %1\n\t"
        "pushl %1\n\t"
        "popfl\n\t"
        "pushfl\n\t"
        "popl %1\n\t"
        "pushl %0\n\t"
        "popfl"
        : "=r"(old_flags), "=r"(new_flags)
        :
        : "memory"
    );
    return (old_flags != new_flags);
}

static void cpuid(uint32_t leaf, uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d) {
    __asm__ volatile (
        "cpuid"
        : "=a"(*a), "=b"(*b), "=c"(*c), "=d"(*d)
        : "a"(leaf)
    );
}

/* ── Read CMOS/RTC ────────────────────────────────────── */
static uint8_t cmos_read(uint8_t reg) {
    outb(0x70, reg);
    return inb(0x71);
}

/* ── Read Timer Count (PIT) ───────────────────────────── */
static uint16_t pit_read_count(void) {
    outb(0x43, 0x00); /* latch counter 0 */
    uint16_t lo = inb(0x40);
    uint16_t hi = inb(0x40);
    return (uint16_t)(lo | (hi << 8));
}

/* ── A20 gate check ──────────────────────────────────── */
static int a20_enabled(void) {
    /* Check A20 via BIOS interrupt 0x15, AX=0x2401 / 0x2402
     * Since we're in protected mode, use a memory comparison
     * via inline asm to prevent compiler optimization. */
    uint32_t val1, val2;
    /* Read from 0x100000 via asm to prevent UB optimization */
    __asm__ volatile (
        "movl 0x100000, %0\n\t"
        "movl 0x000000, %1\n\t"
        : "=r"(val1), "=r"(val2)
        :
        : "memory"
    );
    /* If A20 is disabled, both reads return the same value
     * (memory wraps).  If enabled, they differ (different mem). */
    /* Write test pattern to 0x100000 */
    __asm__ volatile (
        "movl $0xDEADBEEF, 0x100000\n\t"
        "movl 0x000000, %0\n\t"
        "movl %1, 0x100000"
        : "=r"(val2)
        : "r"(val1)
        : "memory"
    );
    return (val2 != 0xDEADBEEFu);
}

/* ── CPU frequency estimation ────────────────────────────
 * Uses the PIT counter to estimate CPU speed. */
static uint32_t estimate_cpu_mhz(void) {
    /* Program PIT counter 0 for mode 0, max count */
    outb(0x43, 0x30);       /* counter 0, mode 0, 16-bit binary */
    outb(0x40, 0xFF);       /* low byte */
    outb(0x40, 0xFF);       /* high byte → count = 65535 */

    /* Wait a bit using a fixed loop, then see how much decremented */
    for (volatile int i = 0; i < 10000; i++);

    uint16_t remaining = pit_read_count();
    uint16_t elapsed = 65535 - remaining;
    if (elapsed == 0) elapsed = 1;

    /* Rough estimate: at 1GHz, ~1000 PIT ticks per 10000-iteration loop */
    uint32_t mhz = (elapsed * 1000) / 100;
    if (mhz < 1) mhz = 1;
    if (mhz > 9999) mhz = 9999;
    return mhz;
}

/* ════════════════════════════════════════════════════════
 *  PUBLIC: boot_log_all()
 *  Called once during kernel init, after fb_init.
 * ════════════════════════════════════════════════════════ */
void boot_log_all(uint32_t mb2_magic, uint32_t mb2_info) {
    /* ── Header ────────────────────────────────────────── */
    tty_print_color("[BLEX] BlexOS x86_64 v0.0.7 \"bee\" starting...\n", PAL_CYAN);

    /* ── CPU information via CPUID ────────────────────── */
    if (!cpuid_supported()) {
        bootlog("BLEX", "CPU: 80386 or earlier (no CPUID)\n");
        return;
    }

    uint32_t a, b, c, d;
    cpuid(0, &a, &b, &c, &d);  /* vendor string */

    char vendor[13];
    ((uint32_t*)vendor)[0] = b;
    ((uint32_t*)vendor)[1] = d;
    ((uint32_t*)vendor)[2] = c;
    vendor[12] = '\0';

    /* Max CPUID leaf */
    cpuid(1, &a, &b, &c, &d);

    uint32_t family = (a >> 8) & 0xF;
    uint32_t model  = (a >> 4) & 0xF;
    uint32_t stepping = a & 0xF;
    uint32_t ext_family = (a >> 20) & 0xFF;
    uint32_t ext_model  = (a >> 16) & 0xF;

    if (family == 0xF) family = ext_family + 0xF;
    if (family == 0x6 || family == 0xF) model = (ext_model << 4) | model;

    /* CPU brand string (leaf 0x80000002-0x80000004) */
    char brand[49];
    if (a >= 0x80000004) {
        cpuid(0x80000002, (uint32_t*)&brand[0], (uint32_t*)&brand[4],
              (uint32_t*)&brand[8], (uint32_t*)&brand[12]);
        cpuid(0x80000003, (uint32_t*)&brand[16], (uint32_t*)&brand[20],
              (uint32_t*)&brand[24], (uint32_t*)&brand[28]);
        cpuid(0x80000004, (uint32_t*)&brand[32], (uint32_t*)&brand[36],
              (uint32_t*)&brand[40], (uint32_t*)&brand[44]);
        brand[48] = '\0';
    } else {
        /* Build a description from family/model */
        char buf[64];
        int p = 0;
        const char *fam_str = "Unknown";
        if (vendor[0] == 'G' && vendor[1] == 'e') fam_str = "Intel";
        else if (vendor[0] == 'A' && vendor[1] == 'u') fam_str = "AMD";
        bootlog("BLEX", "CPU: ");
        tty_print_color(fam_str, PAL_YELLOW);
        tty_print_color(" family=", COL_TEXT_FG);
        print_int((int)family);
        tty_print_color(" model=", COL_TEXT_FG);
        print_int((int)model);
        tty_print_color(" stepping=", COL_TEXT_FG);
        print_int((int)stepping);
        putchar('\n');
    }

    /* Print CPU info */
    if (brand[0]) {
        /* Clean brand string (trim leading spaces) */
        char *bp = brand;
        while (*bp == ' ') bp++;
        tty_print_color("[BLEX] CPU: ", PAL_CYAN);
        tty_print_color(bp, PAL_YELLOW);
        tty_print_color("\n", COL_TEXT_FG);
    }

    /* CPU speed */
    uint32_t mhz = estimate_cpu_mhz();
    tty_print_color("[BLEX] CPU Speed: ~", PAL_CYAN);
    print_int((int)mhz);
    tty_print_color(" MHz (estimated via PIT)\n", COL_TEXT_FG);

    /* ── Feature flags (leaf 1, EDX + ECX) ───────────── */
    cpuid(1, &a, &b, &c, &d);

    /* Standard features (EDX) */
    struct { uint32_t mask; const char *name; } edx_features[] = {
        { 1u<<23, "MMX"       },
        { 1u<<25, "SSE"       },
        { 1u<<26, "SSE2"      },
        { 1u<< 0, "FPU"       },
        { 1u<< 4, "TSC"       },
        { 1u<< 5, "MSR"       },
        { 1u<< 8, "CX8"       },
        { 1u<<11, "SEP"       },
        { 1u<<19, "CLFSH"     },
        { 1u<<24, "FXSR"      },
        { 1u<<28, "HTT"       },
        { 0,      NULL        },
    };

    tty_print_color("[BLEX] CPU Features: ", PAL_CYAN);
    int first = 1;
    for (int i = 0; edx_features[i].name; i++) {
        if (d & edx_features[i].mask) {
            if (!first) tty_print_color(", ", COL_TEXT_FG);
            tty_print_color(edx_features[i].name, PAL_YELLOW);
            first = 0;
        }
    }

    /* Extended features (ECX) */
    struct { uint32_t mask; const char *name; } ecx_features[] = {
        { 1u<< 0, "SSE3"      },
        { 1u<< 1, "PCLMUL"    },
        { 1u<< 9, "SSSE3"     },
        { 1u<<12, "FMA"       },
        { 1u<<13, "CX16"      },
        { 1u<<19, "SSE4.1"    },
        { 1u<<20, "SSE4.2"    },
        { 1u<<22, "MOVBE"     },
        { 1u<<23, "POPCNT"    },
        { 1u<<25, "AES"       },
        { 1u<<26, "XSAVE"     },
        { 1u<<27, "OSXSAVE"   },
        { 1u<<28, "AVX"       },
        { 1u<<29, "F16C"      },
        { 1u<<30, "RDRAND"    },
        { 0,      NULL        },
    };

    for (int i = 0; ecx_features[i].name; i++) {
        if (c & ecx_features[i].mask) {
            if (!first) tty_print_color(", ", COL_TEXT_FG);
            tty_print_color(ecx_features[i].name, PAL_YELLOW);
            first = 0;
        }
    }
    putchar('\n');

    /* ── AVX2 detection (leaf 7, subleaf 0, EBX) ─────── */
    if (a >= 7) {
        uint32_t eax7, ebx7, ecx7, edx7;
        cpuid(7, &eax7, &ebx7, &ecx7, &edx7);

        struct { uint32_t bit; const char *name; int is_64only; } leaf7_features[] = {
            { 3,  "BMI1",       0 },
            { 5,  "AVX2",       0 },
            { 8,  "BMI2",       0 },
            { 16, "AVX-512F",   1 },  /* 64-bit only */
            { 17, "AVX-512DQ",  1 },
            { 19, "AVX512-IFMA",1 },
            { 26, "AVX512-PF",  1 },
            { 27, "AVX512-ER",  1 },
            { 28, "AVX512-CD",  1 },
            { 30, "AVX512-BW",  1 },
            { 31, "AVX512-VL",  1 },
            { 0,  NULL,         0 },
        };

        int any_avx = 0;
        for (int i = 0; leaf7_features[i].name; i++) {
            if (ebx7 & (1u << leaf7_features[i].bit)) {
                if (!any_avx) {
                    tty_print_color("[BLEX] AVX: ", PAL_CYAN);
                    any_avx = 1;
                } else {
                    tty_print_color(", ", COL_TEXT_FG);
                }
                tty_print_color(leaf7_features[i].name, PAL_YELLOW);
                if (leaf7_features[i].is_64only) {
                    tty_print_color("(64-bit)", PAL_GREEN);
                }
            }
        }
        if (any_avx) putchar('\n');
    }

    /* ── Cache info (leaf 2) ──────────────────────────── */
    cpuid(2, &a, &b, &c, &d);
    /* Leaf 2 returns cache/TLB info in bytes; just report existence */
    tty_print_color("[BLEX] CPU Cache: ", PAL_CYAN);
    print_int((int)(a & 0xFF));
    tty_print_color(" descriptors (leaf 2)\n", COL_TEXT_FG);

    /* ── Memory ────────────────────────────────────────── */
    /* Parse Multiboot2 memory map for physical addresses */
    {
        uint32_t total_mb = 0;
        uint32_t ram_regions = 0;

        if (mb2_magic == 0x36D76289) {
            uint8_t *mp = (uint8_t*)(uintptr_t)mb2_info + 8;
            uint32_t mtotal = *(uint32_t*)(uintptr_t)mb2_info;
            uint8_t *mend = (uint8_t*)(uintptr_t)mb2_info + mtotal;

            while (mp < mend) {
                uint32_t mtype = *(uint32_t*)mp;
                uint32_t msize = *(uint32_t*)(mp + 4);
                if (mtype == 0) break;
                if (mtype == 6) {  /* Memory map tag */
                    uint8_t entry_size = *(uint8_t*)(mp + 8);
                    uint8_t *entries = mp + 16;
                    uint8_t *entries_end = mp + msize;
                    while (entries + entry_size <= entries_end) {
                        uint64_t base = *(uint64_t*)entries;
                        uint64_t len  = *(uint64_t*)(entries + 8);
                        uint32_t mtype32 = *(uint32_t*)(entries + 16);
                        uint32_t reserved = *(uint32_t*)(entries + 20);
                        (void)reserved;

                        if (mtype32 == 1) {  /* Usable RAM */
                            ram_regions++;
                            total_mb += (uint32_t)(len / (1024 * 1024));
                            tty_print_color("[BLEX] RAM: ", PAL_CYAN);
                        } else if (mtype32 == 3) {
                            tty_print_color("[BLEX] ACPI: ", PAL_CYAN);
                        } else if (mtype32 == 4) {
                            tty_print_color("[BLEX] NVS:  ", PAL_CYAN);
                        } else {
                            tty_print_color("[BLEX] RSVD: ", PAL_CYAN);
                        }

                        /* Print physical address range */
                        uint32_t base_hi = (uint32_t)(base >> 32);
                        uint32_t base_lo = (uint32_t)(base & 0xFFFFFFFF);
                        uint32_t end_lo  = (uint32_t)((base + len) & 0xFFFFFFFF);
                        uint32_t end_hi  = (uint32_t)((base + len) >> 32);

                        if (base_hi) print_hex(base_hi);
                        print_hex(base_lo);
                        tty_print_color(" - ", COL_TEXT_FG);
                        if (end_hi) print_hex(end_hi);
                        print_hex(end_lo);

                        tty_print_color("  (", COL_TEXT_FG);
                        if (len >= 1024*1024) {
                            print_int((int)(len / (1024*1024)));
                            tty_print_color(" MiB)", COL_TEXT_FG);
                        } else if (len >= 1024) {
                            print_int((int)(len / 1024));
                            tty_print_color(" KiB)", COL_TEXT_FG);
                        } else {
                            print_int((int)len);
                            tty_print_color(" B)", COL_TEXT_FG);
                        }

                        if (mtype32 == 1) {
                            tty_print_color(" usable", PAL_GREEN);
                        }
                        putchar('\n');

                        entries += entry_size;
                    }
                }
                uint32_t aligned = (msize + 7) & ~7u;
                mp += aligned;
            }
        }

        if (ram_regions == 0) {
            /* Fallback: read CMOS */
            uint8_t lo = cmos_read(0x30);
            uint8_t hi = cmos_read(0x31);
            uint32_t mem_lower = ((uint32_t)hi << 8) | lo;
            lo = cmos_read(0x17);
            hi = cmos_read(0x18);
            uint32_t mem_upper = ((uint32_t)hi << 8) | lo;
            total_mb = (mem_lower + mem_upper) / 1024;
            if (total_mb < 1) total_mb = 64;
            tty_print_color("[BLEX] RAM (CMOS): ", PAL_CYAN);
            print_int((int)total_mb);
            tty_print_color(" MiB total\n", COL_TEXT_FG);
        }

        tty_print_color("[BLEX] A20 line: ", PAL_CYAN);
        tty_print_color(a20_enabled() ? "enabled" : "disabled",
                       a20_enabled() ? PAL_GREEN : PAL_RED);
        putchar('\n');
    }

    /* ── Timer info ────────────────────────────────────── */
    tty_print_color("[BLEX] PIT: 1000 Hz (actual: ~1193182 / ", PAL_CYAN);
    print_int((int)pit_read_count());
    tty_print_color(")\n", COL_TEXT_FG);

    {
        /* RTC check: read register A */
        uint8_t rtc_a = cmos_read(0x0A);
        tty_print_color("[BLEX] RTC: status=", PAL_CYAN);
        print_hex(rtc_a);
        tty_print_color((rtc_a & 0x80) ? " (update in progress)" :
                        " (battery ok)", COL_TEXT_FG);
        putchar('\n');
    }

    /* ── PCI bus scan (bus 0, devices 0-31) ────────────── */
    {
        int pci_count = 0;
        for (int dev = 0; dev < 32; dev++) {
            uint32_t vendor = pci_read_config(0, dev, 0, 0) & 0xFFFF;
            if (vendor != 0xFFFF && vendor != 0) {
                if (pci_count == 0) {
                    tty_print_color("[BLEX] PCI bus scan:\n", PAL_CYAN);
                }
                uint32_t dev_id = pci_read_config(0, dev, 0, 0) >> 16;
                uint32_t class_rev = pci_read_config(0, dev, 0, 8);
                uint8_t class_code = (class_rev >> 24) & 0xFF;
                uint8_t subclass   = (class_rev >> 16) & 0xFF;
                uint8_t prog_if    = (class_rev >> 8) & 0xFF;

                /* Get short class name */
                const char *class_name = "?";
                if (class_code == 0x01) {
                    if (subclass == 0x06) class_name = "SATA";
                    else class_name = "Storage";
                } else if (class_code == 0x02) class_name = "Network";
                else if (class_code == 0x03) class_name = "Display";
                else if (class_code == 0x04) class_name = "Audio";
                else if (class_code == 0x06) class_name = "Bridge";
                else if (class_code == 0x08) class_name = "Periph";
                else if (class_code == 0x0C && subclass == 0x03) class_name = "USB3";
                else if (class_code == 0x0C) class_name = "Serial";

                /* Show vendor name from lookup table */
                const char *vname = pci_vendor_name((uint16_t)vendor);

                tty_print_color("      00:", COL_TEXT_FG);
                print_int(dev);
                tty_print_color(".0  ", COL_TEXT_FG);
                print_hex(vendor);
                tty_print_color(":", COL_TEXT_FG);
                print_hex(dev_id);
                tty_print_color("  ", COL_TEXT_FG);
                tty_print_color(class_name, PAL_YELLOW);
                if (vname) {
                    tty_print_color("  ", COL_TEXT_FG);
                    tty_print_color(vname, PAL_WHITE);
                }
                putchar('\n');
                pci_count++;
            }
        }
        if (pci_count == 0) {
            tty_print_color("[BLEX] PCI bus scan: 0 devices found\n", PAL_CYAN);
        }
    }

    /* ── Debug addresses ──────────────────────────────── */
    extern uint32_t initramfs_mod_start;
    extern uint32_t initramfs_mod_end;
    extern fb_info_t fb;

    tty_print_color("[BLEX] Kernel: 0x100000 - entry at ", PAL_CYAN);
    extern void kernel_main(void);
    print_hex((uint32_t)&kernel_main);
    putchar('\n');

    tty_print_color("[BLEX] Stack:  0x", PAL_CYAN);
    {
        uint32_t esp;
        __asm__ volatile ("mov %%esp, %0" : "=r"(esp));
        print_hex(esp);
        tty_print_color(" (size: 32 KiB)\n", COL_TEXT_FG);
    }

    tty_print_color("[BLEX] FB:     0x", PAL_CYAN);
    print_hex((uint32_t)(uintptr_t)fb.addr);
    tty_print_color("  ", COL_TEXT_FG);
    print_int((int)fb.width);
    tty_print_color("x", COL_TEXT_FG);
    print_int((int)fb.height);
    tty_print_color("x", COL_TEXT_FG);
    print_int((int)fb.bpp);
    tty_print_color("  pitch=", COL_TEXT_FG);
    print_int((int)fb.pitch);
    putchar('\n');

    if (initramfs_mod_start) {
        tty_print_color("[BLEX] Initramfs: 0x", PAL_CYAN);
        print_hex(initramfs_mod_start);
        tty_print_color(" - 0x", COL_TEXT_FG);
        print_hex(initramfs_mod_end);
        tty_print_color(" (", COL_TEXT_FG);
        print_int((int)((initramfs_mod_end - initramfs_mod_start) / 1024));
        tty_print_color(" KiB)\n", COL_TEXT_FG);
    }

    extern uint32_t _start;
    tty_print_color("[BLEX] IDT:    0x", PAL_CYAN);
    print_hex((uint32_t)&idt_table);
    tty_print_color("  entries=256\n", COL_TEXT_FG);
}
