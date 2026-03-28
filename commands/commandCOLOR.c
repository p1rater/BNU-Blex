#include "../kernel_utils.h"
extern char current_color; // kernel.c'deki değişkene dışarıdan erişim

void command_color() {
    current_color++; 
    if(current_color > 0x0F) current_color = 0x01;
    print_str("\nText color updated!");
}
