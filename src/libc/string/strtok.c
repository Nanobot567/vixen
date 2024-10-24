#include <stddef.h>
#include <stdbool.h>

#include "../include/stdio.h"
#include "../include/string.h"

bool is_delim(char c, char *delim) {
  while (*delim != '\0') {
    if (c == *delim)
      return true;
    delim++;
  }
  return false;
}

char *strtok(char *s, char *delim) {
  static char *p;
  if (!s) {
    s = p;
  }
  if (!s) {
    return NULL;
  }

  while (1) {
    if (is_delim(*s, delim)) {
      s++;
      continue;
    }
    if (*s == '\0') {
      return NULL;
    }

    break;
  }

  char *ret = s;
  while (1) {
    if (*s == '\0') {
      p = s;
      return ret;
    }
    if (is_delim(*s, delim)) {
      *s = '\0';
      p = s + 1;
      return ret;
    }
    s++;
  }
}

char *strtok_r(char *text, char delimiter, char **save_this) {
  if (save_this == NULL) {
    return NULL;
  }
  if (text != NULL) {
    /* New text. */
    int i = 0;
    while (text[i] != '\0') {
      if (text[i] == delimiter) {
        text[i] = '\0';
        *save_this = &text[i];
        return text;
      }
      i++;
    }
    return NULL;
  } else if ((save_this != NULL) && (*save_this != NULL)) {
    /* Old text. */
    int i = 0;
    char *start = *save_this;
    while ((*save_this)[i] != '\0') {
      if ((*save_this)[i] == delimiter) {
        (*save_this)[i] = '\0';
        *save_this = &((*save_this)[i + 1]);
        return start;
      }
      i++;
    }
    *save_this = NULL;
    save_this = NULL;
    return start;
  }
  return NULL;
}
