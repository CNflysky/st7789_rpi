#include "st7789_def.h"
void pabort(const char *str) {
  perror(str);
  exit(errno);
}