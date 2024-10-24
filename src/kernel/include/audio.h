#ifndef _AUDIO_H
#define _AUDIO_H

void beep();
void play_sequence(int* pitches, double* times);
void beep_freq_time(int freq, double time);
extern int beep_frequency;

#endif
