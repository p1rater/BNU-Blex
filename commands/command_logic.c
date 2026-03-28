#include "commands.h"

/* --- HARİCİ SİSTEM REFERANSLARI --- */
extern int cursor_x, cursor_y;
extern void update_cursor(int x, int y);
extern vfs_node_t ram_disk[10]; 
extern char current_color;
extern unsigned char inb(unsigned short port);
extern void putchar(char c);
extern void clear_screen();
extern void print_str(const char* str);
extern void print_int(int n);

/* --- SİSTEM TAMPONLARI --- */
char editor_buffer[2000];  
int edit_idx = 0;

/* --- GERÇEK DONANIM ERİŞİM FONKSİYONLARI (ASM) --- */

void get_cpu_vendor(char *vendor) {
    unsigned int ebx, ecx, edx;
    asm volatile("cpuid" : "=b"(ebx), "=c"(ecx), "=d"(edx) : "a"(0));
    *((unsigned int *)&vendor[0]) = ebx;
    *((unsigned int *)&vendor[4]) = edx;
    *((unsigned int *)&vendor[8]) = ecx;
    vendor[12] = '\0';
}

unsigned int get_cpu_features() {
    unsigned int edx;
    asm volatile("cpuid" : "=d"(edx) : "a"(1) : "ecx", "ebx");
    return edx;
}

/* CMOS'tan (RTC) Veri Okuma */
unsigned char read_cmos(unsigned char reg) {
    asm volatile ("outb %0, $0x70" : : "a"(reg));
    unsigned char val;
    asm volatile ("inb $0x71, %0" : "=a"(val));
    return val;
}

/* BCD formatını normal sayıya çevirme (Donanım saati BCD döner) */
unsigned int bcd_to_bin(unsigned char bcd) {
    return ((bcd / 16) * 10) + (bcd % 16);
}

/* --- YARDIMCI FONKSİYONLAR --- */
int str_match(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) return 0;
        i++;
    }
    return (s1[i] == s2[i]);
}

void print_hex(unsigned char n) {
    const char *hex = "0123456789ABCDEF";
    putchar(hex[(n >> 4) & 0x0F]);
    putchar(hex[n & 0x0F]);
}

/* --- 1. GERÇEK SİSTEM ANALİZ KOMUTLARI --- */

void command_status(const char* args) {
    unsigned int cr0;
    asm volatile("mov %%cr0, %0" : "=r"(cr0));
    print_str("\n[KERNEL RUNTIME STATE]");
    print_str("\nMode          : "); 
    if (cr0 & 1) print_str("Protected Mode (x86_32)");
    else print_str("Real Mode");
    print_str("\nPaging        : ");
    if (cr0 & 0x80000000) print_str("Enabled");
    else print_str("Disabled");
    print_str("\nMemory Model  : Flat Physical Mapping\n");
}

void command_cpuinfo(const char* args) {
    char vendor[13];
    get_cpu_vendor(vendor);
    unsigned int feat = get_cpu_features();
    print_str("\n[CPU HARDWARE ID]");
    print_str("\nVendor      : "); print_str(vendor);
    print_str("\nFeatures    : ");
    if (feat & (1 << 0))  print_str("FPU ");
    if (feat & (1 << 23)) print_str("MMX ");
    if (feat & (1 << 25)) print_str("SSE ");
    print_str("\nInstruction : i386-Compatible\n");
}

void command_memdump(const char* args) {
    print_str("\nMemory Dump (0x100000):\n");
    unsigned char* ptr = (unsigned char*)0x100000; 
    for(int i=0; i<64; i++) {
        print_hex(ptr[i]); print_str(" ");
        if((i+1) % 16 == 0) print_str("\n");
    }
}

/* --- 2. DOSYA SİSTEMİ ARAÇLARI --- */

void command_ls(const char* args) {
    print_str("\nINDEX  NAME             SIZE\n");
    for(int i=0; i<10; i++) {
        if(ram_disk[i].name[0] != '\0') {
            print_int(i); print_str("      ");
            print_str(ram_disk[i].name); print_str("    ");
            print_int(ram_disk[i].size); print_str(" B\n");
        }
    }
}

void command_cat(const char* args) {
    if(!args[0]) return;
    for(int i=0; i<10; i++) {
        if(str_match(args, ram_disk[i].name)) {
            print_str("\n"); print_str(ram_disk[i].content); print_str("\n");
            return;
        }
    }
}

