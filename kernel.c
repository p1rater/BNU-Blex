/*
 * kernel.c – BlexOS x86_64 kernel  (framebuffer TTY edition, 1920×1080)
 * Copyright (C) 2026 Blex – BOSL License
 *
 * Changes vs. WM version:
 *   - Window manager removed; framebuffer used as a single full-screen TTY
 *   - Target resolution: 1920×1080 (requested via GRUB gfxpayload)
 *   - Font and pixel code unchanged; fonts are embedded in fb.c
 */

#include "kernel_utils.h"
#include "commands/commands.h"
#include "fb.h"
#include "fonts/ttf_render.h"
#include "drivers/initramfs.h"
#include "drivers/cpio.h"
#include "config/system.h"

/* ── Externals from command_logic.c ────────────────────── */
extern int   str_match(const char* s1, const char* s2);
extern void  str_copy(char* dest, const char* src);
extern unsigned char* current_layout;
extern char   history[10][64];
extern int    history_count;
extern int    history_index;
extern command_t command_table[];
extern int    command_count;

/* ── Global Kernel State ────────────────────────────────── */
char          current_user[16]    = "user";
char          system_hostname[16] = "Blex";
unsigned int  boot_ticks          = 0;
int           caps_lock           = 0;

char shell_buffer[64];
int  buf_idx = 0;

int  cursor_x = 0;
int  cursor_y = 0;
char current_color = 0x07;

/* ── Compat shims ───────────────────────────────────────── */
void update_cursor(int x, int y) { (void)x; (void)y; }

void clear_screen(void) { tty_clear(); }

void putchar(char c) { tty_putchar(c); }

void print_str(const char* s) { tty_print(s); }

void print_str_color(const char* s, char vga_attr) {
    uint32_t col;
    switch (vga_attr & 0x0F) {
        case 0xA: col = COL_GREEN;   break;
        case 0xB: col = COL_CYAN;    break;
        case 0xC: col = COL_RED;     break;
        case 0xE: col = COL_YELLOW;  break;
        case 0xF: col = COL_WHITE;   break;
        default:  col = COL_TEXT_FG; break;
    }
    tty_print_color(s, col);
}

void print_int(int n) { tty_print_int(n); }

/* ── Keyboard layout ────────────────────────────────────── */
unsigned char kbd_us[128] = {
    0, 27,'1','2','3','4','5','6','7','8','9','0','-','=','\b','\t',
    'q','w','e','r','t','y','u','i','o','p','[',']','\n', 0,
    'a','s','d','f','g','h','j','k','l',';','\'','`', 0,'\\',
    'z','x','c','v','b','n','m',',','.','/', 0,'*', 0,' '
};

/* ── Boot log helpers ───────────────────────────────────── */
void bootlog_ok(const char* msg) {
    print_str_color("[  OK  ] ", (char)0xA);
    print_str(msg); putchar('\n');
}
void bootlog_info(const char* msg) {
    print_str_color("[ BOOT ] ", (char)0xB);
    print_str(msg); putchar('\n');
}
void bootlog_warn(const char* msg) {
    print_str_color("[ WARN ] ", (char)0xE);
    print_str(msg); putchar('\n');
}

/* ── Boot delay ─────────────────────────────────────────── */
static void boot_delay(void) {
    for (volatile int i = 0; i < 5000000; i++);
}

/* ── BRUN loader ────────────────────────────────────────── */
typedef void (*brun_entry_t)(void);

void brun_exec(const char* filename) {
    es1_node_t *node = es1_find(filename);
    if (!node) {
        print_str_color("brun: file not found: ", (char)0xC);
        print_str(filename); putchar('\n'); return;
    }
    brun_header_t* hdr = (brun_header_t*)node->inline_data;
    if (hdr->magic != BRUN_MAGIC) {
        print_str_color("brun: bad magic\n", (char)0xC); return;
    }
    void* code_entry = (void*)((unsigned char*)node->inline_data + sizeof(brun_header_t));
    print_str("brun: launching "); print_str(hdr->name); print_str("...\n");
    brun_entry_t fn = (brun_entry_t)code_entry;
    fn();
    print_str_color("\nbrun: done.\n", (char)0xA);
}

/* ── SATA boot info ─────────────────────────────────────── */
static void report_sata(void) {
    int any = 0;
    for (int d = 0; d < ATA_MAX_DRIVES; d++) {
        if (!ata_drives[d].present) continue;
        if (!any) { bootlog_ok("ATA/SATA drives detected:"); any = 1; }
        print_str("         drive");
        putchar('0' + d);
        print_str(ata_drives[d].is_sata ? " [SATA] " : " [ATA]  ");
        print_str(ata_drives[d].model);
        print_str(" – ");
        uint32_t mb = (ata_drives[d].sectors) / 2048;
        print_int((int)mb); print_str(" MB\n");
    }
    if (!any) bootlog_warn("No ATA/SATA drives found");
}

/* ── ES1 boot info ──────────────────────────────────────── */
static void report_es1(void) {
    print_str_color("[  OK  ] ", (char)0xA);
    print_str("ES1 filesystem mounted: ");
    print_int((int)es1_sb.used_nodes);
    print_str("/");
    print_int(ES1_MAX_NODES);
    print_str(" nodes, label=\"");
    print_str(es1_sb.label);
    print_str("\"\n");
}

