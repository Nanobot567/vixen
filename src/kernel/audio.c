#include <stdint.h>

#include "include/timer.h"
#include "../misc/include/ports.h"
#include "../misc/include/aconv.h"
#include "../libc/include/stdio.h"

int beep_frequency = 1000;

void play_frequency(uint32_t frequency) {
  uint32_t div;
  uint8_t tmp;
  div = 1193180 / frequency;
  outb(0x43, 0xb6);
  outb(0x42, (uint8_t)(div));
  outb(0x42, (uint8_t)(div >> 8));
  tmp = inb(0x61);
  if (tmp != (tmp | 3)) {
    outb(0x61, tmp | 3);
  }
}
void pcspk_stop() {
  uint8_t tmp = inb(0x61) & 0xFC;
  outb(0x61, tmp);
}
void beep() {
  play_frequency(beep_frequency);
  sleep(0.1);
  pcspk_stop();
}

void beep_freq_time(int freq, double time) {
  play_frequency(freq);
  sleep(time);
  pcspk_stop();
}
