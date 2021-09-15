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
  st7789_clear_screen();
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

void st7789_draw_point(uint16_t x, uint16_t y, uint16_t color) {
  st7789_set_display_area(x, y, x + 1, y + 1);
  st7789_spi_write_16bit(color);
}

void st7789_fill_screen(uint16_t color) {
  st7789_set_display_area(0, 0, st7789_width - 1, st7789_height - 1);
  union {
    uint16_t val;
    struct {
      uint8_t lsb;
      uint8_t msb;
    };
  } data_u;
  data_u.val = color;
  uint8_t color_buf[4096] = {0x00};
  uint16_t buffer_mark = 0;
  for (uint16_t i = 0; i < 2048; i++) {
    color_buf[buffer_mark] = data_u.lsb;
    color_buf[buffer_mark + 1] = data_u.msb;
    buffer_mark += 2;
  }
  for (uint8_t i = 0; i < (st7789_width * st7789_height / 2048 + 1); i++)
    st7789_spi_write_8bytes(color_buf, 4096);
}

void st7789_clear_screen() { st7789_fill_screen(BLACK); }

void st7789_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
                      uint16_t color) {
  uint16_t t;
  uint16_t xerr = 0, yerr = 0, delta_x = x2 - x1, delta_y = y2 - y1, distance;
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
  for (t = 0; t <= distance + 1; t++) {
    st7789_draw_point(uRow, uCol, color);
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
  st7789_draw_point(xc + x, yc + y, color);
  st7789_draw_point(xc - x, yc + y, color);
  st7789_draw_point(xc + x, yc - y, color);
  st7789_draw_point(xc - x, yc - y, color);
  st7789_draw_point(xc + y, yc + x, color);
  st7789_draw_point(xc - y, yc + x, color);
  st7789_draw_point(xc + y, yc - x, color);
  st7789_draw_point(xc - y, yc - x, color);
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
    st7789_set_display_area(x1, y1, x2, y2);
    uint16_t buffer[(x2 + 1 - x1) * (y2 + 1 - y1)];
    for (uint16_t i = 0; i < (x2 + 1 - x1) * (y2 + 1 - y1); i++)
      buffer[i] = color;
    st7789_spi_write_16bytes(buffer, (x2 + 1 - x1) * (y2 + 1 - y1));
  } else {
    st7789_draw_line(x1, y1, x2, y1, color);
    st7789_draw_line(x1, y1, x1, y2, color);
    st7789_draw_line(x1, y2, x2, y2, color);
    st7789_draw_line(x2, y1, x2, y2, color);
  }
}

