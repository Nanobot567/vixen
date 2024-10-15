#include "include/ports.h"

char inb(short _port) {
  char rv;
  __asm__ __volatile__("inb %1, %0" : "=a"(rv) : "dN"(_port));
  return rv;
}

void outb(short _port, char _data) {
  __asm__ __volatile__("outb %1, %0" : : "dN"(_port), "a"(_data));
}
