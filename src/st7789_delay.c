#include "st7789_delay.h"
void st7789_delay(int ms) {
  struct timeval delay = {.tv_sec = 0, .tv_usec = ms * 1000};
  select(0, NULL, NULL, NULL, &delay);
}