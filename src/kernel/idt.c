#include <stdbool.h>
#include <stdint.h>

#include "../libc/include/stdio.h"
#include "../misc/include/aconv.h"
#include "include/terminal.h"
#include "include/vga.h"
#include "include/regs.h"

typedef struct {
  uint16_t isr_low;   // The lower 16 bits of the ISR's address
  uint16_t kernel_cs; // The GDT segment selector that the CPU will load into CS
                      // before calling the ISR
  uint8_t reserved;   // Set to zero
  uint8_t attributes; // Type and attributes; see the IDT page
  uint16_t isr_high;  // The higher 16 bits of the ISR's address
} __attribute__((packed)) idt_entry_t;

__attribute__((aligned(0x10))) static idt_entry_t
    idt[256]; // Create an array of IDT entries; aligned for performance

typedef struct {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) idtr_t;

static idtr_t idtr;


char *exception_messages[] =
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

__attribute__((noreturn))
void exception_handler(struct regs *r);
void exception_handler(struct regs *r) {
  // __asm__ volatile("cli;");
  
  char* temp;

  if (r->int_no < 32) {
    terminal_setcolor(VGA_COLOR_RED);
    printf("\n\n[EXCEPTION] ");

    printf(exception_messages[r->int_no]);

    printf(" (");

    printf(itoa(r->int_no, temp, 10));

    printf("), halting!");
    __asm__ volatile ("hlt"); // Completely hangs the computer
  }

  // __asm__ volatile ("ret");
}

void idt_set_descriptor(uint8_t vector, void *isr, uint8_t flags);
void idt_set_descriptor(uint8_t vector, void *isr, uint8_t flags) {
  idt_entry_t *descriptor = &idt[vector];

  descriptor->isr_low = (uint32_t)isr & 0xFFFF;
  descriptor->kernel_cs = 0x08; // this value can be whatever offset your kernel
                                // code selector is in your GDT
  descriptor->attributes = flags;
  descriptor->isr_high = (uint32_t)isr >> 16;
  descriptor->reserved = 0;
}

#define IDT_MAX_DESCRIPTORS 256

static bool vectors[IDT_MAX_DESCRIPTORS];

extern void *isr_stub_table[];

void idt_init(void);
void idt_init() {
  char* temp;

  idtr.base = (uintptr_t)&idt[0];
  idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

  printf("Filling IDT vectors");

  for (uint8_t vector = 0; vector < 32; vector++) {
    idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
    vectors[vector] = true;
    printf(".");
  }

  printf("\n");

  __asm__ volatile("lidt %0" : : "m"(idtr)); // load the new IDT
  __asm__ volatile("sti");                   // set the interrupt flag
}
