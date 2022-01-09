#include "st7789_ips.h"

void st7789_init(st7789config_t *config, st7789_t *st7789) {
  st7789->width = config->width;
  st7789->height = config->height;
  st7789->spi_speed = config->spi_speed;
  st7789_spi_open(config, st7789);
  st7789_spi_set_bit(st7789);
  st7789_spi_set_mode(st7789);
  st7789_spi_set_speed(config, st7789);
  st7789_gpiod_request_gpio(config, st7789);
  gpiod_line_set_value(st7789->gpio_reset, 0);
  usleep(50000);  // 50ms
  gpiod_line_set_value(st7789->gpio_reset, 1);
  usleep(50000);  // 50ms
  st7789_spi_write_8bit(st7789, COMMAND, 0x36);
  st7789_spi_write_8bit(st7789, DATA, 0x00);
  st7789_spi_write_8bit(st7789, COMMAND, 0x3A);
  st7789_spi_write_8bit(st7789, DATA, 0x05);
  st7789_spi_write_8bit(st7789, COMMAND, 0xB2);
  st7789_spi_write_8bit(st7789, DATA, 0x0C);
  st7789_spi_write_8bit(st7789, DATA, 0x0C);
  st7789_spi_write_8bit(st7789, DATA, 0x00);
  st7789_spi_write_8bit(st7789, DATA, 0x33);
  st7789_spi_write_8bit(st7789, DATA, 0x33);
  st7789_spi_write_8bit(st7789, COMMAND, 0xB7);
  st7789_spi_write_8bit(st7789, DATA, 0x35);
  st7789_spi_write_8bit(st7789, COMMAND, 0xBB);
  st7789_spi_write_8bit(st7789, DATA, 0x19);
  st7789_spi_write_8bit(st7789, COMMAND, 0xC0);
  st7789_spi_write_8bit(st7789, DATA, 0x2C);
  st7789_spi_write_8bit(st7789, COMMAND, 0xC2);
  st7789_spi_write_8bit(st7789, DATA, 0x01);
  st7789_spi_write_8bit(st7789, COMMAND, 0xC3);
  st7789_spi_write_8bit(st7789, DATA, 0x12);
  st7789_spi_write_8bit(st7789, COMMAND, 0xC4);
  st7789_spi_write_8bit(st7789, DATA, 0x20);
  st7789_spi_write_8bit(st7789, COMMAND, 0xC6);
  st7789_spi_write_8bit(st7789, DATA, 0x0F);
  st7789_spi_write_8bit(st7789, COMMAND, 0xD0);
  st7789_spi_write_8bit(st7789, DATA, 0xA4);
  st7789_spi_write_8bit(st7789, DATA, 0xA1);
  st7789_spi_write_8bit(st7789, COMMAND, 0xE0);
  st7789_spi_write_8bit(st7789, DATA, 0xD0);
  st7789_spi_write_8bit(st7789, DATA, 0x04);
  st7789_spi_write_8bit(st7789, DATA, 0x0D);
  st7789_spi_write_8bit(st7789, DATA, 0x11);
  st7789_spi_write_8bit(st7789, DATA, 0x13);
  st7789_spi_write_8bit(st7789, DATA, 0x2B);
  st7789_spi_write_8bit(st7789, DATA, 0x3F);
  st7789_spi_write_8bit(st7789, DATA, 0x54);
  st7789_spi_write_8bit(st7789, DATA, 0x4C);
  st7789_spi_write_8bit(st7789, DATA, 0x18);
  st7789_spi_write_8bit(st7789, DATA, 0x0D);
  st7789_spi_write_8bit(st7789, DATA, 0x0B);
  st7789_spi_write_8bit(st7789, DATA, 0x1F);
  st7789_spi_write_8bit(st7789, DATA, 0x23);
  st7789_spi_write_8bit(st7789, COMMAND, 0xE1);
  st7789_spi_write_8bit(st7789, DATA, 0xD0);
  st7789_spi_write_8bit(st7789, DATA, 0x04);
  st7789_spi_write_8bit(st7789, DATA, 0x0C);
  st7789_spi_write_8bit(st7789, DATA, 0x11);
  st7789_spi_write_8bit(st7789, DATA, 0x13);
  st7789_spi_write_8bit(st7789, DATA, 0x2C);
  st7789_spi_write_8bit(st7789, DATA, 0x3F);
  st7789_spi_write_8bit(st7789, DATA, 0x44);
  st7789_spi_write_8bit(st7789, DATA, 0x51);
  st7789_spi_write_8bit(st7789, DATA, 0x2F);
  st7789_spi_write_8bit(st7789, DATA, 0x1F);
  st7789_spi_write_8bit(st7789, DATA, 0x1F);
  st7789_spi_write_8bit(st7789, DATA, 0x20);
  st7789_spi_write_8bit(st7789, DATA, 0x23);
  st7789_spi_write_8bit(st7789, COMMAND, 0x21);
  st7789_spi_write_8bit(st7789, COMMAND, 0x11);
  st7789_multidev_clear_buf(st7789);
  st7789_multidev_send_buf(st7789);
  st7789_spi_write_8bit(st7789, COMMAND, 0x29);
  st7789_spi_write_8bit(st7789, COMMAND, 0x36);
  st7789_spi_write_8bit(st7789, DATA, 0x00);
}

