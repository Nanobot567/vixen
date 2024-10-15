#ifndef _KERNEL_TERMINAL_H
#define _KERNEL_TERMINAL_H

#include <stddef.h>
#include <stdint.h>

extern int terminal_user_color;

extern void terminal_cls(void);
extern void terminal_setcolor(uint8_t color);
extern void terminal_putentryat(char c, uint8_t color, int x, int y);
extern void terminal_putchar(char c);
extern void terminal_write(const char *data, size_t size);
extern void terminal_writestring(const char *data);

#endif
