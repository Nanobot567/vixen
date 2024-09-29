#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "sys.h"

void kernel_main(void) {
  terminal_cls();

  terminal_writestring("Initializing keyboard...\n");
  keyboard_init();
  terminal_writestring("Finished! Loading...\n");

  terminal_cls();

  terminal_setcolor(VGA_COLOR_RED);
  terminal_writestring("Vixen ");
  terminal_writestring(VERSION);
  terminal_writestring("\n\n");

  terminal_writestring("Hello, welcome to Vixen! This is a dumb little operating system. Have fun?\n\n");

  terminal_prompt();

  while(1) {
    keyboard_handler();
  }
}
