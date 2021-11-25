#ifndef _ST7789_DELAY_H_
#define _ST7789_DELAY_H_
/**
 * @brief delay program with given miliseconds .
 * @param ms delay time (ms).
 * @return None
*/
void st7789_delay(int ms);
#include <stddef.h>
#include <sys/select.h>
#include <sys/time.h>
#endif