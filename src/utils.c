#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "sys.h"

char *memcpy(void *dest, void *src, int n) {
  char *csrc = (char *)src;
  char *cdest = (char *)dest;

  for (int i = 0; i < n; i++) {
    cdest[i] = csrc[i];
  }

  return cdest;
}

int *memset(int *dest, char val, int n) {
  for (int i = 0; i < n; i++) {
    dest[i] = val;
  }

  return dest;
}

int strlen(const char *str) {
  int len = 0;
  while (str[len]) {
    len++;
  }
  return len;
}

char inb(short _port) {
  char rv;
  __asm__ __volatile__("inb %1, %0" : "=a"(rv) : "dN"(_port));
  return rv;
}

void outb(short _port, char _data) {
  __asm__ __volatile__("outb %1, %0" : : "dN"(_port), "a"(_data));
}

void append(char s[], char n) {
  int len = strlen(s);
  s[len] = n;
  s[len + 1] = '\0';
}

void backspace(char s[]) {
  int len = strlen(s);
  s[len - 1] = '\0';
}

int strcmp(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

char* substr(char *dst, char *src, int offset, int length) {
    memcpy(dst, src + offset, length);
    dst[length] = '\0';
    return dst;
}
