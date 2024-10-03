#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef _SYS_H
#define _SYS_H

extern const int VGA_WIDTH;
extern const int VGA_HEIGHT;
extern char* VERSION;

extern int terminal_row;
extern int terminal_column;
extern uint8_t terminal_color;
extern uint16_t *terminal_buffer;

extern void upd_csr(void);
extern void move_csr(int row, int col);

enum VGA_COLOR {
  VGA_COLOR_BLACK = 0,
  VGA_COLOR_BLUE = 1,
  VGA_COLOR_GREEN = 2,
  VGA_COLOR_CYAN = 3,
  VGA_COLOR_RED = 4,
  VGA_COLOR_MAGENTA = 5,
  VGA_COLOR_BROWN = 6,
  VGA_COLOR_LIGHT_GREY = 7,
  VGA_COLOR_DARK_GREY = 8,
  VGA_COLOR_LIGHT_BLUE = 9,
  VGA_COLOR_LIGHT_GREEN = 10,
  VGA_COLOR_LIGHT_CYAN = 11,
  VGA_COLOR_LIGHT_RED = 12,
  VGA_COLOR_LIGHT_MAGENTA = 13,
  VGA_COLOR_LIGHT_BROWN = 14,
  VGA_COLOR_WHITE = 15,
};

extern enum VGA_COLOR VGA_COLOR;

extern int terminal_user_color;

extern void terminal_cls(void);
extern void terminal_setcolor(uint8_t color);
extern void terminal_putentryat(char c, uint8_t color, int x, int y);
extern void terminal_putchar(char c);
extern void terminal_write(char *data, int size);
extern void terminal_writestring(char *data);
extern void terminal_exec(char data[]);
extern void terminal_prompt();

extern void keyboard_init();
extern void keyboard_handler();

extern char* memcpy(void *dest, void *src, int n);
extern int* memset(int *dest, char val, int n);
extern int strlen(const char *str);
extern char inb(short _port);
extern void outb(short _port, char _data);

extern void append(char s[], char n);
extern void backspace(char s[]);
extern int strcmp(char s1[], char s2[]);
extern char *substr(char *dst, char *src, int offset, int length);
extern void reverse(char str[], int length);
extern char *itoa(int num, char *str, int base);
extern int atoi(char* str);

extern unsigned char century;
extern unsigned char second;
extern unsigned char minute;
extern unsigned char hour;
extern unsigned char day;
extern unsigned char month;
extern unsigned int year;

extern void read_rtc();
extern void wait_a_moment();

extern void play_frequency(uint32_t frequency);
extern void pcspk_stop();
extern void beep();

#endif
