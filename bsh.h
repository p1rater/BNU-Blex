/*
 * bsh.h – Blex SHell script interpreter
 * Copyright (C) 2026 Blex – BOSL License
 *
 * BSH files start with shebang "#!/ec/bsh" and contain shell
 * commands, one per line.  Supports:
 *   - All built-in shell commands (ls, cd, cat, echo, ...)
 *   - wait(N) – pause for N seconds
 *   - // comments
 *   - Empty/skip lines
 */
#ifndef BSH_H
#define BSH_H

#include <stdint.h>

/* Maximum line length in a BSH script */
#define BSH_MAX_LINE   64

/* Maximum number of lines in a BSH script */
#define BSH_MAX_LINES  128

/* BSH shebang line */
#define BSH_SHEBANG    "#!/ec/bsh"

/*
 * bsh_detect - check if file data starts with the BSH shebang.
 * Returns 1 if yes, 0 otherwise.
 */
int  bsh_detect(const char *data, uint32_t size);

/*
 * bsh_exec - execute a BSH script from memory.
 * Parses each line, strips comments, handles wait(N),
 * and runs commands through the shell.
 */
void bsh_exec(const char *data, uint32_t size);

/*
 * bsh_run_file - load a file from ES1 and run it as a BSH script.
 * Returns 0 on success, negative on error.
 */
int  bsh_run_file(const char *path);

#endif /* BSH_H */
