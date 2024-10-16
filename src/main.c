#include <stddef.h>
#include <stdint.h>

#include "kernel/include/gdt.h"
#include "kernel/include/idt.h"
#include "kernel/include/irq.h"
#include "kernel/include/terminal.h"
#include "kernel/include/keyboard.h"
#include "kernel/include/vga.h"

void kernel_main() {

  terminal_cls();
 
  keyboard_init();

  gdt_init();
  idt_init();
  irq_init();

  printf("\nVixen v0.1\n\n");

  terminal_setcolor(VGA_COLOR_RED);
  printf("[VXN] ");
  terminal_setcolor(terminal_user_color);

  while(1){}
}