void st7789_draw_chinese_string(uint16_t x, uint16_t y, fonts_t font,
                                uint8_t *str, uint16_t fcolor) {
  uint8_t distance, x0 = x;
  switch (font) {
    case gb2312_12x12:
      distance = 12;
      break;
    case gb2312_15x16:
      distance = 16;
      break;
    case gb2312_24x24:
      distance = 24;
      break;
    case gb2312_32x32:
      distance = 32;
      break;
  }
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
  uint16_t x0 = x;
  uint32_t font_addr = 0x00;
  uint16_t fontsize = 0, fontwidth = 0;
  switch (type) {
    case gb2312_12x12:
      font_addr = 0x0;
      fontsize = 24;
      fontwidth = 12;
      break;
    case gb2312_15x16:
      font_addr = 0x2C9D0;
      fontsize = 32;
      fontwidth = 16;
      break;
    case gb2312_24x24:
      font_addr = 0x68190;
      fontsize = 72;
      fontwidth = 24;
      break;
    case gb2312_32x32:
      font_addr = 0xEDF00;
      fontsize = 128;
      fontwidth = 32;
      break;
  }

  uint8_t gb2312_code[2] = {0x00};
  st7789_gt30_convert_utf8_to_gb2312(ch, sizeof ch, gb2312_code,
                                     sizeof gb2312_code);
  uint8_t addr_buf[3];
  st7789_gt30_caculate_chinese_address(type, gb2312_code[0], gb2312_code[1],
                                       addr_buf);
  uint8_t data[128] = {0x00};
  st7789_gt30_get_char_data(addr_buf, data, fontsize);
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
      if (buf[i] & (0x80 >> k)) st7789_draw_point(x, y, color);
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
  uint16_t fontsize = 0, fontheight = 0, fontwidth = 0, offset = 0, spec = 0;
  uint32_t baseaddr = 0x00;
  switch (type) {
    case ascii_standard_5x7:
      baseaddr = 0x1DDF80;
      fontsize = 7;
      fontheight = 7;
      fontwidth = 5;
      offset = 8;
      break;
    case ascii_standard_6x12:
      baseaddr = 0x1DBE00;
      fontsize = 12;
      fontwidth = 6;
      fontheight = 12;
      break;
    case ascii_standard_7x8:
      baseaddr = 0x1DE280;
      fontsize = 8;
      fontwidth = 7;
      fontheight = 8;
      break;
    case ascii_standard_8x16:
      baseaddr = 0x1DD780;
      fontsize = 16;
      fontwidth = 8;
      fontheight = 16;
      break;
    case ascii_12x24:
      baseaddr = 0x1DFF00;
      fontsize = 48;
      fontwidth = 12;
      fontheight = 24;
      break;
    case ascii_16x32:
      baseaddr = 0x1E5A50;
      fontsize = 64;
      fontwidth = 16;
      fontheight = 32;
      break;
    case ascii_arial_10x12:
      baseaddr = 0x1DC400;
      fontsize = 26;
      fontwidth = 10;
      fontheight = 12;
      spec = 2;
      break;
    case ascii_arial_12x16:
      baseaddr = 0x1DE580;
      fontsize = 34;
      fontwidth = 12;
      fontheight = 16;
      spec = 2;
      break;
    case ascii_arial_20x24:
      baseaddr = 0x1E22D0;
      fontsize = 74;
      fontwidth = 20;
      fontheight = 24;
      spec = 2;
      break;
    case ascii_arial_25x32:
      baseaddr = 0x1E99D0;
      fontsize = 130;
      fontwidth = 25;
      fontheight = 32;
      spec = 2;
      break;
    case ascii_times_10x12:
      baseaddr = 0x1DCDC0;
      fontsize = 26;
      fontwidth = 10;
      fontheight = 12;
      spec = 2;
      break;
    case ascii_times_12x16:
      baseaddr = 0x1DF240;
      fontsize = 34;
      fontwidth = 12;
      fontheight = 16;
      spec = 2;
      break;
    case ascii_times_20x24:
      baseaddr = 0x1E3E90;
      fontsize = 74;
      fontwidth = 20;
      fontheight = 24;
      spec = 2;
      break;
    case ascii_times_25x32:
      baseaddr = 0x1ECA90;
      fontsize = 130;
      fontwidth = 25;
      fontheight = 32;
      spec = 2;
      break;
  }
  if (offset == 0) offset = fontsize;
  uint8_t buf[130] = {0x00};
  uint32_t addr = st7789_gt30_caculate_ascii_address(baseaddr, offset, ch);
  uint8_t addr_buf[3] = {(addr & 0xff0000) >> 16, (addr & 0xff00) >> 8,
                         addr & 0xff};
  st7789_gt30_get_char_data(addr_buf, buf, fontsize);
  st7789_display_font_data(x, y, fontwidth, fontheight, fontsize, buf, fcolor,
                           spec);
}

void st7789_draw_ascii_string(uint16_t x, uint16_t y, fonts_t font,
                              uint8_t *str, uint16_t fcolor) {
  uint8_t distance, x0 = x;
  switch (font) {
    case ascii_standard_5x7:
      distance = 5;
      break;
    case ascii_standard_6x12:
      distance = 6;
      break;
    case ascii_standard_7x8:
      distance = 7;
      break;
    case ascii_standard_8x16:
      distance = 8;
      break;
    case ascii_12x24:
      distance = 12;
      break;
    case ascii_16x32:
      distance = 16;
      break;
    case ascii_arial_10x12:
      distance = 10;
      break;
    case ascii_arial_12x16:
      distance = 12;
      break;
    case ascii_arial_20x24:
      distance = 20;
      break;
    case ascii_arial_25x32:
      distance = 25;
      break;
    case ascii_times_10x12:
      distance = 10;
      break;
    case ascii_times_12x16:
      distance = 12;
      break;
    case ascii_times_20x24:
      distance = 20;
      break;
    case ascii_times_25x32:
      distance = 25;
      break;
  }
  for (uint8_t i = 0; i < strlen(str); i++) {
    st7789_draw_ascii_char(x0, y, font, str[i], fcolor);
    x0 += distance;
  }
}
