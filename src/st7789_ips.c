#include "st7789_ips.h"
void st7789_init(uint16_t width, uint16_t height) {
  st7789_height = height;
  st7789_width = width;
  gpiod_line_set_value(st7789_reset, 0);
  st7789_delay(50);
  gpiod_line_set_value(st7789_reset, 1);  // hw reset
  st7789_delay(50);
  st7789_spi_write_8bit(COMMAND, 0x36);
  st7789_spi_write_8bit(DATA, 0x00);
  st7789_spi_write_8bit(COMMAND, 0x3A);
  st7789_spi_write_8bit(DATA, 0x05);
  st7789_spi_write_8bit(COMMAND, 0xB2);
  st7789_spi_write_8bit(DATA, 0x0C);
  st7789_spi_write_8bit(DATA, 0x0C);
  st7789_spi_write_8bit(DATA, 0x00);
  st7789_spi_write_8bit(DATA, 0x33);
  st7789_spi_write_8bit(DATA, 0x33);
  st7789_spi_write_8bit(COMMAND, 0xB7);
  st7789_spi_write_8bit(DATA, 0x35);
  st7789_spi_write_8bit(COMMAND, 0xBB);
  st7789_spi_write_8bit(DATA, 0x19);
  st7789_spi_write_8bit(COMMAND, 0xC0);
  st7789_spi_write_8bit(DATA, 0x2C);
  st7789_spi_write_8bit(COMMAND, 0xC2);
  st7789_spi_write_8bit(DATA, 0x01);
  st7789_spi_write_8bit(COMMAND, 0xC3);
  st7789_spi_write_8bit(DATA, 0x12);
  st7789_spi_write_8bit(COMMAND, 0xC4);
  st7789_spi_write_8bit(DATA, 0x20);
  st7789_spi_write_8bit(COMMAND, 0xC6);
  st7789_spi_write_8bit(DATA, 0x0F);
  st7789_spi_write_8bit(COMMAND, 0xD0);
  st7789_spi_write_8bit(DATA, 0xA4);
  st7789_spi_write_8bit(DATA, 0xA1);
  st7789_spi_write_8bit(COMMAND, 0xE0);
  st7789_spi_write_8bit(DATA, 0xD0);
  st7789_spi_write_8bit(DATA, 0x04);
  st7789_spi_write_8bit(DATA, 0x0D);
  st7789_spi_write_8bit(DATA, 0x11);
  st7789_spi_write_8bit(DATA, 0x13);
  st7789_spi_write_8bit(DATA, 0x2B);
  st7789_spi_write_8bit(DATA, 0x3F);
  st7789_spi_write_8bit(DATA, 0x54);
  st7789_spi_write_8bit(DATA, 0x4C);
  st7789_spi_write_8bit(DATA, 0x18);
  st7789_spi_write_8bit(DATA, 0x0D);
  st7789_spi_write_8bit(DATA, 0x0B);
  st7789_spi_write_8bit(DATA, 0x1F);
  st7789_spi_write_8bit(DATA, 0x23);
  st7789_spi_write_8bit(COMMAND, 0xE1);
  st7789_spi_write_8bit(DATA, 0xD0);
  st7789_spi_write_8bit(DATA, 0x04);
  st7789_spi_write_8bit(DATA, 0x0C);
  st7789_spi_write_8bit(DATA, 0x11);
  st7789_spi_write_8bit(DATA, 0x13);
  st7789_spi_write_8bit(DATA, 0x2C);
  st7789_spi_write_8bit(DATA, 0x3F);
  st7789_spi_write_8bit(DATA, 0x44);
  st7789_spi_write_8bit(DATA, 0x51);
  st7789_spi_write_8bit(DATA, 0x2F);
  st7789_spi_write_8bit(DATA, 0x1F);
  st7789_spi_write_8bit(DATA, 0x1F);
  st7789_spi_write_8bit(DATA, 0x20);
  st7789_spi_write_8bit(DATA, 0x23);
  st7789_spi_write_8bit(COMMAND, 0x21);
  st7789_spi_write_8bit(COMMAND, 0x11);
  st7789_clear_buf();
  st7789_clear_screen();
  st7789_send_buf();
  st7789_spi_write_8bit(COMMAND, 0x29);
  st7789_spi_write_8bit(COMMAND, 0x36);
  st7789_spi_write_8bit(DATA, 0x00);
}

void st7789_set_display_area(uint16_t x0, uint16_t y0, uint16_t x1,
                             uint16_t y1) {
  st7789_spi_write_8bit(COMMAND, 0x2A);
  st7789_spi_write_16bit(x0);
  st7789_spi_write_16bit(x1);

  st7789_spi_write_8bit(COMMAND, 0x2B);
  st7789_spi_write_16bit(y0);
  st7789_spi_write_16bit(y1);

  st7789_spi_write_8bit(COMMAND, 0x2C);  // gram write command
}

