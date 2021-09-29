#ifndef _ST7789_IPS_H_
#define _ST7789_IPS_H_

#include "st7789_delay.h"
#include "st7789_font.h"
#include "st7789_gpio.h"
#include "st7789_spi.h"

typedef enum {
  RED = 0xF800,
  YELLOW = 0xFFE0,
  BLUE = 0x001F,
  GREEN = 0x0400,
  WHITE = 0xFFFF,
  BLACK = 0x0000
} colors_t;

uint16_t st7789_width;
uint16_t st7789_height;
uint16_t st7789_buffer[400 * 400];
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
void st7789_draw_chinese_char(uint16_t x, uint16_t y, fonts_t type, uint8_t *ch,
                              uint16_t fcolor);
void st7789_draw_chinese_string(uint16_t x, uint16_t y, fonts_t font,
                                uint8_t *str, uint16_t fcolor);
void st7789_draw_ascii_char(uint16_t x, uint16_t y, fonts_t type, uint8_t ch,
                            uint16_t fcolor);
void st7789_display_font_data(uint16_t x, uint16_t y, uint16_t fontwidth,
                              uint16_t fontheight, uint16_t fontsize,
                              uint8_t *buf, uint16_t color, uint8_t spec);
void st7789_draw_ascii_string(uint16_t x, uint16_t y, fonts_t font,
                              uint8_t *str, uint16_t fcolor);
void st7789_draw_string_mixed(uint16_t x, uint16_t y, fonts_t ascfont,
                              fonts_t cnfont, uint8_t *str, uint16_t color);
void st7789_draw_pic(uint16_t x, uint16_t y, uint16_t pic_height,
                     uint16_t pic_width, uint8_t *pic);
void st7789_send_buf();
void st7789_clear_buf();
#endif