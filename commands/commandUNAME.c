#include "../kernel_utils.h"

int str_cmp(const char* s1, const char* s2) {
    while (*s1 && (*s1 == *s2)) { s1++; s2++; }
    return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

void command_uname(const char* args) {
    if (str_cmp(args, "-r") == 0) {
        print_str("\nblexx-0.0.1");
    } else if (str_cmp(args, "-a") == 0) {
        print_str("\nBlexxOS blexx-0.0.1 x86_32");
    } else {
        print_str("\nblexx-0.0.1");
    }
}
