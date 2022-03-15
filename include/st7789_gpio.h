#ifndef _ST7789_GPIO_H_
#define _ST7789_GPIO_H_
#include "st7789_def.h"
void st7789_gpiod_request_gpio(st7789config_t *config, st7789_t *st7789);
void st7789_gpiod_release_resources(st7789_t *st7789);
#endif