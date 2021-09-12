#ifndef _ST7789_FONT_H_
#define _ST7789_FONT_H_
typedef enum {
  gb2312_12x12,
  gb2312_15x16,
  gb2312_24x24,
  gb2312_32x32,
  gb2312_extend_6x12,
  ascii_standard_6x12,
  ascii_arial_12x12,
  ascii_time_12x12,
  gb2312_extend_8x16,
  asccii_extend_8x16,
  ascii_standard_5x7,
  ascii_standard_7x8,
  ascii_arial_16x16,
  ascii_time_16x16,
  gb2312_extend_12x24,
  ascii_12x24,
  ascii_arial_24x24,
  ascii_time_24x24,
  gb2312_extend_16x32,
  ascii_16x32,
  ascii_arial_32x32,
  ascii_time_32x32,
  gb2312_special_8x16
} fonts_t;

#include <iconv.h>

#include "st7789_spi.h"

int st7789_gt30_spi_fd;
int st7789_gt30_spi_speed;

void st7789_gt30_spi_open(uint8_t* path);
void st7789_gt30_spi_set_mode(uint8_t mode);
void st7789_gt30_spi_set_speed(uint32_t speed);
void st7789_gt30_get_char_data(uint8_t* addr, uint8_t* data, uint16_t len);
void st7789_gt30_convert_utf8_to_gb2312(uint8_t* str, uint16_t in_len,
                                        uint8_t* outbuf, uint16_t out_len);
void st7789_gt30_caculate_chinese_address(fonts_t type, uint8_t msb,
                                          uint8_t lsb, uint8_t* addrbuf);

#endif