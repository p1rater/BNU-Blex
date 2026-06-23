#ifndef LOGO_DISPLAY_H
#define LOGO_DISPLAY_H

#include <stdint.h>

/* ── Log levels (Linux-compatible) ───────────────────── */
#define LOG_EMERG   0
#define LOG_ALERT   1
#define LOG_CRIT    2
#define LOG_ERR     3
#define LOG_WARN    4
#define LOG_NOTICE  5
#define LOG_INFO    6
#define LOG_DEBUG   7
#define LOG_TRACE   8

/* ── Log level names ─────────────────────────────────── */
extern const char *log_level_names[9];

/* ── Current log level (settable) ────────────────────── */
extern int current_log_level;
extern int log_to_serial;
extern int show_boot_logo;
extern int logo_duration_secs;

/* ── Initialize log system from config file ──────────── */
void log_init_from_cfg(void);

/* ── Log a message with level ────────────────────────── */
void boot_log(int level, const char *tag, const char *msg);
void boot_log_fmt(int level, const char *tag, const char *fmt, int val);

/* ── PPM logo display ───────────────────────────────── */
int  logo_display_ppm(void);
int  logo_clear(void);
void logo_wait_and_clear(int seconds);

/* ── Bootlog streaming area management ───────────────── */
/* Partition the screen: logo at top, logs below         */
#define LOGO_TOP         4
#define LOGO_LEFT        8
#define LOGO_AREA_Y      LOGO_TOP        /* PPM top edge */
#define LOGO_AREA_H      130             /* height reserved for logo + padding */
#define LOG_TEXT_TOP     (LOGO_AREA_H + 10)  /* first log text row */
#define LOG_TEXT_LEFT    8

/* ── DMESG ring buffer ─────────────────────────────── */
#define DMESG_BUF_LINES   128
extern char dmesg_buffer[DMESG_BUF_LINES][128];
extern int  dmesg_count;

/* ── Save boot message to dmesg buffer ─────────────── */
void dmesg_write(const char *tag, const char *msg);

#endif /* LOGO_DISPLAY_H */
