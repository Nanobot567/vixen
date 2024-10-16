#include <stdbool.h>

#include "../libc/include/string.h"

char *itoa(int num, char *str, int base) {
  int i = 0;
  char isNegNum = 0;
  /*Handle 0 explicitly,
    otherwise empty string is printed for 0 */
  if (num == 0) {
    str[i++] = '0';
    str[i] = '\0';
  } else {
    // In library itoa function -ve numbers handled only with
    // base 10. SO here we are also following same concept
    if ((num < 0) && (base == 10)) {
      isNegNum = 1;
      num = -num; // make num positive
    }
    // Process individual digits
    do {
      const int rem = (num % base);
      str[i++] = (rem > 9) ? ((rem - 10) + 'a') : (rem + '0');
      num = num / base;
    } while (num != 0);
    // If number is negative, append '-'
    if (isNegNum) {
      str[i++] = '-';
    }
    // Append string terminator
    str[i] = '\0';
    // Reverse the string
    int start;
    int end = strlen(str) - 1;
    for (start = 0; start < end; ++start, --end) {
      const char ch = str[start];
      str[start] = str[end];
      str[end] = ch;
    }
  }
  return str;
}

int atoi(char *str) {
  int num = 0;
  int i = 0;
  bool isNegative = false;
  if (str[i] == '-') {
    isNegative = true;
    i++;
  }
  while (str[i] && (str[i] >= '0' && str[i] <= '9')) {
    num = num * 10 + (str[i] - '0');
    i++;
  }
  if (isNegative) {
    num = -1 * num;
  }
  return num;
}