void st7789_draw_pixel(uint16_t x, uint16_t y, uint16_t color) {
  st7789_buffer[y * st7789_width + x] = color;
}

void st7789_fill_screen(uint16_t color) {
  for (uint32_t i = 0; i < (st7789_height * st7789_width) - 1; i++)
    st7789_buffer[i] = color;
}

void st7789_clear_screen() { st7789_fill_screen(BLACK); }

void st7789_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                      uint16_t color) {
  int16_t xerr = 0, yerr = 0, delta_x = x2 - x1, delta_y = y2 - y1, distance;
  uint16_t incx, incy, uRow = x1, uCol = y1;

  if (delta_x > 0)
    incx = 1;
  else if (delta_x == 0)
    incx = 0;
  else {
    incx = -1;
    delta_x = -delta_x;
  }

  if (delta_y > 0)
    incy = 1;
  else if (delta_y == 0)
    incy = 0;
  else {
    incy = -1;
    delta_y = -delta_y;
  }

  (delta_x > delta_y) ? (distance = delta_x) : (distance = delta_y);
  for (uint16_t t = 0; t <= distance + 1; t++) {
    st7789_draw_pixel(uRow, uCol, color);
    xerr += delta_x;
    yerr += delta_y;
    if (xerr > distance) {
      xerr -= distance;
      uRow += incx;
    }
    if (yerr > distance) {
      yerr -= distance;
      uCol += incy;
    }
  }
}

void st7789_precircle(uint16_t xc, uint16_t yc, uint16_t x, uint16_t y,
                      uint16_t color) {
  st7789_draw_pixel(xc + x, yc + y, color);
  st7789_draw_pixel(xc - x, yc + y, color);
  st7789_draw_pixel(xc + x, yc - y, color);
  st7789_draw_pixel(xc - x, yc - y, color);
  st7789_draw_pixel(xc + y, yc + x, color);
  st7789_draw_pixel(xc - y, yc + x, color);
  st7789_draw_pixel(xc + y, yc - x, color);
  st7789_draw_pixel(xc - y, yc - x, color);
}

void st7789_draw_circle(uint16_t xc, uint16_t yc, uint16_t radius,
                        uint16_t color, bool filled) {
  int16_t x = 0, y = radius, yi, fontwidth = 3 - 2 * radius;
  if (filled) {
    while (x <= y) {
      for (yi = x; yi <= y; yi++) st7789_precircle(xc, yc, x, yi, color);
      if (fontwidth < 0)
        fontwidth = fontwidth + 4 * x + 6;
      else {
        fontwidth = fontwidth + 4 * (x - y) + 10;
        y--;
      }
      x++;
    }
  } else {
    while (x <= y) {
      st7789_precircle(xc, yc, x, y, color);
      if (fontwidth < 0)
        fontwidth = fontwidth + 4 * x + 6;
      else {
        fontwidth = fontwidth + 4 * (x - y) + 10;
        y--;
      }
      x++;
    }
  }
}

void st7789_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                           uint16_t color, bool filled) {
  if (filled) {
    for (uint16_t i = y1; i < y2; i++)
      for (uint16_t j = x1; j < x2; j++) st7789_draw_pixel(j, i, color);
  } else {
    st7789_draw_line(x1, y1, x2, y1, color);
    st7789_draw_line(x1, y1, x1, y2, color);
    st7789_draw_line(x1, y2, x2, y2, color);
    st7789_draw_line(x2, y1, x2, y2, color);
  }
}

void st7789_draw_chinese_string(uint16_t x, uint16_t y, fonts_t font,
                                uint8_t *str, uint16_t fcolor) {
  uint8_t distance = st7789_gt30_get_font_detail(font, WIDTH), x0 = x;
  uint8_t buf[3] = {0x00};
  uint16_t offset = 0;
  for (uint8_t i = 0; i < strlen(str) / 3; i++) {
    memcpy(buf, str + offset, 3);
    st7789_draw_chinese_char(x0, y, font, buf, fcolor);
    offset += 3;
    x0 += distance;
  }
}

void st7789_draw_chinese_char(uint16_t x, uint16_t y, fonts_t type, uint8_t *ch,
                              uint16_t fcolor) {
  /* How it works
* 1st:get some font data related to the given font type
* 2nd:convert utf8-encoded chinese char into gb2312-encoded form.
* 3rd:put gb2312-encoded addr into st7789_gt30_get_gb2312_addr() and gets the
corresponding addr.
* 4th:st7789_gt30_read_data() read data from the GT30 font chip and put them
into a buffer(buf).
* 5th:display buf on screen(put them into st7789_buffer).
*/
  uint16_t x0 = x;
  uint32_t font_addr = st7789_gt30_get_font_detail(type, BASEADDR);
  uint16_t fontsize = st7789_gt30_get_font_detail(type, SIZE),
           fontwidth = st7789_gt30_get_font_detail(type, WIDTH);
  uint8_t gb2312_code[2] = {0x00};
  st7789_gt30_convert_utf8_to_gb2312(ch, sizeof ch, gb2312_code,
                                     sizeof gb2312_code);
  uint8_t addr_buf[3];
  st7789_gt30_get_gb2312_addr(type, gb2312_code[0], gb2312_code[1], font_addr,
                              fontsize, addr_buf);
  uint8_t data[128] = {0x00};
  st7789_gt30_read_data(addr_buf, data, fontsize);
  st7789_delay(1);
  st7789_display_font_data(x, y, fontwidth, fontwidth, fontsize, data, fcolor,
                           0);
}

