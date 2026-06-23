/*
 * config/sio.h – Serial I/O driver (16550 UART)
 * Copyright (C) 2026 Blex – BOSL License
 *
 * Provides buffered serial output over the standard COM port.
 * Boot logs are mirrored to serial for debugging on real hardware
 * or viewing in QEMU with `-serial stdio` or `-serial file:log.txt`.
 *
 * Serial configuration (default: COM1, 115200 8N1):
 *   SIO_COM1_BASE  0x3F8
 *   SIO_BAUD_DIV   1        → 115200 baud (with 1.8432 MHz clock)
 */

#ifndef CONFIG_SIO_H
#define CONFIG_SIO_H

#include <stdint.h>

/* ══════════════════════════════════════════════════════
 *  CONFIGURATION
 * ══════════════════════════════════════════════════════ */

/* COM port base addresses (PC standard) */
#define SIO_COM1_BASE  0x3F8
#define SIO_COM2_BASE  0x2F8
#define SIO_COM3_BASE  0x3E8
#define SIO_COM4_BASE  0x2E8

/* Default serial port to use */
#ifndef SIO_PORT_BASE
#define SIO_PORT_BASE  SIO_COM1_BASE
#endif

/* Baud rate divisor (DLL/DLM).  1 = 115200, 2 = 57600, 3 = 38400, … 12 = 9600 */
#ifndef SIO_BAUD_DIV
#define SIO_BAUD_DIV  1
#endif

/* ══════════════════════════════════════════════════════
 *  API
 * ══════════════════════════════════════════════════════ */

/* Initialise the serial port.  Must be called once before any sio_* usage. */
void sio_init(void);

/* Send a single character over serial.  Blocks until transmitter is ready. */
void sio_putchar(char c);

/* Send a null-terminated string over serial. */
void sio_puts(const char *s);

/* Return non-zero if a character is available to read (no blocking). */
int  sio_data_available(void);

/* Read a single character from serial (non-blocking, returns -1 if none). */
int  sio_getchar(void);

/* Return non-zero if the serial port was successfully initialised. */
int  sio_is_present(void);

#endif /* CONFIG_SIO_H */
