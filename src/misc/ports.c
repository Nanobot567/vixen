#include "include/ports.h"
#include <stdint.h>

char inb(short _port) {
  char rv;
  __asm__ __volatile__("inb %1, %0" : "=a"(rv) : "dN"(_port));
  return rv;
}

uint16_t inw(int port) {
  uint16_t result;
  __asm__ __volatile__("inw %w1, %w0" : "=a"(result) : "Nd"(port));
  return result;
}

uint32_t inl(int port) {
  uint32_t result;
  __asm__ __volatile__("inl %w1, %0" : "=a"(result) : "Nd"(port));
  return result;
}

void outb(short _port, char _data) {
  __asm__ __volatile__("outb %1, %0" : : "dN"(_port), "a"(_data));
}

void outw(int port, uint16_t data) {
  __asm__ __volatile__("outw %w0, %w1" : : "a"(data), "Nd"(port));
}

void outl(int port, uint32_t data) {
  __asm__ __volatile__("outl %0, %w1" : : "a"(data), "Nd" (port));
}
