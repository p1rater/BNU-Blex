/*
 * config/sio.c – Serial I/O driver (16550 UART) implementation
 * Copyright (C) 2026 Blex – BOSL License
 *
 * Uses the port I/O helpers declared in kernel_utils.h (inb/outb).
 * COM1 at 0x3F8, 115200 baud, 8 data bits, no parity, 1 stop bit.
 */

#include "sio.h"
#include "../../kernel_utils.h"

/* ── 16550 UART register offsets (from port base) ──── */
#define SIO_REG_DATA      0   /* R/W: data byte                 */
#define SIO_REG_IER       1   /* W:   interrupt enable           */
#define SIO_REG_IIR       2   /* R:   interrupt identification   */
#define SIO_REG_FCR       2   /* W:   FIFO control               */
#define SIO_REG_LCR       3   /* W:   line control               */
#define SIO_REG_MCR       4   /* W:   modem control              */
#define SIO_REG_LSR       5   /* R:   line status               */
#define SIO_REG_MSR       6   /* R:   modem status              */

/* Line status register bits */
#define SIO_LSR_TX_READY  0x20 /* Transmitter holding register empty */

/* Line control register values */
#define SIO_LCR_8N1       0x03 /* 8 data bits, no parity, 1 stop */
#define SIO_LCR_DLAB      0x80 /* Divisor latch access bit       */

/* FIFO control register */
#define SIO_FCR_ENABLE    0x01 /* Enable FIFOs */
#define SIO_FCR_RX_RESET  0x02 /* Reset receive FIFO */
#define SIO_FCR_TX_RESET  0x04 /* Reset transmit FIFO */
#define SIO_FCR_TRIGGER_14 0xC0 /* Trigger at 14 bytes */

/* ── Port base (configurable) ──────────────────────────── */
static uint16_t sio_base = 0;
static int      sio_ok   = 0;

/* ══════════════════════════════════════════════════════
 *  PUBLIC: sio_init
 * ══════════════════════════════════════════════════════ */
void sio_init(void) {
    sio_base = (uint16_t)SIO_PORT_BASE;

    /* Try to detect the UART by writing and reading back the FCR.
     * On a real 16550, writing 0x07 to FCR and reading back should
     * keep the lower 3 bits.  If no UART is present, reads return 0xFF. */

    outb(sio_base + SIO_REG_FCR, 0x07);
    uint8_t fcr_check = inb(sio_base + SIO_REG_FCR);

    /* If no device responds, we read 0xFF (floating bus) */
    if (fcr_check == 0xFF || fcr_check == 0x00) {
        sio_base = 0;
        sio_ok   = 0;
        return;
    }

    /* Disable interrupts */
    outb(sio_base + SIO_REG_IER, 0x00);

    /* Enable FIFOs, clear them, set 14-byte threshold */
    outb(sio_base + SIO_REG_FCR, SIO_FCR_ENABLE | SIO_FCR_RX_RESET |
                                  SIO_FCR_TX_RESET | SIO_FCR_TRIGGER_14);

    /* Set baud rate: DLAB on, set divisor, DLAB off */
    outb(sio_base + SIO_REG_LCR, SIO_LCR_DLAB);
    outb(sio_base + SIO_REG_DATA, (uint8_t)(SIO_BAUD_DIV & 0xFF));        /* DLL */
    outb(sio_base + SIO_REG_IER, (uint8_t)((SIO_BAUD_DIV >> 8) & 0xFF)); /* DLM */
    outb(sio_base + SIO_REG_LCR, SIO_LCR_8N1);

    /* Set DTR + RTS (modem control) so the other side knows we're alive */
    outb(sio_base + SIO_REG_MCR, 0x03);

    sio_ok = 1;
}

/* ══════════════════════════════════════════════════════
 *  PUBLIC: sio_is_present
 * ══════════════════════════════════════════════════════ */
int sio_is_present(void) {
    return sio_ok;
}

/* ══════════════════════════════════════════════════════
 *  PUBLIC: sio_putchar
 * ══════════════════════════════════════════════════════ */
void sio_putchar(char c) {
    if (!sio_base || !sio_ok) return;

    /* Convert LF to CR+LF for proper terminal behaviour */
    if (c == '\n') {
        sio_putchar('\r');
    }

    /* Wait for transmitter holding register to be empty */
    for (volatile int wait = 0; wait < 0x10000; wait++) {
        if (inb(sio_base + SIO_REG_LSR) & SIO_LSR_TX_READY)
            break;
    }

    outb(sio_base + SIO_REG_DATA, (uint8_t)c);
}

/* ══════════════════════════════════════════════════════
 *  PUBLIC: sio_data_available
 * ══════════════════════════════════════════════════════ */
int sio_data_available(void) {
    if (!sio_base || !sio_ok) return 0;
    /* LSR bit 0 = receiver data ready */
    return (inb(sio_base + SIO_REG_LSR) & 0x01) ? 1 : 0;
}

/* ══════════════════════════════════════════════════════
 *  PUBLIC: sio_getchar
 * ══════════════════════════════════════════════════════ */
int sio_getchar(void) {
    if (!sio_base || !sio_ok) return -1;
    if (!sio_data_available()) return -1;
    return (int)(unsigned char)inb(sio_base + SIO_REG_DATA);
}

/* ══════════════════════════════════════════════════════
 *  PUBLIC: sio_puts
 * ══════════════════════════════════════════════════════ */
void sio_puts(const char *s) {
    if (!sio_ok) return;
    while (*s) sio_putchar(*s++);
}
