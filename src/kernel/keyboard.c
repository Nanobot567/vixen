#include "include/keyboard.h"
#include "include/irq.h"
#include "include/terminal.h"
#include "include/vga.h"
#include "include/timer.h"

#include "../misc/include/ports.h"

#include "../libc/include/string.h"
#include "../libc/include/stdio.h"

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

void kbNoHandler(char sc, char ch) {}

kbHandler_t currentKeyboardHandler;

void keyboard_push_handler(kbHandler_t h) {
  currentKeyboardHandler = h;
}

void keyboard_init() {
  printf("Initializing keyboard...\n");

  for (int i = 0; i < 256; i++) {
    kbBuffer[i] = '\x00';
  }

  for (int i = 0; i < 16; i++) {
    kbHeldBuffer[i] = '\x00';
  }

  keyboard_push_handler(terminal_keyboard_handler);

  irq_install_handler(1, keyboard_handler);
}

void keyboard_handler() {
  char sc = inb(0x60);
  char ch = kbdus[(int)sc];

  (*currentKeyboardHandler)(sc, ch);
}
