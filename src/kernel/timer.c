#include <stdbool.h>

#include "../misc/include/aconv.h"
#include "../misc/include/ports.h"
#include "include/irq.h"
#include "include/regs.h"
#include "include/timer.h"

#include "../libc/include/stdio.h"

int pit_freq;
int timer_ticks = 0;

void timer_handler(struct regs *r) {
  timer_ticks++;

  if (timer_ticks % 100 == 0) {
  }
}

void timer_wait(int ticks) {
  unsigned long eticks = 0;

  eticks = timer_ticks + ticks;

  __asm__ volatile ("sti");

  while (timer_ticks < eticks) {
    __asm__ volatile ("nop");  // uhhh.. for some reason this works and not just while();
  };
}

void timer_init() {
  timer_phase(100);
  irq_install_handler(0, (void *)timer_handler);
}

void sleep(double secs) {
  timer_wait((int)(secs * 100));
}

void timer_phase(int hz) {
  pit_freq = hz;

  int divisor = 1193180 / hz; /* Calculate our divisor */
  outb(0x43, 0x36);           /* Set our command byte 0x36 */
  outb(0x40, divisor & 0xFF); /* Set low byte of divisor */
  outb(0x40, divisor >> 8);   /* Set high byte of divisor */
}
