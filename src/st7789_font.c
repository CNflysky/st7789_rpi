#include "st7789_font.h"
#if __SIZEOF_POINTER__ == 4
#define _POINTER_CONVERT_TO_ uint32_t
#else
#define _POINTER_CONVERT_TO_ uint64_t
#endif

void st7789_gt30_spi_open(gt30config_t* config, gt30_t* gt30);
void st7789_gt30_spi_set_mode(gt30_t* gt30);
void st7789_gt30_spi_set_speed(gt30_t* gt30);

void st7789_gt30_init(gt30config_t* config, gt30_t* gt30) {
  st7789_gt30_spi_open(config, gt30);
  st7789_gt30_spi_set_mode(gt30);
  st7789_gt30_spi_set_speed(gt30);
}

void st7789_gt30_spi_open(gt30config_t* config, gt30_t* gt30) {
  gt30->spi_speed = config->spi_speed;
  int spi_fd = open(config->spi_path, O_NONBLOCK);
  if (spi_fd < 0)
    pabort("Error opening gt30 spi");
  else
    gt30->spi_fd = spi_fd;
}

void st7789_gt30_spi_set_mode(gt30_t* gt30) {
  int spi_mode = SPI_MODE_0;
  if (ioctl(gt30->spi_fd, SPI_IOC_WR_MODE, &spi_mode) < 0)
    pabort("Error setting gt30 spi mode");
}

void st7789_gt30_spi_set_speed(gt30_t* gt30) {
  if (ioctl(gt30->spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &(gt30->spi_speed)) < 0)
    pabort("Error setting gt30 spi speed");
}

void st7789_gt30_read_data(gt30_t* gt30, uint8_t* addr, uint8_t* data,
                           uint16_t len) {
  uint8_t cmd_with_addr[4] = {0x03};
  memcpy(cmd_with_addr + 1, addr, 3);
  struct spi_ioc_transfer spi_cmd = {
      .speed_hz = gt30->spi_speed,
      .tx_buf = (_POINTER_CONVERT_TO_)cmd_with_addr,
      .rx_buf = 0,
      .delay_usecs = 0,
      .len = 4,
      .cs_change = true};
  if (ioctl(gt30->spi_fd, SPI_IOC_MESSAGE(1), &spi_cmd) < 0)
    pabort("Error:send command and address to gt30 error");
  struct spi_ioc_transfer spi_data = {.speed_hz = gt30->spi_speed,
                                      .tx_buf = (_POINTER_CONVERT_TO_)data,
                                      .rx_buf = (_POINTER_CONVERT_TO_)data,
                                      .delay_usecs = 0,
                                      .len = len};
  if (ioctl(gt30->spi_fd, SPI_IOC_MESSAGE(1), &spi_data) < 0)
    pabort("Error:send data to gt30 error");
}

void st7789_gt30_convert_utf8_to_gb2312(uint8_t* str, uint16_t in_len,
                                        uint8_t* outbuf, uint16_t out_len) {
  iconv_t conv;
  if ((conv = iconv_open("GB2312//IGNORE", "UTF-8")) < 0)
    pabort("Error:open iconv_t failed");
  uint8_t in_buffer[in_len];
  strcpy(in_buffer, str);
  size_t in_buffer_len = strlen(in_buffer);

  size_t out_buffer_len = out_len;

  uint8_t* pinbuf = in_buffer;
  uint8_t* poutbuf = outbuf;
  if (iconv(conv, (char**)&pinbuf, &in_buffer_len, (char**)&poutbuf,
            &out_buffer_len) < 0)
    pabort("Error:iconv convert failed");
  iconv_close(conv);
}

void st7789_gt30_get_gb2312_addr(fonts_t type, uint8_t msb, uint8_t lsb,
                                 uint32_t addr, uint8_t size,
                                 uint8_t* addrbuf) {
  uint32_t address = 0;
  uint32_t baseaddr = addr;
  uint8_t n = size;
  if (msb >= 0xA1 && msb <= 0xA9 && lsb >= 0xA1)
    address = ((msb - 0xA1) * 94 + (lsb - 0xA1)) * n + baseaddr;
  else if (msb >= 0xB0 && msb <= 0xF7 && lsb >= 0xA1)
    address = ((msb - 0xB0) * 94 + (lsb - 0xA1) + 846) * n + baseaddr;
  addrbuf[0] = (address & 0xff0000) >> 16;
  addrbuf[1] = (address & 0xff00) >> 8;
  addrbuf[2] = address & 0xff;
}

uint32_t st7789_gt30_get_ascii_addr(uint32_t baseaddr, uint16_t fontsize,
                                    uint8_t ch) {
  if (ch >= 0x20 && ch <= 0x7E)
    return (ch - 0x20) * fontsize + baseaddr;
  else
    return -1;
}
void st7789_gt30_close_spi_fd(gt30_t* gt30) { close(gt30->spi_fd); }

