/*
 * idt.c – Minimal IDT + PIC remap for BlexOS
 *
 * 1. Remaps the 8259A PIC so IRQs don't overlap CPU exception vectors.
 * 2. Masks all IRQ lines after remap.
 * 3. Installs a 256-entry IDT with three stub types:
 *    - halt_err:  for CPU exceptions WITH error code (pop err, cli, hlt)
 *    - halt:      for CPU exceptions WITHOUT error code (cli, hlt)
 *    - eoi_iret:  for hardware IRQs (send EOI, then iret)
 *
 * The EOI in the IRQ handler is critical — without it, the PIC keeps
 * asserting the IRQ line, which will re-fire as soon as IF=1 is restored
 * by iret.
 */

#include "idt.h"
#include "../kernel_utils.h"

/* ── IDT table ──────────────────────────────────────────── */
idt_entry_t   idt_table[IDT_ENTRIES] __attribute__((aligned(8)));
idt_pointer_t idt_ptr;

/* ── Assembly stubs ─────────────────────────────────────── */
__asm__ (
    /* HALT on CPU exception that pushes an error code */
    ".globl idt_stub_halt_err\n"
    "idt_stub_halt_err:\n"
    "    addl $4, %esp      \n"   /* pop error code */
    "    cli                \n"
    "1:  hlt                \n"
    "    jmp 1b             \n"

    /* HALT on CPU exception WITHOUT error code */
    ".globl idt_stub_halt\n"
    "idt_stub_halt:\n"
    "    cli                \n"
    "2:  hlt                \n"
    "    jmp 2b             \n"

    /* IRQ handler — send EOI then return */
    ".globl idt_stub_eoi_iret\n"
    "idt_stub_eoi_iret:\n"
    "    push %eax          \n"   /* save eax */
    "    movb $0x20, %al    \n"   /* EOI command (non-specific) */
    "    outb %al, $0x20    \n"   /* to master PIC command port */
    "    outb %al, $0xA0    \n"   /* to slave  PIC command port */
    "    pop %eax           \n"   /* restore eax */
    "    iret               \n"

    /* int 0x80 syscall handler — passes pointer to saved regs */
    ".globl idt_stub_syscall\n"
    "idt_stub_syscall:\n"
    "    push %edx          \n"
    "    push %ecx          \n"
    "    push %ebx          \n"
    "    push %eax          \n"   /* regs[0..3] = eax,ebx,ecx,edx */
    "    mov %esp, %eax     \n"   /* arg1 = pointer to regs */
    "    call syscall_handler\n"
    "    pop %eax           \n"   /* restore eax (modified by handler) */
    "    pop %ebx           \n"
    "    pop %ecx           \n"
    "    pop %edx           \n"
    "    iret               \n"
);

/* ── Externs from command_logic.c (kernel globals) ───────── */
extern char  cwd_path[256];
extern int   str_len(const char*);
extern void  str_copy(char*, const char*);

/* ── C syscall handler ───────────────────────────────────────
 * Called from idt_stub_syscall.
 * regs points to the saved registers (eax,ebx,ecx,edx) from
 * the interrupted code.  The handler may modify regs->eax
 * to return a value to the caller.
 */
void syscall_handler(syscall_regs_t *regs) {
    switch (regs->eax) {
    case SYSCALL_PUTS:    /* 1: print string at ebx */
        if (regs->ebx) print_str((const char*)(unsigned long)regs->ebx);
        break;
    case SYSCALL_EXIT:    /* 2: halt system */
        print_str_color("\n[exit]\n", (char)0x0C);
        __asm__ volatile ("cli; hlt");
        break;
    case SYSCALL_PUTCHAR: /* 3: putchar(ebx) */
        putchar((char)regs->ebx);
        break;
    case SYSCALL_CLEAR:   /* 4: clear screen */
        clear_screen();
        break;
    case SYSCALL_CD:      /* 5: change directory (ebx = path) */
        if (regs->ebx) {
            str_copy(cwd_path, (const char*)(unsigned long)regs->ebx);
        }
        break;
    case SYSCALL_GETCWD:  /* 6: get cwd (ebx = buf, ecx = size) */
        if (regs->ebx && regs->ecx > 0) {
            int i = 0;
            while (cwd_path[i] && i < (int)regs->ecx - 1) {
                ((char*)(unsigned long)regs->ebx)[i] = cwd_path[i];
                i++;
            }
            ((char*)(unsigned long)regs->ebx)[i] = '\0';
        }
        break;
    case SYSCALL_ES1_NODES: /* 7: return es1_nodes pointer in eax */
        {
            extern es1_node_t es1_nodes[];
            regs->eax = (uint32_t)(unsigned long)es1_nodes;
        }
        break;
    }
}