/* ── Shell ──────────────────────────────────────────────── */
void print_prompt(void) {
    tty_print_prompt(current_user, system_hostname);
}

void process_command(void) {
    shell_buffer[buf_idx] = '\0';
    putchar('\n');

    if (buf_idx > 0) {
        if (history_count < 10) str_copy(history[history_count++], shell_buffer);
        else {
            for (int i = 0; i < 9; i++) str_copy(history[i], history[i+1]);
            str_copy(history[9], shell_buffer);
        }
        history_index = history_count;

        char cmd_name[32]; int i = 0;
        while (shell_buffer[i] != ' ' && shell_buffer[i] != '\0' && i < 31) {
            cmd_name[i] = shell_buffer[i]; i++;
        }
        cmd_name[i] = '\0';
        const char* args = (shell_buffer[i] == ' ') ? &shell_buffer[i+1] : "";

        int found = 0;
        for (int k = 0; k < command_count; k++) {
            if (str_match(cmd_name, command_table[k].name)) {
                command_table[k].func(args); found = 1; break;
            }
        }
        if (!found) {
            print_str_color("BNU-SH: command not found: ", (char)0xC);
            print_str(cmd_name); putchar('\n');
        }
    }

    print_prompt();
    buf_idx = 0;
}

/* ── Kernel entry ─────────────────────────────────────────
 * GRUB passes mb2_magic in rdi, mb2_info in rsi (SysV64 ABI)
 * via boot.s which moves eax→edi, ebx→esi before the call.
 * ──────────────────────────────────────────────────────── */
void kernel_main(uint32_t mb2_magic, uint64_t mb2_info) {
    /* 1. Init framebuffer (TTY) */
    fb_init(mb2_magic, (void*)(uintptr_t)mb2_info);

    if (!fb.addr) {
        __asm__ volatile ("cli; hlt");
    }

    /* 2. Init ES1 filesystem first (CPIO extraction needs it) */
    es1_init();

    /* 3. Initramfs: detect module, extract CPIO into ES1, load font */
    initramfs_setup(mb2_magic, (void*)(uintptr_t)mb2_info);

    current_layout = kbd_us;

    /* ── Boot sequence ─────────────────────────────────── */
    bootlog_info("BlexOS x86_64 starting..."); boot_delay();
    bootlog_ok("Framebuffer TTY initialised (1920x1080)");

    bootlog_info("Initialising ES1 filesystem...");
    report_es1();

    bootlog_info("Probing ATA/SATA drives...");
    ata_init();
    report_sata();

    bootlog_info("Probing PS/2 keyboard..."); boot_delay();
    bootlog_ok("Keyboard driver ready");

    bootlog_info("Starting shell service..."); boot_delay();

    tty_print_color("\n  BlexOS x86_64 v2.0   (c) 2026 Blex\n\n", COL_CYAN);
    tty_print_color("  Filesystem: ES1 (Embed File System 1)\n",  COL_TEXT_FG);
    tty_print_color("  Storage:    ATA/SATA PIO driver\n\n",       COL_TEXT_FG);
    print_str("Type 'help' for a list of commands.\n\n");
    print_prompt();

    /* ── Main keyboard loop ────────────────────────────── */
    static int ctrl_pressed  = 0;
    static int shift_pressed = 0;

    while (1) {
        boot_ticks++;

        if (inb(0x64) & 1) {
            unsigned char sc  = inb(0x60);
            unsigned char key = sc & 0x7F;
            int is_release    = (sc & 0x80);

            if (key == 0x1D) { ctrl_pressed  = !is_release; continue; }
            if (key == 0x2A || key == 0x36) { shift_pressed = !is_release; continue; }

            if (is_release) continue;

            if (key == 0x3A) { caps_lock = !caps_lock; continue; }

            if (key == 0x48) {   /* Up arrow – history */
                if (history_count > 0 && history_index > 0) {
                    history_index--;
                    while (buf_idx > 0) { putchar('\b'); buf_idx--; }
                    str_copy(shell_buffer, history[history_index]);
                    for (int j = 0; shell_buffer[j]; j++) { putchar(shell_buffer[j]); buf_idx++; }
                }
            } else if (key == 0x50) {   /* Down arrow – history */
                if (history_index < history_count - 1) {
                    history_index++;
                    while (buf_idx > 0) { putchar('\b'); buf_idx--; }
                    str_copy(shell_buffer, history[history_index]);
                    for (int j = 0; shell_buffer[j]; j++) { putchar(shell_buffer[j]); buf_idx++; }
                }
            } else {
                char c = (char)current_layout[key];

                if (shift_pressed || caps_lock) {
                    if (c >= 'a' && c <= 'z') c -= 32;
                }

                if (c == '\n')      process_command();
                else if (c == '\b') { if (buf_idx > 0) { buf_idx--; putchar('\b'); } }
                else if (c && buf_idx < 63) { shell_buffer[buf_idx++] = c; putchar(c); }
            }
        }
        for (volatile int i = 0; i < 1000; i++);
    }
}