void st7789_set_default_device(st7789_t *st7789) { default_st7789 = st7789; }
void st7789_set_default_fontchip(gt30_t *gt30) { default_gt30 = gt30; }
void st7789_draw_pixel(uint16_t x, uint16_t y, uint16_t color) {
  st7789_multidev_draw_pixel(default_st7789, x, y, color);
}
void st7789_clear_buf() { st7789_multidev_clear_buf(default_st7789); }
void st7789_set_display_area(uint16_t x0, uint16_t y0, uint16_t x1,
                             uint16_t y1) {
  st7789_multidev_set_display_area(default_st7789, x0, y0, x1, y1);
}
void st7789_fill_screen(uint16_t color) {
  st7789_multidev_fill_screen(default_st7789, color);
}
void st7789_send_buf() { st7789_multidev_send_buf(default_st7789); }
void st7789_clear_screen() { st7789_multidev_clear_screen(default_st7789); }
void st7789_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                      uint16_t color) {
  st7789_multidev_draw_line(default_st7789, x1, y1, x2, y2, color);
}
void st7789_draw_circle(uint16_t xc, uint16_t yc, uint16_t radius,
                        uint16_t color, bool filled) {
  st7789_multidev_draw_circle(default_st7789, xc, yc, radius, color, filled);
}
void st7789_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                           uint16_t color, bool filled) {
  st7789_multidev_draw_rectangle(default_st7789, x1, y1, x2, y2, color, filled);
}
void st7789_draw_chinese_string(uint16_t x, uint16_t y, fonts_t font,
                                uint8_t *str, uint16_t fcolor) {
  st7789_multidev_draw_chinese_string(default_st7789, default_gt30, x, y, font,
                                      str, fcolor);
}
void st7789_draw_chinese_char(uint16_t x, uint16_t y, fonts_t type, uint8_t *ch,
                              uint16_t fcolor) {
  st7789_multidev_draw_chinese_char(default_st7789, default_gt30, x, y, type,
                                    ch, fcolor);
}
void st7789_draw_ascii_char(uint16_t x, uint16_t y, fonts_t type, uint8_t ch,
                            uint16_t fcolor) {
  st7789_multidev_draw_ascii_char(default_st7789, default_gt30, x, y, type, ch,
                                  fcolor);
}
void st7789_draw_ascii_string(uint16_t x, uint16_t y, fonts_t font,
                              uint8_t *str, uint16_t fcolor) {
  st7789_multidev_draw_ascii_string(default_st7789, default_gt30, x, y, font,
                                    str, fcolor);
}
void st7789_draw_string(uint16_t x, uint16_t y, fonts_t ascfont, fonts_t cnfont,
                        uint8_t *str, uint16_t color) {
  st7789_multidev_draw_string(default_st7789, default_gt30, x, y, ascfont,
                              cnfont, str, color);
}
void st7789_printf(uint16_t x, uint16_t y, fonts_t ascfont, fonts_t gbfont,
                   uint16_t color, const char *fmt, ...) {
  uint8_t buf[256] = {0x00};
  va_list arg;
  va_start(arg, fmt);
  vsprintf(buf, fmt, arg);
  va_end(arg);
  st7789_draw_string(x, y, ascfont, gbfont, buf, color);
}
void st7789_draw_pic(uint16_t x, uint16_t y, uint16_t pic_width,
                     uint16_t pic_height, uint8_t *pic) {
  st7789_multidev_draw_pic(default_st7789, x, y, pic_width, pic_height, pic);
}