/* ── Vectors that push an error code ────────────────────── */
#define ERROR_CODE_VECTORS \
    ((1u << 8)|(1u << 10)|(1u << 11)|(1u << 12)|(1u << 13)|(1u << 14)|(1u << 17))

static int has_error_code(int vec) {
    if (vec < 0 || vec >= 32) return 0;
    return (ERROR_CODE_VECTORS >> vec) & 1;
}

/* ── Write one IDT entry ────────────────────────────────── */
static void idt_set_entry(int idx, uint32_t handler,
                          uint16_t selector, uint8_t flags) {
    idt_entry_t *e = &idt_table[idx];
    e->offset_low  = handler & 0xFFFF;
    e->selector    = selector;
    e->zero        = 0;
    e->type_attr   = flags;
    e->offset_high = (handler >> 16) & 0xFFFF;
}

/* ── Remap the 8259A PIC ──────────────────────────────────
 *
 * Default BIOS mapping:
 *   Master ICW2 = 0x08  → IRQ0 → INT 0x08 (double fault vector!)
 *   Slave  ICW2 = 0x70  → IRQ8 → INT 0x70
 *
 * We remap to the standard protected-mode offsets:
 *   Master → 0x20  (IRQ0 → INT 0x20)
 *   Slave  → 0x28  (IRQ8 → INT 0x28)
 *
 * After remap, all IRQs are masked (OCW1 = 0xFF).
 * ──────────────────────────────────────────────────────── */
static void pic_remap(void) {
    /* Save current masks */
    uint8_t mask_master, mask_slave;
    __asm__ volatile ("inb %1, %0" : "=a"(mask_master) : "Nd"(0x21));
    __asm__ volatile ("inb %1, %0" : "=a"(mask_slave)  : "Nd"(0xA1));

    /* ICW1: begin initialization sequence (cascade, ICW4 needed) */
    outb(0x20, 0x11);    /* master */
    outb(0xA0, 0x11);    /* slave  */

    /* ICW2: remap offset */
    outb(0x21, 0x20);    /* master: IRQ0 → INT 0x20 */
    outb(0xA1, 0x28);    /* slave:  IRQ8 → INT 0x28 */

    /* ICW3: slave connection */
    outb(0x21, 0x04);    /* master: slave at IRQ2 (bit 2) */
    outb(0xA1, 0x02);    /* slave:  cascade ID 2 */

    /* ICW4: 8086 mode, normal EOI, non-buffered */
    outb(0x21, 0x01);
    outb(0xA1, 0x01);

    /* OCW1: restore masks (originally 0xFF from boot.s, but just mask all) */
    outb(0x21, 0xFF);    /* mask all on master */
    outb(0xA1, 0xFF);    /* mask all on slave  */
}

/* ── Initialize the IDT ─────────────────────────────────── */
void idt_init(void) {
    extern uint32_t idt_stub_halt_err;
    extern uint32_t idt_stub_halt;
    extern uint32_t idt_stub_eoi_iret;
    extern uint32_t idt_stub_syscall;

    /* 1. Remap PIC first — this must happen BEFORE installing the IDT
     *    because the PIC might fire spurious interrupts during remap. */
    pic_remap();

    /* 2. Fill IDT */
    uint16_t cs;
    __asm__ volatile ("mov %%cs, %0" : "=r"(cs));

    for (int i = 0; i < IDT_ENTRIES; i++) {
        uint32_t handler;
        if (i >= 32) {
            /* Hardware IRQ — send EOI, then return */
            handler = (uint32_t)&idt_stub_eoi_iret;
        } else if (has_error_code(i)) {
            /* Exception with error code — pop it, then halt */
            handler = (uint32_t)&idt_stub_halt_err;
        } else {
            /* Exception without error code — halt immediately */
            handler = (uint32_t)&idt_stub_halt;
        }
        idt_set_entry(i, handler, cs, IDT_GATE_32INT);
    }

    /* Override vector 0x80 with syscall handler */
    idt_set_entry(IDT_VEC_SYSCALL, (uint32_t)&idt_stub_syscall, cs, IDT_GATE_32INT);

    /* 3. Load IDT */
    idt_ptr.limit = sizeof(idt_table) - 1;
    idt_ptr.base  = (uint32_t)&idt_table;
    __asm__ volatile ("lidt %0" : : "m"(idt_ptr) : "memory");
}
