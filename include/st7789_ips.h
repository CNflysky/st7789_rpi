#ifndef _ST7789_IPS_H_
#define _ST7789_IPS_H_

#include <stdarg.h>

#include "st7789_delay.h"
#include "st7789_font.h"
#include "st7789_gpio.h"
#include "st7789_spi.h"

/**
 * standard colors
 */
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
uint16_t st7789_buffer[240 * 320];  // max resolution:240*320
/**
 *
 * @brief init the display.
 * @param width width
 * @param height height
 * @return None
 * @note
 */
void st7789_init(uint16_t width, uint16_t height);

/**
 *
 * @brief set display area
 * @param x0 x start pos
 * @param y0 y start pos
 * @param x1 x end pos
 * @param x2 y end pos
 * @return None
 * @note
 */
void st7789_set_display_area(uint16_t x0, uint16_t y0, uint16_t x1,
                             uint16_t y1);

/**
 *
 * @brief draw a pixel
 * @param x x pos
 * @param y y pos
 * @param color pixel color
 * @return None
 * @note
 */
void st7789_draw_pixel(uint16_t x, uint16_t y, uint16_t color);

/**
 *
 * @brief fill screen
 * @param color color
 * @return None
 * @note
 */
void st7789_fill_screen(uint16_t color);

/**
 *
 * @brief clear screen
 * @param None
 * @return None
 * @note
 */
void st7789_clear_screen();

/**
 *
 * @brief draw line
 * @param x1 x start pos
 * @param y1 y start pos
 * @param x2 x end pos
 * @param y2 y end pos
 * @param color line color
 * @return None
 * @note
 */
void st7789_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                      uint16_t color);
/**
 *
 * @brief component of st7789_draw_circle. shouldn't be called directly,see
 * st7789_draw_circle
 */
static void st7789_precircle(uint16_t xc, uint16_t yc, uint16_t x, uint16_t y,
                      uint16_t color);
/**
 *
 * @brief draw circle
 * @param xc x pos of circle center.
 * @param yc y pos of circle center.
 * @param radius circle radius
 * @param color color
 * @param filled fill or not fill
 * @return None
 * @note
 */
void st7789_draw_circle(uint16_t xc, uint16_t yc, uint16_t radius,
                        uint16_t color, bool filled);
/**
 *
 * @brief draw a rectangle
 * @param x1 x start pos
 * @param y1 y start pos
 * @param x2 x end pos
 * @param y2 y end pos
 * @param color color
 * @param filled fill or not fill
 * @return
 * @note
 */
void st7789_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                           uint16_t color, bool filled);
/**
 *
 * @brief draw a chinese char
 * @param x x pos
 * @param y y pos
 * @param type font type (see fonts_t)
 * @param ch char
 * @param color char color
 * @return None
 * @note
 */
void st7789_draw_chinese_char(uint16_t x, uint16_t y, fonts_t type, uint8_t *ch,
                              uint16_t fcolor);
/**
 *
 * @brief draw a chinese string
 * @param x x pos
 * @param y y pos
 * @param type font type (see fonts_t)
 * @param str string
 * @param color string color
 * @return None
 * @note
 */
void st7789_draw_chinese_string(uint16_t x, uint16_t y, fonts_t font,
                                uint8_t *str, uint16_t fcolor);
/**
 *
 * @brief draw a ascii char
 * @param x x pos
 * @param y y pos
 * @param type font type (see fonts_t)
 * @param ch char
 * @param color char color
 * @return None
 * @note
 */
void st7789_draw_ascii_char(uint16_t x, uint16_t y, fonts_t type, uint8_t ch,
                            uint16_t fcolor);
/**
 *
 * @brief component of char display functions. shouldn't be called directly
 */
static void st7789_draw_font_data(uint16_t x, uint16_t y, uint16_t fontwidth,
                           uint16_t fontheight, uint16_t fontsize, uint8_t *buf,
                           uint16_t color, uint8_t spec);
/**
 *
 * @brief draw a ascii string
 * @param x x pos
 * @param y y pos
 * @param type font type (see fonts_t)
 * @param str string
 * @param color string color
 * @return None
 * @note
 */
void st7789_draw_ascii_string(uint16_t x, uint16_t y, fonts_t font,
                              uint8_t *str, uint16_t fcolor);

/**
 *
 * @brief draw a string
 * @param x x pos
 * @param y y pos
 * @param ascfont ascii font type (see fonts_t)
 * @param cnfont gb2312 font type (see fonts_t)
 * @param str string
 * @param color string color
 * @return None
 * @note
 */
void st7789_draw_string(uint16_t x, uint16_t y, fonts_t ascfont, fonts_t cnfont,
                        uint8_t *str, uint16_t color);
/**
 *
 * @brief draw a pic
 * @param x x start pos
 * @param y y start pos
 * @param pic_width pic width
 * @param pic_height pic height
 * @param pic pic
 * @return None
 * @note
 */
void st7789_draw_pic(uint16_t x, uint16_t y, uint16_t pic_width,
                     uint16_t pic_height, uint8_t *pic);
/**
 *
 * @brief printf on screen
 * @param x x pos
 * @param y y pos
 * @param ascfont ascii font type (see fonts_t)
 * @param gbfont gb2312 font type (see fonts_t)
 * @param color string color
 * @param fmt format (see printf)
 * @param ... param
 * @return None
 * @note
 */
void st7789_printf(uint16_t x, uint16_t y, fonts_t ascfont, fonts_t gbfont,
                   uint16_t color, const char *fmt, ...)
    __attribute__((format(printf, 6, 7)));
/**
 *
 * @brief send buffer
 * @param None
 * @return None
 * @note
 */
void st7789_send_buf();
/**
 *
 * @brief clear buffer
 * @param None
 * @return None
 * @note
 */
void st7789_clear_buf();

#endif