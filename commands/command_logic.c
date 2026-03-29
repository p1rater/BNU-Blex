#include "commands.h"

/* --- KERNEL REFERANSLARI --- */
extern vfs_node_t ram_disk[32];
extern char current_user[16];
extern unsigned int boot_ticks;
extern int cursor_x, cursor_y;
extern char current_color;

extern void putchar(char c);
extern void clear_screen();
extern void print_str(const char* str);
extern void print_int(int n);
extern void update_cursor(int x, int y);
extern unsigned char inb(unsigned short port);
extern void outb(unsigned short port, unsigned char val);

/* --- KERNEL ÇİZİM REFERANSLARI --- */
extern void draw_box(int x, int y, int w, int h, char color, char fill_char);
extern void draw_kolibri_window(int x, int y, int w, int h, const char* title);

/* --- YARDIMCI FONKSİYONLAR --- */

unsigned char read_rtc(unsigned char reg) {
    outb(0x70, reg);
    return inb(0x71);
}

unsigned char bcd_to_bin(unsigned char bcd) {
    return (bcd & 0x0F) + ((bcd >> 4) * 10);
}

int str_match(const char* s1, const char* s2) {
    if (!s1 || !s2) return 0;
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) return 0;
        i++;
    }
    return (s1[i] == '\0' && s2[i] == '\0');
}

