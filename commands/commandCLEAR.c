#include "../kernel_utils.h"
extern void clear_screen(); // kernel.c'deki fonksiyona dışarıdan erişim

void command_clear() {
    clear_screen();
}
