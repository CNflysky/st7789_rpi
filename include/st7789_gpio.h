#ifndef _ST7789_GPIO_H_
#define _ST7789_GPIO_H_

#include <gpiod.h>
#include <stdint.h>
#include <errno.h>
#include <stdio.h>
struct gpiod_line *st7789_dc;
struct gpiod_line *st7789_reset;
struct gpiod_line *st7789_gpiod_request_gpio(const uint8_t *gpiochip,
                                             const uint8_t *linename, int pin);

#endif