void kernel_panic(const char* error_code, const char* description) {
    current_color = 0x4F;
    clear_screen();
    print_str("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    print_str("!!              KERNEL PANIC                  !!\n");
    print_str("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n");
    print_str("STOP: "); print_str(error_code); print_str("\n");
    print_str("MSG : "); print_str(description); print_str("\n");
    asm volatile ("cli");
    while(1) { asm volatile ("hlt"); }
}

/* --- DOSYA SİSTEMİ KOMUTLARI --- */

void command_ls(const char* args) {
    print_str("\nType  Name\n----------");
    for(int i=0; i<32; i++) {
        if(ram_disk[i].name[0] != '\0') {
            print_str("\n");
            print_str(ram_disk[i].is_directory ? "[DIR] " : "[FIL] ");
            print_str(ram_disk[i].name);
        }
    }
    print_str("\n");
}

void command_mkdir(const char* args) {
    if(!args[0]) { print_str("\nUsage: mkdir <name>\n"); return; }
    for(int i=0; i<32; i++) {
        if(ram_disk[i].name[0] == '\0') {
            int k=0; while(args[k] && args[k] != ' ' && k < 31) { ram_disk[i].name[k]=args[k]; k++; }
            ram_disk[i].name[k] = '\0';
            ram_disk[i].is_directory = 1;
            print_str("\nDirectory created.\n"); return;
        }
    }
}

void command_touch(const char* args) {
    if(!args[0]) { print_str("\nUsage: touch <name>\n"); return; }
    for(int i=0; i<32; i++) {
        if(ram_disk[i].name[0] == '\0') {
            int k=0; while(args[k] && args[k] != ' ' && k < 31) { ram_disk[i].name[k]=args[k]; k++; }
            ram_disk[i].name[k] = '\0';
            ram_disk[i].is_directory = 0;
            ram_disk[i].size = 0;
            ram_disk[i].content[0] = '\0';
            print_str("\nFile created.\n"); return;
        }
    }
}

void command_rm(const char* args) {
    if(!args[0]) { print_str("\nUsage: rm <name>\n"); return; }
    for(int i=0; i<32; i++) {
        if(str_match(args, ram_disk[i].name)) {
            ram_disk[i].name[0] = '\0';
            print_str("\nDeleted.\n"); return;
        }
    }
}

void command_cat(const char* args) {
    if(!args[0]) { print_str("\nUsage: cat <name>\n"); return; }
    for(int i=0; i<32; i++) {
        if(str_match(args, ram_disk[i].name)) {
            print_str("\n"); print_str(ram_disk[i].content); print_str("\n");
            return;
        }
    }
    print_str("\nFile not found.\n");
}

void command_nano(const char* args) {
    if(!args[0]) { print_str("\nUsage: nano <name>\n"); return; }
    int target = -1;
    for(int i=0; i<32; i++) if(str_match(args, ram_disk[i].name)) target = i;
    if(target == -1) {
        for(int i=0; i<32; i++) {
            if(ram_disk[i].name[0] == '\0') {
                target = i;
                int k=0; while(args[k] && args[k] != ' ' && k < 31) { ram_disk[target].name[k]=args[k]; k++; }
                ram_disk[target].name[k] = '\0'; ram_disk[target].is_directory = 0;
                ram_disk[target].size = 0; ram_disk[target].content[0] = '\0';
                break;
            }
        }
    }
    if(target == -1) return;
    clear_screen();
    current_color = 0x70; for(int i=0; i<80; i++) putchar(' '); 
    cursor_x = 1; cursor_y = 0; print_str("NANO Editor - "); print_str(ram_disk[target].name);
    current_color = 0x0F; cursor_x = 0; cursor_y = 2; print_str(ram_disk[target].content);
    cursor_y = 24; cursor_x = 0; current_color = 0x70;
    print_str(" [F1] Save & Exit    [ESC] Panic                                       ");
    current_color = 0x0F; cursor_x = 0; cursor_y = 2; update_cursor(cursor_x, cursor_y);
    int editing = 1; int idx = ram_disk[target].size;
    extern unsigned char kbd_us[128];
    while(editing) {
        if (inb(0x64) & 1) {
            unsigned char sc = inb(0x60);
            if (!(sc & 0x80)) {
                if (sc == 0x3B) editing = 0; 
                else if (sc == 0x01) kernel_panic("0xDEAD", "Nano Exit");
                else if (sc == 0x1C) { ram_disk[target].content[idx++] = '\n'; putchar('\n'); }
                else if (sc == 0x0E && idx > 0) { idx--; putchar('\b'); }
                else { char c = kbd_us[sc]; if(c && idx < 510) { ram_disk[target].content[idx++] = c; putchar(c); } }
            }
        }
    }
    ram_disk[target].size = idx; ram_disk[target].content[idx] = '\0';
    clear_screen(); print_str("Saved.\n>> ");
}

/* --- EXPERIMENTAL GUI KOMUTU (KOLIBRI STYLE) --- */

void command_gui(const char* args) {
    // 1. Önceki Enter tuşunu ve tamponu temizle
    while (inb(0x64) & 1) { inb(0x60); }

    // 2. Ekranı temizle ve masaüstü arkaplanını yap (Mavi: 0x1F)
    draw_box(0, 0, 80, 25, 0x1F, ' ');
    
    // 3. Ana Uygulama Penceresini Çiz
    draw_kolibri_window(15, 5, 50, 12, " Blexx-OS Experimental GUI ");
    
    // 4. Pencere İçine Bilgileri Yaz
    int saved_x = cursor_x; int saved_y = cursor_y;
    char saved_color = current_color;

    current_color = 0x70; // Gri arkaplan üzerine siyah yazı
    cursor_x = 17; cursor_y = 7; print_str("Welcome to Blexx-OS GUI!");
    cursor_x = 17; cursor_y = 8; print_str("----------------------------");
    cursor_x = 17; cursor_y = 9; print_str("Kernel: i386-stable");
    cursor_x = 17; cursor_y = 10; print_str("Uptime: "); print_int(boot_ticks / 100); print_str("s");
    cursor_x = 17; cursor_y = 11; print_str("User  : "); print_str(current_user);
    
    cursor_x = 17; cursor_y = 15;
    current_color = 0x1F; // Mavi arka plan üzerine beyaz yazı
    print_str("PRESS [ESC] TO RETURN TO SHELL");

    // 5. Alt Görev Çubuğu (Gri: 0x70)
    draw_box(0, 24, 80, 1, 0x70, ' ');
    cursor_x = 1; cursor_y = 24;
    print_str("[Start] [Files] [Terminal]                   12:00");

    // 6. DÖNGÜ: ESC tuşu basılana kadar bekle
    int in_gui = 1;
    while(in_gui) {
        if (inb(0x64) & 1) {
            unsigned char scancode = inb(0x60);
            if (scancode == 0x01) { // 0x01 ESC scancode'udur
                in_gui = 0;
            }
        }
        // CPU'yu %100 kullanmamak için çok kısa bir bekleme
        for(int i = 0; i < 2000; i++) { asm volatile("nop"); }
    }

    // 7. Eski haline dön
    cursor_x = saved_x; cursor_y = saved_y;
    current_color = saved_color;
    clear_screen();
    print_str("Exited GUI mode.\n>> ");
}

/* --- SİSTEM KOMUTLARI --- */

void command_date(const char* args) {
    unsigned char h = bcd_to_bin(read_rtc(0x04));
    unsigned char m = bcd_to_bin(read_rtc(0x02));
    unsigned char s = bcd_to_bin(read_rtc(0x00));
    print_str("\nDate: "); 
    if(h < 10) putchar('0'); print_int(h); putchar(':');
    if(m < 10) putchar('0'); print_int(m); putchar(':');
    if(s < 10) putchar('0'); print_int(s); print_str("\n");
}

void command_uptime(const char* args) {
    print_str("\nUptime: "); print_int(boot_ticks / 100); print_str("s\n");
}

void command_whoami(const char* args) {
    print_str("\nUser: "); print_str(current_user); print_str("\n");
}

void command_uname(const char* args) {
    print_str("\nBlexx-OS 0.0.5 i386-stable\n");
}

void command_free(const char* args) {
    print_str("\nRAM: 32MB Total / 28MB Free\n");
}

void command_fetch(const char* args) {
    print_str("\n Blexx-OS v0.0.5\n Kernel: i386-stable\n User: root\n");
}

void command_help(const char* args) {
    print_str("\nFiles: ls, mkdir, rm, touch, cat, nano");
    print_str("\nSys: date, uptime, whoami, uname, free, fetch, clear, gui");
    print_str("\nAdm: panic, reboot\n");
}

void command_clear(const char* args) { clear_screen(); }
void command_reboot(const char* args) { outb(0x64, 0xFE); }
void command_panic(const char* args) { kernel_panic("0xMANUAL", "User triggered"); }

/* --- KOMUT TABLOSU --- */
command_t command_table[] = {
    {"help",    command_help},   {"ls",      command_ls},
    {"mkdir",   command_mkdir},  {"rm",      command_rm},
    {"touch",   command_touch},  {"cat",     command_cat},
    {"nano",    command_nano},   {"date",    command_date},
    {"uptime",  command_uptime}, {"whoami",  command_whoami},
    {"uname",   command_uname},  {"free",    command_free},
    {"fetch",   command_fetch},  {"clear",   command_clear},
    {"panic",   command_panic},  {"reboot",  command_reboot},
    {"gui",     command_gui}     
};

int command_count = 17;