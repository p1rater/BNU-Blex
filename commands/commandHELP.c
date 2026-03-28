#include "../kernel_utils.h"
#include "commands.h"
void command_help(const char* args) {
    print_str("\nAvailable commands: ls, reboot, help, clear, color, uname");
}
