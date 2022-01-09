#ifndef _ST7789_IPS_H_
#define _ST7789_IPS_H_
#include "st7789_multidev.h"
st7789_t *default_st7789;
gt30_t *default_gt30;
void st7789_init(st7789config_t *config, st7789_t *st7789);
void st7789_set_default_device(st7789_t *st7789);
void st7789_set_default_fontchip(gt30_t *gt30);
void st7789_draw_pixel(uint16_t x, uint16_t y, uint16_t color);
void st7789_clear_buf();
void st7789_set_display_area(uint16_t x0, uint16_t y0, uint16_t x1,
                             uint16_t y1);
void st7789_fill_screen(uint16_t color);
void st7789_send_buf();
void st7789_clear_screen();
void st7789_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                      uint16_t color);
void st7789_draw_circle(uint16_t xc, uint16_t yc, uint16_t radius,
                        uint16_t color, bool filled);
void st7789_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                           uint16_t color, bool filled);
void st7789_draw_chinese_string(uint16_t x, uint16_t y, fonts_t font,
                                uint8_t *str, uint16_t fcolor);
void st7789_draw_chinese_char(uint16_t x, uint16_t y, fonts_t type, uint8_t *ch,
                              uint16_t fcolor);
void st7789_draw_ascii_char(uint16_t x, uint16_t y, fonts_t type, uint8_t ch,
                            uint16_t fcolor);
void st7789_draw_ascii_string(uint16_t x, uint16_t y, fonts_t font,
                              uint8_t *str, uint16_t fcolor);
void st7789_draw_string(uint16_t x, uint16_t y, fonts_t ascfont, fonts_t cnfont,
                        uint8_t *str, uint16_t color);
void st7789_printf(uint16_t x, uint16_t y, fonts_t ascfont, fonts_t gbfont,
                   uint16_t color, const char *fmt, ...);
void st7789_draw_pic(uint16_t x, uint16_t y, uint16_t pic_width,
                     uint16_t pic_height, uint8_t *pic);
#endif