#ifndef _GDT_H
#define _GDT_H

#include <stdint.h>
#include "../../libc/include/stdio.h"

void gdt_create_descriptor(uint32_t base, uint32_t limit, uint16_t flag);
void gdt_init(void);

#endif
