#ifndef _STRING_H
#define _STRING_H 1

#include <stddef.h>

int memcmp(const void*, const void*, size_t);
void* memcpy(void* __restrict, const void* __restrict, size_t);
void* memmove(void*, const void*, size_t);
void* memset(void*, int, size_t);
size_t strlen(const char*);
int strcmp(char s1[], char s2[]);
char *strtok_r(char *text, char delimiter, char **save_this);
char* substr(char *src, int offset, int length);
char *strtok(char *s, char *delim);

#endif
