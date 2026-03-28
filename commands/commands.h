#ifndef COMMANDS_H
#define COMMANDS_H

typedef void (*command_func_t)(const char* args);

typedef struct {
    const char* name;
    command_func_t func;
    const char* help;
} command_t;

extern command_t command_table[];
extern int command_count;

/* Tum komutlarin imzasi */
void command_help(const char* args);
void command_ls(const char* args);
void command_reboot(const char* args);
void command_clear(const char* args);
void command_color(const char* args);
void command_uname(const char* args);
void command_shutdown(const char* args);
void command_cat(const char* args);

#endif
