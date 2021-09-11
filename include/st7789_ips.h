#ifndef _ST7789_IPS_H_
#define _ST7789_IPS_H_

#include "st7789_delay.h"
#include "st7789_gpio.h"
#include "st7789_spi.h"
uint16_t st7789_width;
uint16_t st7789_height;
void st7789_init(uint16_t height, uint16_t width);
void st7789_set_display_area(uint16_t x0, uint16_t y0, uint16_t x1,
                             uint16_t y1);
void st7789_draw_point(uint16_t x, uint16_t y, uint16_t color);
void st7789_fill_screen(uint16_t color);
void st7789_clear_screen();
void st7789_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                      uint16_t color);
void st7789_precircle(uint16_t xc, uint16_t yc, uint16_t x, uint16_t y,
                      uint16_t color);
void st7789_draw_circle(uint16_t xc, uint16_t yc, uint16_t radius,
                        uint16_t color, bool filled);
void st7789_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                           uint16_t color, bool filled);
void st7789_draw_char(uint16_t x, uint16_t y, uint8_t num, uint16_t fc,
                      uint16_t bc, uint8_t sizey, uint8_t mode);
// void st7789_draw_string(uint8_t x, uint8_t y, fontname_t font, uint8_t *str);
// void st7789_draw_char(uint8_t x, uint8_t y, fontname_t font, uint8_t ch);
#endif