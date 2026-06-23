/*
 * config/idt.h – Minimal IDT setup for BlexOS
 * Copyright (C) 2026 Blex – BOSL License
 *
 * Sets up a 256-entry Interrupt Descriptor Table where every
 * entry points to the same "ignore and return" stub.
 * This prevents triple-faults from any unhandled interrupt
 * (PIT timer, keyboard, spurious IRQs, etc.).
 *
 * The kernel is polling-based and does not need interrupts,
 * but the CPU will crash if an interrupt fires without an IDT.
 */

#ifndef CONFIG_IDT_H
#define CONFIG_IDT_H

#include <stdint.h>

/* Register state passed to syscall_handler */
typedef struct {
    uint32_t eax, ebx, ecx, edx;
} __attribute__((packed)) syscall_regs_t;

/* IDT entry (8 bytes, x86 protected mode) */
typedef struct {
    uint16_t offset_low;   /* bits 0..15 of handler address */
    uint16_t selector;     /* code segment selector */
    uint8_t  zero;         /* must be 0 */
    uint8_t  type_attr;    /* present, DPL, gate type */
    uint16_t offset_high;  /* bits 16..31 of handler address */
} __attribute__((packed)) idt_entry_t;

/* IDT pointer structure (loaded by LIDT) */
typedef struct {
    uint16_t limit;        /* size of IDT - 1 */
    uint32_t base;         /* linear address of IDT */
} __attribute__((packed)) idt_pointer_t;

/* Gate type: 32-bit interrupt gate */
#define IDT_GATE_32INT     0x8E   /* present, ring 0, 32-bit interrupt gate */

/* Syscall vector number */
#define IDT_VEC_SYSCALL     0x80

/* Number of IDT entries */
#define IDT_ENTRIES        256

/* The IDT table (256 entries, 2048 bytes) */
extern idt_entry_t  idt_table[IDT_ENTRIES];
extern idt_pointer_t idt_ptr;

/* Syscall numbers used via int 0x80 */
#define SYSCALL_PUTS       1   /* ebx = const char* string */
#define SYSCALL_EXIT       2   /* cli; hlt */
#define SYSCALL_PUTCHAR    3   /* ebx = char */
#define SYSCALL_CLEAR      4   /* clear screen */
#define SYSCALL_CD         5   /* ebx = path, change cwd */
#define SYSCALL_GETCWD     6   /* ebx = buf, ecx = size, copy cwd */
#define SYSCALL_ES1_NODES  7   /* return es1_nodes pointer in eax */

/* Initialize IDT: fill all 256 entries with the default handler and load IDT */
void idt_init(void);

#endif /* CONFIG_IDT_H */