void st7789_display_font_data(uint16_t x, uint16_t y, uint16_t fontwidth,
                              uint16_t fontheight, uint16_t fontsize,
                              uint8_t *buf, uint16_t color, uint8_t spec) {
  uint16_t x0 = x;
  st7789_set_display_area(x, y, x + fontwidth - 1, y + fontheight - 1);
  for (uint8_t i = spec; i < fontsize; i++) {
    for (uint8_t k = 0; k < 8; k++) {
      if (buf[i] & (0x80 >> k)) st7789_draw_pixel(x, y, color);
      x++;
      if ((x - x0) == fontwidth) {
        x = x0;
        y++;
        break;
      }
    }
  }
}

void st7789_draw_ascii_char(uint16_t x, uint16_t y, fonts_t type, uint8_t ch,
                            uint16_t fcolor) {
  /* How it works
  * 1st:get some font data related to the given font type
  * 2nd:adjust some special font type(ascii_std_5x7)
  * 3rd:split baseaddr into 3 parts,and put them into addr_buf.
  * 4th:st7789_gt30_read_data() read data from the GT30 font chip and put them
  into a buffer(buf).
  * 5th:display buf on screen(put them into st7789_buffer).
  */
  uint32_t baseaddr = st7789_gt30_get_font_detail(type, BASEADDR);
  uint16_t fontsize = st7789_gt30_get_font_detail(type, SIZE),
           fontwidth = st7789_gt30_get_font_detail(type, WIDTH),
           fontheight = st7789_gt30_get_font_detail(type, HEIGHT),
           spec = st7789_gt30_get_font_detail(type, OFFSET);
  uint8_t offset = 0;
  if (type == ascii_standard_5x7) offset = 8;
  if (offset == 0) offset = fontsize;
  uint8_t buf[130] = {0x00};
  uint32_t addr = st7789_gt30_get_ascii_addr(baseaddr, offset, ch);
  uint8_t addr_buf[3] = {(addr & 0xff0000) >> 16, (addr & 0xff00) >> 8,
                         addr & 0xff};
  st7789_gt30_read_data(addr_buf, buf, fontsize);
  st7789_display_font_data(x, y, fontwidth, fontheight, fontsize, buf, fcolor,
                           spec);
}

void st7789_draw_ascii_string(uint16_t x, uint16_t y, fonts_t font,
                              uint8_t *str, uint16_t fcolor) {
  uint8_t distance = st7789_gt30_get_font_detail(font, WIDTH), x0 = x;
  for (uint8_t i = 0; i < strlen(str); i++) {
    st7789_draw_ascii_char(x0, y, font, str[i], fcolor);
    x0 += distance;
  }
}

void st7789_draw_string_mixed(uint16_t x, uint16_t y, fonts_t ascfont,
                              fonts_t cnfont, uint8_t *str, uint16_t color) {
  uint16_t asc_distance = st7789_gt30_get_font_detail(ascfont, WIDTH),
           cn_distance = st7789_gt30_get_font_detail(cnfont, WIDTH), x0 = x;
  uint8_t cn_buf[3] = {0x00};
  for (uint16_t i = 0; i < strlen(str); i++) {
    if (str[i] >= 0x20 && str[i] <= 0x7E) {
      st7789_draw_ascii_char(x0, y, ascfont, str[i], color);
      x0 += asc_distance;
    } else {
      memcpy(cn_buf, &str[i], 3);  // chinese
      i += 2;
      st7789_draw_chinese_char(x0, y, cnfont, cn_buf, color);
      x0 += cn_distance;
    }
  }
}

void st7789_draw_pic(uint16_t x, uint16_t y, uint16_t pic_width,
                     uint16_t pic_height, uint8_t *pic) {
  st7789_set_display_area(x, y, x + pic_width - 1, y + pic_height - 1);
  st7789_spi_write_8bytes(pic, pic_height * pic_width * 2);
}

void st7789_send_buf() {
  st7789_set_display_area(0, 0, st7789_width - 1, st7789_height - 1);
  st7789_spi_write_16bytes(st7789_buffer, st7789_height * st7789_width);
}

void st7789_clear_buf() { memset(st7789_buffer, 0x0000, sizeof st7789_buffer); }