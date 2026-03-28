#include "../kernel_utils.h"
void command_reboot(const char* args) {
    print_str("\nRebooting...");
    // x86 Klavye kontrolcüsü üzerinden reset sinyali
    unsigned char good = 0x02;
    while (good & 0x02) {
        asm volatile ("inb %1, %0" : "=a"(good) : "Nd"(0x64));
    }
    asm volatile ("outb %0, %1" : : "a"((unsigned char)0xFE), "Nd"(0x64));
}
