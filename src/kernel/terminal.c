#include "../libc/include/string.h"
#include "../libc/include/stdio.h"

#include "../misc/include/ports.h"
#include "../misc/include/strutils.h"

#include "../shell/include/shell.h"

#include "include/keyboard.h"
#include "include/terminal.h"
#include "include/vga.h"

static const int VGA_WIDTH = 80;
static const int VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

int terminal_user_color = VGA_COLOR_LIGHT_GREY;

void upd_csr(void) {
  unsigned temp;

  temp = terminal_row * 80 + terminal_column;

  outb(0x3D4, 14);
  outb(0x3D5, temp >> 8);
  outb(0x3D4, 15);
  outb(0x3D5, temp);
}

void move_csr(int row, int col) {
  terminal_row = row;
  terminal_column = col;

  upd_csr();
}

void terminal_cls(void) {
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = vga_entry_color(terminal_user_color, VGA_COLOR_BLACK);
  terminal_buffer = (uint16_t *)0xB8000;
  for (int y = 0; y < VGA_HEIGHT; y++) {
    for (int x = 0; x < VGA_WIDTH; x++) {
      const int index = y * VGA_WIDTH + x;
      terminal_buffer[index] = vga_entry(' ', terminal_color);
    }
  }
}

void terminal_setcolor(uint8_t color) { terminal_color = color; }

void terminal_putentryat(char c, uint8_t color, int x, int y) {
  const int index = y * VGA_WIDTH + x;
  terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) {
  char uc = c;

  switch (c) {
  case '\n':
    terminal_row++;
    terminal_column = 0;
    break;

  case '\b':
    terminal_column -= 1;
    terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
    break;

  default:
    terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
    terminal_column++;
  }

  if (terminal_column >= VGA_WIDTH) {
    terminal_column = 0;
    terminal_row++;
  }

  if (terminal_row >= VGA_HEIGHT) {
    int i, j;
    for (i = 0; i < VGA_WIDTH; i++) {
      for (j = 0; j < VGA_HEIGHT; j++) {
        terminal_buffer[(j * VGA_WIDTH) + i] =
            terminal_buffer[((j + 1) * VGA_WIDTH) + i];
      }
    }

    for (i = 0; i < VGA_WIDTH; i++) {
      terminal_putentryat(' ', terminal_color, i, VGA_HEIGHT - 1);
    }

    terminal_row = VGA_HEIGHT - 1;
  }

  upd_csr();
}

void terminal_write(const char *data, size_t size) {
  for (int i = 0; i < size; i++) {
    terminal_putchar(data[i]);
  }
}

void terminal_writestring(const char *data) { terminal_write(data, strlen(data)); }

void terminal_keyboard_handler(char sc, char ch) {
  if (sc & 0x80) {
    backspace(kbHeldBuffer);
  } else if (kbHeldBuffer[strlen(kbHeldBuffer) - 1] != ch) {
    append(kbHeldBuffer, ch);

    if (ch == KB_ENTER) {
      terminal_setcolor(VGA_COLOR_GREEN);
      printf("\xFB\n");
      terminal_setcolor(terminal_user_color);

      parse(kbBuffer);

      for (int i = 0; i < 256; i++) {
        kbBuffer[i] = '\x00';
      }
      
      terminal_setcolor(VGA_COLOR_RED);
      printf("[VXN] ");
      terminal_setcolor(terminal_user_color);
    } else if (ch == KB_BACKSPACE) {
      if (strlen(kbBuffer) != 0) {
        backspace(kbBuffer);
        putchar('\b');
      }
    } else {
      append(kbBuffer, ch);

      putchar(ch);
    }
  }
}
