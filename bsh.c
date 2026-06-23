/*
 * bsh.c – Blex SHell script interpreter
 *
 * Parses and executes BSH script files.
 * Shebang: "#!/ec/bsh"  (first line)
 * Lines starting with "//" are comments.
 * "wait(N)" pauses for N seconds (approximate).
 * All other lines are executed as shell commands.
 */

#include "bsh.h"
#include "kernel_utils.h"
#include "config/system.h"
#include "commands/commands.h"

/* ── Constants ──────────────────────────────────────────── */
#define BSH_MAX_LINE 256
#define TICKS_PER_SEC 3000   /* boot_ticks increment rate (Hz) – adjust if needed */

/* ── String helpers ─────────────────────────────────────── */
static int bsh_streq(const char *a, const char *b) {
    while (*a && *b) {
        if (*a++ != *b++) return 0;
    }
    return (*a == '\0' && *b == '\0');
}

static int bsh_strlen(const char *s) {
    int n = 0;
    while (s[n]) n++;
    return n;
}

static void bsh_strcpy(char *d, const char *s) {
    while (*s) *d++ = *s++;
    *d = '\0';
}

static int bsh_isdigit(char c) {
    return (c >= '0' && c <= '9');
}

/* ── Extract number from "wait(N)" ────────────────────── */
static int parse_wait_seconds(const char *line) {
    const char *p = line;
    while (*p && *p != '(') p++;
    if (*p != '(') return 0;
    p++; /* skip '(' */
    int val = 0;
    while (*p && bsh_isdigit(*p)) {
        val = val * 10 + (*p - '0');
        p++;
    }
    return val;
}

/* ── Busy‑wait with interrupt support (approximate seconds) ── */
static void bsh_wait(int seconds) {
    if (seconds <= 0) return;
    extern unsigned int boot_ticks;
    unsigned int target = boot_ticks + (unsigned int)(seconds * TICKS_PER_SEC);

    /* Enable interrupts so the timer can update boot_ticks */
    __asm__ volatile ("sti");

    while (boot_ticks < target) {
        /* Halt CPU until next interrupt (timer tick) */
        __asm__ volatile ("hlt");
        /* If HLT is not suitable, fallback to PAUSE: */
        // __asm__ volatile ("pause");
    }
}

/* ── Check if line starts with a prefix ────────────────── */
static int bsh_starts_with(const char *s, const char *prefix) {
    while (*prefix) {
        if (*s != *prefix) return 0;
        s++; prefix++;
    }
    return 1;
}

/* ── Execute a single line of script ───────────────────── */
static void bsh_run_line(const char *line) {
    if (!line || !line[0]) return;
    /* Skip blank lines (including CR) */
    if (line[0] == '\n' || line[0] == '\r') return;

    /* Skip comments (//) */
    if (bsh_starts_with(line, "//")) return;

    /* Handle wait(N) */
    if (bsh_starts_with(line, "wait(")) {
        int secs = parse_wait_seconds(line);
        print_str_color("BSH: waiting ", VGA_ATTR(COL_CYAN, COL_BLACK));
        print_int(secs);
        print_str(" seconds...\n");
        bsh_wait(secs);
        return;
    }

    /* Otherwise, execute as a shell command */
    char cmd[32];
    int i = 0;
    while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && i < 31) {
        cmd[i] = line[i];
        i++;
    }
    cmd[i] = '\0';

    /* Skip whitespace to get arguments */
    const char *args = line + i;
    while (*args == ' ' || *args == '\t') args++;
    /* If no arguments, pass empty string */
    if (!*args || *args == '\n' || *args == '\r') args = "";

    /* Look up command in global command table */
    extern command_t command_table[];
    extern int command_count;
    int found = 0;
    for (int k = 0; k < command_count; k++) {
        if (bsh_streq(cmd, command_table[k].name)) {
            print_str_color("BSH> ", VGA_ATTR(COL_CYAN, COL_BLACK));
            print_str(line);
            putchar('\n');

            /* Execute the command with arguments */
            command_table[k].func(args);
            found = 1;
            break;
        }
    }

    if (!found) {
        print_str_color("BSH: command not found: ", VGA_ATTR(COL_LRED, COL_BLACK));
        print_str(cmd);
        putchar('\n');
    }
}

/* ═════════════════════════════════════════════════════════
 *  Public API
 * ═════════════════════════════════════════════════════════ */

int bsh_detect(const char *data, uint32_t size) {
    if (!data || size < 8) return 0;
    /* Check shebang */
    for (int i = 0; BSH_SHEBANG[i]; i++) {
        if (data[i] != BSH_SHEBANG[i]) return 0;
    }
    return 1;
}

void bsh_exec(const char *data, uint32_t size) {
    if (!data || !bsh_detect(data, size)) {
        print_str_color("BSH: not a valid BSH script\n", VGA_ATTR(COL_LRED, COL_BLACK));
        return;
    }

    print_str_color("\n--- BSH script execution ---\n", VGA_ATTR(COL_LCYAN, COL_BLACK));

    /* Skip the shebang line (first line) */
    const char *p = data;
    while (*p && *p != '\n' && (uint32_t)(p - data) < size) p++;
    if (*p == '\n') p++; /* skip newline */

    const char *line_start = p;
    while (*line_start && (uint32_t)(line_start - data) < size) {
        const char *line_end = line_start;
        while (*line_end && *line_end != '\n' && *line_end != '\r' &&
               (uint32_t)(line_end - data) < size) {
            line_end++;
        }

        int line_len = (int)(line_end - line_start);
        if (line_len > 0) {
            char line_buf[BSH_MAX_LINE];
            int copy_len = (line_len < BSH_MAX_LINE - 1) ? line_len : BSH_MAX_LINE - 1;
            for (int i = 0; i < copy_len; i++) {
                line_buf[i] = line_start[i];
            }
            line_buf[copy_len] = '\0';
            bsh_run_line(line_buf);
        }

        /* Advance past the line ending */
        line_start = line_end;
        if (*line_start == '\n' || *line_start == '\r') {
            line_start++;
            /* Handle CRLF */
            if (*line_start == '\n' && *(line_start - 1) == '\r') {
                line_start++;
            }
        }
    }

    print_str_color("--- BSH script done ---\n\n", VGA_ATTR(COL_LCYAN, COL_BLACK));
}

int bsh_run_file(const char *path) {
    es1_node_t *node = es1_find(path);
    if (!node) {
        print_str_color("BSH: file not found: ", VGA_ATTR(COL_LRED, COL_BLACK));
        print_str(path); putchar('\n');
        return -1;
    }

    if (node->flags & ES1_FL_DIR) {
        print_str_color("BSH: is a directory\n", VGA_ATTR(COL_LRED, COL_BLACK));
        return -2;
    }

    const char *data = es1_get_data(node);
    uint32_t size = node->size;

    if (!bsh_detect(data, size)) {
        print_str_color("BSH: not a BSH script (missing shebang)\n", VGA_ATTR(COL_LRED, COL_BLACK));
        return -3;
    }

    bsh_exec(data, size);
    return 0;
}
