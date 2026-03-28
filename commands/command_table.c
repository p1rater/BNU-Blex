#include "commands.h"
#include "../kernel_utils.h"

extern vfs_node_t ram_disk[3];
extern unsigned int system_ticks;

int str_match(const char* s1, const char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) return 0;
        i++;
    }
    return (s1[i] == s2[i]);
}

void command_fetch(const char* args) {
    print_str("\n");
    print_str("__________  .__                        \n");
    print_str("\\______   \\ |  |   ____ ___  ______  ___\n");
    print_str(" |    |  _/ |  | _/ __ \\\\  \\/  /\\  \\/  /\n");
    print_str(" |    |   \\ |  |_\\  ___/ >    <  >    < \n");
    print_str(" |______  / |____/\\___  >__/\\_ \\/__/\\_ \\\n");
    print_str("        \\/            \\/      \\/      \\/\n");
    print_str("\n OS: BlexxOS v0.0.2.5");
    print_str("\n Kernel: x86_32");
    print_str("\n Shell: blexx-sh");
    print_str("\n Uptime: ");
    
    // Basit bir saniye tahmini
    int uptime_secs = system_ticks / 1000000;
    if (uptime_secs < 1) {
        print_str("just booted");
    } else {
        print_str("stable");
    }
    
    print_str("\n Memory: 128KB / 4MB (VFS)");
    print_str("\n Status: Active");
}

void command_help(const char* args) {
    print_str("\nCommands: fetch, ls, cat, uname, clear, reboot, shutdown, uptime");
}

void command_ls(const char* args) {
    print_str("\nListing VFS:");
    for(int i=0; i<3; i++) { print_str("\n - "); print_str(ram_disk[i].name); }
}

void command_cat(const char* args) {
    for(int i=0; i<3; i++) {
        if(str_match(args, ram_disk[i].name)) {
            print_str("\n"); print_str(ram_disk[i].content); return;
        }
    }
    print_str("\nFile not found.");
}

void command_uname(const char* args) { print_str("\nblexx-0.0.1"); }
void command_clear(const char* args) { clear_screen(); }
void command_reboot(const char* args) { asm volatile ("outb %0, %1" : : "a"((unsigned char)0xFE), "Nd"(0x64)); }
void command_shutdown(const char* args) { asm volatile ("outw %0, %1" : : "a"((unsigned short)0x2000), "Nd"((unsigned short)0x604)); }

command_t command_table[] = {
    {"help", command_help, ""}, {"ls", command_ls, ""}, {"cat", command_cat, ""},
    {"uname", command_uname, ""}, {"clear", command_clear, ""}, {"reboot", command_reboot, ""},
    {"shutdown", command_shutdown, ""}, {"fetch", command_fetch, ""},
    {"uptime", command_fetch, ""}, {"k", command_clear, ""}, {"u", command_uname, ""}, {"cls", command_clear, ""}
};

int command_count = sizeof(command_table) / sizeof(command_t);