uint32_t st7789_gt30_get_font_param(fonts_t font, fontdata_t type) {
  switch (font) {
    case ascii_standard_5x7:
      switch (type) {
        case BASEADDR:
          return 0x1DDF80;
          break;
        case SIZE:
          return 7;
          break;
        case HEIGHT:
          return 7;
          break;
        case WIDTH:
          return 5;
          break;
        case OFFSET:
          return 0;
          break;
      }
      break;
    case ascii_standard_6x12:
      switch (type) {
        case BASEADDR:
          return 0x1DBE00;
          break;
        case SIZE:
          return 12;
          break;
        case HEIGHT:
          return 12;
          break;
        case WIDTH:
          return 6;
          break;
        case OFFSET:
          return 0;
          break;
      }
      break;
    case ascii_standard_7x8:
      switch (type) {
        case BASEADDR:
          return 0x1DE280;
          break;
        case SIZE:
          return 8;
          break;
        case HEIGHT:
          return 8;
          break;
        case WIDTH:
          return 7;
          break;
        case OFFSET:
          return 0;
          break;
      }
      break;
    case ascii_standard_8x16:
      switch (type) {
        case BASEADDR:
          return 0x1DD780;
          break;
        case SIZE:
          return 16;
          break;
        case HEIGHT:
          return 16;
          break;
        case WIDTH:
          return 8;
          break;
        case OFFSET:
          return 0;
          break;
      }
      break;
    case ascii_12x24:
      switch (type) {
        case BASEADDR:
          return 0x1DFF00;
          break;
        case SIZE:
          return 48;
          break;
        case HEIGHT:
          return 24;
          break;
        case WIDTH:
          return 12;
          break;
        case OFFSET:
          return 0;
          break;
      }
      break;
    case ascii_16x32:
      switch (type) {
        case BASEADDR:
          return 0x1E5A50;
          break;
        case SIZE:
          return 64;
          break;
        case HEIGHT:
          return 32;
          break;
        case WIDTH:
          return 16;
          break;
        case OFFSET:
          return 0;
          break;
      }
      break;
    case ascii_arial_10x12:
      switch (type) {
        case BASEADDR:
          return 0x1DC400;
          break;
        case SIZE:
          return 26;
          break;
        case HEIGHT:
          return 12;
          break;
        case WIDTH:
          return 10;
          break;
        case OFFSET:
          return 2;
          break;
      }
      break;
    case ascii_arial_12x16:
      switch (type) {
        case BASEADDR:
          return 0x1DE580;
          break;
        case SIZE:
          return 34;
          break;
        case HEIGHT:
          return 16;
          break;
        case WIDTH:
          return 12;
          break;
        case OFFSET:
          return 2;
          break;
      }
      break;
    case ascii_arial_20x24:
      switch (type) {
        case BASEADDR:
          return 0x1E22D0;
          break;
        case SIZE:
          return 74;
          break;
        case HEIGHT:
          return 21;
          break;
        case WIDTH:
          return 20;
          break;
        case OFFSET:
          return 2;
          break;
      }
      break;
    case ascii_arial_25x32:
      switch (type) {
        case BASEADDR:
          return 0x1E99D0;
          break;
        case SIZE:
          return 130;
          break;
        case HEIGHT:
          return 32;
          break;
        case WIDTH:
          return 25;
          break;
        case OFFSET:
          return 2;
          break;
      }
      break;
    case ascii_times_10x12:
      switch (type) {
        case BASEADDR:
          return 0x1DCDC0;
          break;
        case SIZE:
          return 26;
          break;
        case HEIGHT:
          return 12;
          break;
        case WIDTH:
          return 10;
          break;
        case OFFSET:
          return 2;
          break;
      }
      break;
    case ascii_times_12x16:
      switch (type) {
        case BASEADDR:
          return 0x1DF240;
          break;
        case SIZE:
          return 34;
          break;
        case HEIGHT:
          return 16;
          break;
        case WIDTH:
          return 12;
          break;
        case OFFSET:
          return 2;
          break;
      }
      break;
    case ascii_times_20x24:
      switch (type) {
        case BASEADDR:
          return 0x1E3E90;
          break;
        case SIZE:
          return 74;
          break;
        case HEIGHT:
          return 24;
          break;
        case WIDTH:
          return 20;
          break;
        case OFFSET:
          return 2;
          break;
      }
      break;
    case ascii_times_25x32:
      switch (type) {
        case BASEADDR:
          return 0x1ECA90;
          break;
        case SIZE:
          return 130;
          break;
        case HEIGHT:
          return 32;
          break;
        case WIDTH:
          return 25;
          break;
        case OFFSET:
          return 2;
          break;
      }
      break;
    case gb2312_12x12:
      switch (type) {
        case BASEADDR:
          return 0x0;
          break;
        case SIZE:
          return 24;
          break;
        case HEIGHT:
        case WIDTH:
          return 12;
          break;
      }
      break;
    case gb2312_15x16:
      switch (type) {
        case BASEADDR:
          return 0x2C9D0;
          break;
        case SIZE:
          return 32;
          break;
        case HEIGHT:
        case WIDTH:
          return 16;
          break;
      }
      break;
    case gb2312_24x24:
      switch (type) {
        case BASEADDR:
          return 0x68190;
          break;
        case SIZE:
          return 72;
          break;
        case HEIGHT:
        case WIDTH:
          return 24;
          break;
      }
      break;
    case gb2312_32x32:
      switch (type) {
        case BASEADDR:
          return 0xEDF00;
          break;
        case SIZE:
          return 128;
          break;
        case HEIGHT:
        case WIDTH:
          return 32;
          break;
      }
      break;
  }
}