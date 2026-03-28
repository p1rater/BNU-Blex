#include "kernel_utils.h"
#include "commands/commands.h"

#define VIDEO_BUF ((char*)0xB8000)

/* Fonksiyonu derleyiciye onceden tanitalim (Prototip) */
extern int str_match(const char* s1, const char* s2);

/* --- GLOBAL DEGISKENLER --- */
int cursor_x = 0; int cursor_y = 0;
char current_color = 0x0F;
char shell_buffer[80];
char cmd_name[80];
char args[80];
int buf_idx = 0;

/* --- HISTORY & UPTIME --- */
char history[5][80]; 
int history_count = 0;
int history_index = -1;
unsigned int system_ticks = 0;

/* --- VFS RAM DISK --- */
vfs_node_t ram_disk[3] = {
    {"readme.txt", "BlexxOS v0.0.2.5 - Power User Edition", 38},
    {"version.txt", "blexx-0.0.2.5", 13},
    {"author.txt", "bad@archlinux", 13}
};

unsigned char kbd_us[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0,  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',   0,
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0, '*',
    0, ' ', 0
};

unsigned char inb(unsigned short port) {
    unsigned char ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void clear_screen() {
    for(int i = 0; i < 80 * 25 * 2; i += 2) { VIDEO_BUF[i] = ' '; VIDEO_BUF[i+1] = 0x07; }
    cursor_x = 0; cursor_y = 0;
}

void putchar(char c) {
    if (c == '\n') { cursor_x = 0; cursor_y++; }
    else if (c == '\b') { 
        if (cursor_x > 0) {
            cursor_x--;
            VIDEO_BUF[(cursor_y * 80 + cursor_x) * 2] = ' ';
        }
    } else {
        int offset = (cursor_y * 80 + cursor_x) * 2;
        VIDEO_BUF[offset] = c;
        VIDEO_BUF[offset + 1] = current_color;
        cursor_x++;
    }
}

void print_str(const char* str) { for(int i = 0; str[i] != '\0'; i++) putchar(str[i]); }

void load_history(int idx) {
    while(buf_idx > 0) { buf_idx--; putchar('\b'); }
    int i = 0;
    while(history[idx][i] != '\0') {
        shell_buffer[buf_idx++] = history[idx][i];
        putchar(history[idx][i]);
        i++;
    }
}

void process_command() {
    shell_buffer[buf_idx] = '\0';
    if (buf_idx == 0) { print_str("\n>> "); return; }

    for(int i=4; i>0; i--) { 
        for(int j=0; j<80; j++) history[i][j] = history[i-1][j];
    }
    for(int j=0; j<80; j++) history[0][j] = shell_buffer[j];
    if(history_count < 5) history_count++;
    history_index = -1;

    for(int k=0; k<80; k++) { cmd_name[k] = 0; args[k] = 0; }
    int i = 0, j = 0;
    while (shell_buffer[i] != ' ' && shell_buffer[i] != '\0') {
        cmd_name[i] = shell_buffer[i]; i++;
    }
    cmd_name[i] = '\0';
    if (shell_buffer[i] == ' ') {
        i++;
        while (shell_buffer[i] != '\0') args[j++] = shell_buffer[i++];
    }
    args[j] = '\0';

    for (int k = 0; k < command_count; k++) {
        /* str_empty_compare yerine artik str_match kullaniyoruz */
        if (str_match(cmd_name, command_table[k].name)) {
            command_table[k].func(args);
            print_str("\n>> ");
            buf_idx = 0;
            return;
        }
    }
    print_str("\nUnknown command\n>> ");
    buf_idx = 0;
}

void kernel_main() {
    clear_screen();
    print_str("Blexx OS v0.0.2.5 - History & Uptime Fixed.\n>> ");
    while(1) {
        system_ticks++;
        if (inb(0x64) & 1) {
            unsigned char sc = inb(0x60);
            if (!(sc & 0x80)) {
                if (sc == 0x48) { // YUKARI OK
                    if(history_index < history_count - 1) {
                        history_index++;
                        load_history(history_index);
                    }
                } else if (sc == 0x50) { // ASAGI OK
                    if(history_index > 0) {
                        history_index--;
                        load_history(history_index);
                    }
                } else {
                    char c = kbd_us[sc];
                    if (c == '\n') process_command();
                    else if (c == '\b' && buf_idx > 0) { buf_idx--; putchar('\b'); }
                    else if (c && c != '\b' && buf_idx < 79) { 
                        shell_buffer[buf_idx++] = c; putchar(c); 
                    }
                }
            }
        }
    }
}
