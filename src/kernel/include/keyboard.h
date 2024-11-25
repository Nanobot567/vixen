#ifndef _KEYBOARD_H
#define _KEYBOARD_H

typedef void (*kbHandler_t)(char, char);

extern void keyboard_init();
extern void keyboard_handler();
extern void keyboard_push_handler(kbHandler_t);

extern char kbBuffer[256];
extern char kbHeldBuffer[16];

#define KB_BACKSPACE 0x0E
#define KB_ENTER 0x1C

#endif
