#include <stddef.h>
#include <stdint.h>

#include "kernel/include/gdt.h"
#include "kernel/include/terminal.h"
#include "kernel/include/keyboard.h"
#include "kernel/include/vga.h"

#include "libc/include/stdio.h"

void kernel_main() {
  gdt_init();

  terminal_cls();
  printf("Vixen v0.1\n\n");

  terminal_setcolor(VGA_COLOR_RED);
  printf("[VXN] ");
  terminal_setcolor(terminal_user_color);

  while(1) {
    keyboard_handler();
  }
}
