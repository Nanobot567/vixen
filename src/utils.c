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
    if (s1[i] == '\0')
      return 0;
  }
  return s1[i] - s2[i];
}

char *substr(char *dst, char *src, int offset, int length) {
  memcpy(dst, src + offset, length);
  dst[length] = '\0';
  return dst;
}

void reverse(char str[], int length) {
  int start;
  int end = length - 1;
  for (start = 0; start < end; ++start, --end) {
    const char ch = str[start];
    str[start] = str[end];
    str[end] = ch;
  }
}

char *itoa(int num, char *str, int base) {
  int i = 0;
  char isNegNum = 0;
  /*Handle 0 explicitly,
    otherwise empty string is printed for 0 */
  if (num == 0) {
    str[i++] = '0';
    str[i] = '\0';
  } else {
    // In library itoa function -ve numbers handled only with
    // base 10. SO here we are also following same concept
    if ((num < 0) && (base == 10)) {
      isNegNum = 1;
      num = -num; // make num positive
    }
    // Process individual digits
    do {
      const int rem = (num % base);
      str[i++] = (rem > 9) ? ((rem - 10) + 'a') : (rem + '0');
      num = num / base;
    } while (num != 0);
    // If number is negative, append '-'
    if (isNegNum) {
      str[i++] = '-';
    }
    // Append string terminator
    str[i] = '\0';
    // Reverse the string
    reverse(str, i);
  }
  return str;
}

int atoi(char *str) {
  int num = 0;
  int i = 0;
  bool isNegetive = false;
  if (str[i] == '-') {
    isNegetive = true;
    i++;
  }
  while (str[i] && (str[i] >= '0' && str[i] <= '9')) {
    num = num * 10 + (str[i] - '0');
    i++;
  }
  if (isNegetive)
    num = -1 * num;
  return num;
}
