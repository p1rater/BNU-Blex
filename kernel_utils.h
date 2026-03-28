#ifndef KERNEL_UTILS_H
#define KERNEL_UTILS_H

void print_str(const char* str);
void putchar(char c);
void clear_screen();

typedef struct {
    char name[32];
    char content[128];
    int size;
} vfs_node_t;

#endif
