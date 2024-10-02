#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "sys.h"

static inline uint8_t vga_entry_color(enum VGA_COLOR fg, enum VGA_COLOR bg) {
  return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
  return (uint16_t)uc | (uint16_t)color << 8;
}

int terminal_row;
int terminal_column;
uint8_t terminal_color;
uint16_t *terminal_buffer;

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
  terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
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

void terminal_write(char *data, int size) {
  for (int i = 0; i < size; i++) {
    terminal_putchar(data[i]);
  }
}

void terminal_writestring(char *data) { terminal_write(data, strlen(data)); }

void terminal_prompt() { terminal_writestring("VXN> "); }

void terminal_exec(char data[]) {
  char temp[256];

  if (strcmp(substr(temp, data, 0, 4), "echo") == 0) {
    terminal_setcolor(VGA_COLOR_WHITE);
    terminal_writestring(substr(temp, data, 5, strlen(data)));
    terminal_writestring("\n");
    terminal_setcolor(VGA_COLOR_RED);
  } else if (strcmp(substr(temp, data, 0, 4), "halt") == 0) {
    terminal_writestring("\nHalting CPU. Later!\n");
    asm volatile("hlt");
  } else if (strcmp(substr(temp, data, 0, 3), "spk") == 0) {
    beep();
  }
  terminal_prompt();
}
