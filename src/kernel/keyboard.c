#include "include/keyboard.h"
#include "include/irq.h"
#include "include/terminal.h"
#include "include/vga.h"

#include "../misc/include/ports.h"
#include "../libc/include/string.h"
#include "../libc/include/stdio.h"

// TODO: move to new file pls
void append(char s[], char n) {
  int len = strlen(s);
  s[len] = n;
  s[len + 1] = '\0';
}

void backspace(char s[]) {
  int len = strlen(s);
  s[len - 1] = '\0';
}


#define KB_BACKSPACE 0x0E
#define KB_ENTER 0x1C

const char kbdus[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9',  '0', '-', '=', KB_BACKSPACE,
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', KB_ENTER,
    0, 'a', 's', 'd', 'f', 'g', 'h',  'j', 'k', 'l', ';', '\'', '`',
    0, // lshift
    '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 
    0, // rshift
    '*',
    0, // alt
    ' ',
    0, // caps lock
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // f1 - f10
    0, // num lock
    0, // scroll lock
    0, // home
    0, // up
    0, // pgup
    '-',
    0, // larrow
    0,
    0, // rarrow
    '+',
    0, // end key
    0, // down
    0, // pgdown
    0, // insert
    0, // delete
    0, 0, 0, 0, 0, 0
};

char kbBuffer[256];
char kbHeldBuffer[16];

void keyboard_init() {
  printf("Initializing keyboard...\n");

  for (int i = 0; i < 256; i++) {
    kbBuffer[i] = '\x00';
  }

  for (int i = 0; i < 16; i++) {
    kbHeldBuffer[i] = '\x00';
  }

  irq_install_handler(1, keyboard_handler);
}

void keyboard_handler() {
  char sc = inb(0x60);

  char ch = kbdus[(int)sc];

  if (sc & 0x80) {
    backspace(kbHeldBuffer);
  } else if (kbHeldBuffer[strlen(kbHeldBuffer) - 1] != ch) {
    append(kbHeldBuffer, ch);

    if (ch == KB_ENTER) {
      terminal_setcolor(VGA_COLOR_GREEN);
      printf("\xFB\n");
      terminal_setcolor(terminal_user_color);
      // terminal_exec(kbBuffer);

      for (int i = 0; i < 256; i++) {
        kbBuffer[i] = '\x00';
      }
      
      terminal_setcolor(VGA_COLOR_RED);
      printf("[VXN] ");
      terminal_setcolor(terminal_user_color);
    } else if (ch == KB_BACKSPACE) {
      backspace(kbBuffer);
      putchar('\b');
    } else {
      append(kbBuffer, ch);

      putchar(ch);
    }
  }
}
