#ifndef _TIMER_H
#define _TIMER_H

#include <stdbool.h>

void timer_init();
void timer_wait(int ticks);
void timer_phase(int hz);
void sleep(double secs);

extern int timer_ticks;

#endif
