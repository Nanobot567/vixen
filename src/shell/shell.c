#include <stdbool.h>

#include "../kernel/include/audio.h"
#include "../kernel/include/timer.h"
#include "../libc/include/stdio.h"
#include "../libc/include/string.h"
#include "../misc/include/aconv.h"
#include "../misc/include/hex2int.h"

bool contains_delim(char *str, char delim) {
  int len = strlen(str);

  for (int i = 0; i < len; i++) {
    if (str[i] == delim) {
      return true;
    }
  }
  return false;
}

unsigned char RAM_prgspace[2048];

int parse(char *input) {
  char *tmp;
  char *tmp2;
  char *argv[256];
  int argv_len = 0;

  char *ch;
  ch = strtok(input, " ");
  while (ch != NULL) {
    argv[argv_len] = ch;
    argv_len++;
    ch = strtok(NULL, " ,");
  }

  char* cmd = argv[0];

  if (strcmp(cmd, "freq") == 0) {
    // int freq = atoi(tmp);

    printf("beep frequency = ");
    printf(argv[1]);
    printf("Hz. \n");

    beep_frequency = atoi(argv[1]);

  } else if (strcmp(cmd, "beep") == 0) {
    beep();
  } else if (strcmp(cmd, "rpeek") == 0) {
    char *p = (char *)atoi(argv[1]);

    printf("Address:  %p\n", p);
    printf("Contents: 0x%02x\n", *p);
  } else if (strcmp(cmd, "rpoke") == 0) {
    memset((void*)atoi(argv[1]), atoi(argv[2]), 8);
  } else if (strcmp(cmd, "peek") == 0) {
    int dat = RAM_prgspace[atoi(argv[1])];

    printf(itoa(dat, tmp, 10));

    printf(" (%02X)", dat);

    printf("\n");
    // RAM_prgspace[atoi(argv[1])] = atoi(argv[2]);
  } else if (strcmp(cmd, "poke") == 0) {
    char* old = itoa(RAM_prgspace[atoi(argv[1])], tmp, 10);

    printf(old);
    printf(" >> ");
    printf(argv[2]);
    printf("\n");

    RAM_prgspace[atoi(argv[1])] = atoi(argv[2]);
  } else if (strcmp(cmd, "int") == 0) {
    printf(argv[1]);

    printf(" = ");

    printf("0x%02X", atoi(argv[1]));

    printf("\n");
  } else if (strcmp(cmd, "hex") == 0) {
    printf("0x");

    printf(argv[1]);

    printf(" = ");

    printf(itoa(hex2int(argv[1]), tmp, 10));

    printf("\n");
  } else if (strcmp(cmd, "exec") == 0) {
    // TODO: execute bytes as scripting language instead of raw code
    void(*func_ptr)(void) = (void(*)(void)) &RAM_prgspace[0];
    func_ptr();
  } else if (strcmp(cmd, "uptime") == 0) {
    printf("up for ");
    printf(itoa(timer_ticks, tmp, 10));
    printf(" ticks (");
    printf(itoa(timer_ticks / pit_freq, tmp, 10));
    printf(" sec)\n");
  }

  return 0;
}
