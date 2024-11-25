#ifndef _PORTS_H
#define _PORTS_H

#include <stdint.h>

char inb(short _port);
uint16_t inw(int port);
uint32_t inl(int port);
void outb(short _port, char _data);
void outw(int port, uint16_t data);
void outl(int port, uint32_t data);

#endif
