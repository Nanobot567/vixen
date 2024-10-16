#ifndef _IRQ_H
#define _IRQ_H

void irq_init(void);
void irq_install_handler(int irq, void (*handler)(struct regs *r));

#endif
