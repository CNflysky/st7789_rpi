#ifndef _ST7789_MULTIDEV_H_
#define _ST7789_MULTIDEV_H_
#include "st7789_def.h"
#include "st7789_font.h"
#include "st7789_gpio.h"
#include "st7789_spi.h"
void st7789_multidev_draw_pixel(st7789_t *st7789, uint16_t x, uint16_t y,
                       uint16_t color);
void st7789_multidev_clear_buf(st7789_t *st7789);
void st7789_multidev_set_display_area(st7789_t *st7789, uint16_t x0, uint16_t y0,
                             uint16_t x1, uint16_t y1);
void st7789_multidev_fill_screen(st7789_t *st7789, uint16_t color);
void st7789_multidev_send_buf(st7789_t *st7789);
void st7789_multidev_clear_screen(st7789_t *st7789);
void st7789_multidev_draw_line(st7789_t *st7789, uint16_t x1, uint16_t y1, uint16_t x2,
                      uint16_t y2, uint16_t color);
void st7789_multidev_draw_circle(st7789_t *st7789, uint16_t xc, uint16_t yc,
                        uint16_t radius, uint16_t color, bool filled);
void st7789_multidev_draw_rectangle(st7789_t *st7789, uint16_t x1, uint16_t y1,
                           uint16_t x2, uint16_t y2, uint16_t color,
                           bool filled);
void st7789_multidev_draw_chinese_string(st7789_t *st7789, gt30_t *gt30, uint16_t x,
                                uint16_t y, fonts_t font, uint8_t *str,
                                uint16_t fcolor);
void st7789_multidev_draw_chinese_char(st7789_t *st7789, gt30_t *gt30, uint16_t x,
                              uint16_t y, fonts_t type, uint8_t *ch,
                              uint16_t fcolor);
void st7789_multidev_draw_ascii_char(st7789_t *st7789, gt30_t *gt30, uint16_t x,
                            uint16_t y, fonts_t type, uint8_t ch,
                            uint16_t fcolor);
void st7789_multidev_draw_ascii_string(st7789_t *st7789, gt30_t *gt30, uint16_t x,
                              uint16_t y, fonts_t font, uint8_t *str,
                              uint16_t fcolor);
void st7789_multidev_draw_string(st7789_t *st7789, gt30_t *gt30, uint16_t x, uint16_t y,
                        fonts_t ascfont, fonts_t cnfont, uint8_t *str,
                        uint16_t color);
void st7789_multidev_printf(st7789_t *st7789, gt30_t *gt30, uint16_t x, uint16_t y,
                   fonts_t ascfont, fonts_t gbfont, uint16_t color,
                   const char *fmt, ...);
void st7789_multidev_draw_pic(st7789_t *st7789, uint16_t x, uint16_t y,
                     uint16_t pic_width, uint16_t pic_height, uint8_t *pic);

#endif