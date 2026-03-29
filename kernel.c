#include "kernel_utils.h"
#include "commands/commands.h"

#define VIDEO_BUF ((char*)0xB8000)
#define MAX_COLS 80
#define MAX_ROWS 25

typedef struct {
    unsigned int flags;
    unsigned int mem_lower;
    unsigned int mem_upper; 
    unsigned int boot_device;
    unsigned int cmdline;
} multiboot_info_t;

/* --- DIŞ REFERANSLAR --- */
extern int str_match(const char* s1, const char* s2);
extern command_t command_table[];
extern int command_count;

/* --- GLOBAL DEĞİŞKENLER --- */
vfs_node_t ram_disk[32];
char current_user[16] = "root";
unsigned int boot_ticks = 0;   
int cursor_x = 0; 
int cursor_y = 0;
char current_color = 0x0F;

char shell_buffer[81];
int buf_idx = 0;   

/* --- DONANIM FONKSİYONLARI --- */
unsigned char inb(unsigned short port) {
    unsigned char ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void outb(unsigned short port, unsigned char val) {
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

void update_cursor(int x, int y) {
    unsigned short pos = y * MAX_COLS + x;
    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char)((pos >> 8) & 0xFF));
}

/* --- GUI ÇİZİM ARAÇLARI --- */
void draw_box(int x, int y, int w, int h, char color, char fill_char) {
    for (int i = y; i < y + h; i++) {
        for (int j = x; j < x + w; j++) {
            if (i >= 0 && i < MAX_ROWS && j >= 0 && j < MAX_COLS) {
                int offset = (i * MAX_COLS + j) * 2;
                VIDEO_BUF[offset] = fill_char;
                VIDEO_BUF[offset + 1] = color;
            }
        }
    }
}

void draw_kolibri_window(int x, int y, int w, int h, const char* title) {
    draw_box(x, y, w, h, 0x70, ' ');      // Gövde (Gri)
    draw_box(x, y, w, 1, 0x1F, ' ');      // Başlık (Mavi)
    
    int sx = cursor_x; int sy = cursor_y;
    cursor_x = x + 1; cursor_y = y;
    print_str(title);
    
    int close_off = (y * MAX_COLS + (x + w - 2)) * 2;
    VIDEO_BUF[close_off] = 'X';
    VIDEO_BUF[close_off + 1] = 0x4F;     // Kapat butonu (Kırmızı)
    
    cursor_x = sx; cursor_y = sy;
}

/* --- EKRAN ÇIKTILARI --- */
void putchar(char c) {
    if (c == '\n') { cursor_x = 0; cursor_y++; }
    else if (c == '\b') {
        if (cursor_x > 3) {
            cursor_x--;
            int offset = (cursor_y * MAX_COLS + cursor_x) * 2;
            VIDEO_BUF[offset] = ' ';
            VIDEO_BUF[offset + 1] = current_color;
        }
    } else {
        int offset = (cursor_y * MAX_COLS + cursor_x) * 2;
        VIDEO_BUF[offset] = c;
        VIDEO_BUF[offset + 1] = current_color;
        cursor_x++;
    }
    if (cursor_x >= MAX_COLS) { cursor_x = 0; cursor_y++; }
    if (cursor_y >= MAX_ROWS) {
        for (int i = 0; i < (MAX_ROWS - 1) * MAX_COLS * 2; i++)
            VIDEO_BUF[i] = VIDEO_BUF[i + MAX_COLS * 2];
        for (int i = (MAX_ROWS - 1) * MAX_COLS * 2; i < MAX_ROWS * MAX_COLS * 2; i += 2) {
            VIDEO_BUF[i] = ' '; VIDEO_BUF[i+1] = 0x07;
        }
        cursor_y = MAX_ROWS - 1;
    }
    update_cursor(cursor_x, cursor_y);
}

void print_str(const char* str) { for (int i = 0; str[i] != '\0'; i++) putchar(str[i]); }

void print_int(int n) {
    if (n == 0) { putchar('0'); return; }
    char buf[12]; int i = 10; buf[11] = '\0';
    while (n > 0 && i >= 0) { buf[i--] = (n % 10) + '0'; n /= 10; }
    print_str(&buf[i+1]);
}

void clear_screen() {
    for (int i = 0; i < MAX_COLS * MAX_ROWS * 2; i += 2) {
        VIDEO_BUF[i] = ' '; VIDEO_BUF[i+1] = 0x07;
    }
    cursor_x = 0; cursor_y = 0; update_cursor(0, 0);
}

/* --- KABUK --- */
void process_command() {
    shell_buffer[buf_idx] = '\0';
    putchar('\n');
    if (buf_idx > 0) {
        char cmd_name[32]; int i = 0;
        while (shell_buffer[i] != ' ' && shell_buffer[i] != '\0' && i < 31) {
            cmd_name[i] = shell_buffer[i]; i++;
        }
        cmd_name[i] = '\0';
        char* args = (shell_buffer[i] == ' ') ? &shell_buffer[i+1] : "";
        int found = 0;
        for (int k = 0; k < command_count; k++) {
            if (str_match(cmd_name, command_table[k].name)) {
                command_table[k].func(args); found = 1; break;
            }
        }
        if (!found) { print_str("Unknown: "); print_str(cmd_name); putchar('\n'); }
    }
    print_str(">> "); buf_idx = 0;
}

unsigned char kbd_us[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
    'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\',
    'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' '
};

void kernel_main(unsigned int magic, multiboot_info_t* mbi) {
    clear_screen();
    for(int i = 0; i < 32; i++) ram_disk[i].name[0] = '\0';
    print_str("Blexx-OS v0.0.5\n>> ");
    while (1) {
        boot_ticks++; 
        if (inb(0x64) & 1) {
            unsigned char scancode = inb(0x60);
            if (!(scancode & 0x80)) { 
                char c = kbd_us[scancode];
                if (c == '\n') process_command();
                else if (c == '\b' && buf_idx > 0) { buf_idx--; putchar('\b'); }
                else if (c && buf_idx < 79) { shell_buffer[buf_idx++] = c; putchar(c); }
            }
        }
    }
}