void command_touch(const char* args) {
    if(!args[0]) return;
    for(int i=0; i<10; i++) {
        if(ram_disk[i].name[0] == '\0') {
            int k=0; while(args[k] && k<31) { ram_disk[i].name[k]=args[k]; k++; }
            ram_disk[i].name[k]='\0'; ram_disk[i].size = 0;
            print_str("\nFile created."); return;
        }
    }
}

void command_rm(const char* args) {
    if(!args[0]) return;
    for(int i=0; i<10; i++) {
        if(str_match(args, ram_disk[i].name)) {
            ram_disk[i].name[0] = '\0';
            print_str("\nUnlinked."); return;
        }
    }
}

/* --- 3. BLEX-VI EDİTÖR --- */

void command_edit(const char* args) {
    if(!args[0]) return;
    int target = -1;
    for(int i=0; i<10; i++) if(str_match(args, ram_disk[i].name)) target = i;
    if(target == -1) {
        command_touch(args);
        for(int i=0; i<10; i++) if(str_match(args, ram_disk[i].name)) target = i;
    }
    if(target == -1) return;
    clear_screen();
    print_str("EDIT: "); print_str(args); print_str(" | ESC to Save\n---\n");
    extern unsigned char kbd_us[128];
    int active = 1; edit_idx = 0;
    while(active) {
        if (inb(0x64) & 1) {
            unsigned char sc = inb(0x60);
            if (!(sc & 0x80)) {
                if (sc == 0x01) active = 0; 
                else if (sc == 0x1C) { cursor_x = 0; cursor_y++; editor_buffer[edit_idx++] = '\n'; putchar('\n'); }
                else if (sc == 0x0E && edit_idx > 0) { edit_idx--; putchar('\b'); }
                else { char c = kbd_us[sc]; if(c && edit_idx < 1999) { editor_buffer[edit_idx++] = c; putchar(c); } }
                update_cursor(cursor_x, cursor_y);
            }
        }
    }
    int i; for(i=0; i < edit_idx && i < 127; i++) ram_disk[target].content[i] = editor_buffer[i];
    ram_disk[target].content[i] = '\0'; ram_disk[target].size = edit_idx;
    clear_screen(); print_str("\nSaved.\n>> ");
}

/* --- 4. SİSTEM VE SHELL ARAÇLARI --- */

void command_date(const char* args) {
    unsigned int second = bcd_to_bin(read_cmos(0x00));
    unsigned int minute = bcd_to_bin(read_cmos(0x02));
    unsigned int hour   = bcd_to_bin(read_cmos(0x04));
    unsigned int day    = bcd_to_bin(read_cmos(0x07));
    unsigned int month  = bcd_to_bin(read_cmos(0x08));
    unsigned int year   = bcd_to_bin(read_cmos(0x09));

    print_str("\nRTC DATE: ");
    print_int(day); print_str("/"); print_int(month); print_str("/20"); print_int(year);
    print_str("\nRTC TIME: ");
    if(hour < 10) print_str("0"); print_int(hour); print_str(":");
    if(minute < 10) print_str("0"); print_int(minute); print_str(":");
    if(second < 10) print_str("0"); print_int(second);
    print_str(" UTC\n");
}

void command_uptime(const char* args) {
    unsigned int lo, hi;
    asm volatile ("rdtsc" : "=a"(lo), "=d"(hi));
    print_str("\nTSC: "); print_int(lo);
}

void command_uname(const char* args) {
    print_str("\nBlexxOS 0.0.3-i386");
}

void command_whoami(const char* args) {
    print_str("\nroot");
}

void command_clear(const char* args) {
    clear_screen();
}

void command_reboot(const char* args) {
    asm volatile ("outb %0, %1" : : "a"((unsigned char)0xFE), "Nd"(0x64));
}

void command_help(const char* args) {
    print_str("\nCommands: status, cpuinfo, memdump, uptime, ls, touch, cat, edit, rm, uname, whoami, clear, date, reboot");
}

/* --- 5. KOMUT TABLOSU --- */

command_t command_table[] = {
    {"help",     command_help,     ""},
    {"status",   command_status,   ""},
    {"cpuinfo",  command_cpuinfo,  ""},
    {"memdump",  command_memdump,  ""},
    {"uptime",   command_uptime,   ""},
    {"ls",       command_ls,       ""},
    {"touch",    command_touch,    ""},
    {"cat",      command_cat,      ""},
    {"edit",     command_edit,     ""},
    {"rm",       command_rm,       ""},
    {"uname",    command_uname,    ""},
    {"whoami",   command_whoami,   ""},
    {"clear",    command_clear,    ""},
    {"date",     command_date,     ""},
    {"reboot",   command_reboot,   ""}
};

int command_count = sizeof(command_table) / sizeof(command_t);
