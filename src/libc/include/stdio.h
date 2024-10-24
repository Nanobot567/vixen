#ifndef _STDIO_H
#define _STDIO_H 1

#define EOF (-1)

// int printf(const char* __restrict, ...);

#define printf printf_
int printf_(const char* format, ...);

int putchar(int);
int puts(const char*);

#endif
