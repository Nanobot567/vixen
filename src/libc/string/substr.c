#include "../include/string.h"

char* substr(char *src, int offset, int length) {
  char* dst;

  memcpy(dst, src + offset, length);
  dst[length] = '\0';
  return dst;
}
