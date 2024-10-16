#ifndef _GDT_H
#define _GDT_H

#include <stdint.h>
#include "../../libc/include/stdio.h"

extern void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
extern void gdt_init();

#endif
