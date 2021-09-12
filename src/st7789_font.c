#include "st7789_font.h"

void st7789_gt30_spi_open(uint8_t* path) {
  if ((st7789_gt30_spi_fd = open(path, O_NONBLOCK)) < 0) {
    perror("Error:open font chip spidev failed!");
    exit(EXIT_FAILURE);
  } else {
    int bitsperword = 8;
    ioctl(st7789_gt30_spi_fd, SPI_IOC_WR_BITS_PER_WORD, &bitsperword);
  }
}

void st7789_gt30_spi_set_mode(uint8_t mode) {
  int st7789_gt30_spi_mode = mode;
  if (ioctl(st7789_gt30_spi_fd, SPI_IOC_WR_MODE, &st7789_gt30_spi_mode) < 0) {
    perror("Error setting gt30 spi mode");
    exit(EXIT_FAILURE);
  }
}

void st7789_gt30_spi_set_speed(uint32_t speed) {
  st7789_gt30_spi_speed = speed;
  if (ioctl(st7789_gt30_spi_fd, SPI_IOC_WR_MAX_SPEED_HZ,
            &st7789_gt30_spi_speed) < 0) {
    perror("Error setting gt30 spi speed");
    exit(EXIT_FAILURE);
  }
}

void st7789_gt30_get_char_data(uint8_t* addr, uint8_t* data, uint16_t len) {
  uint8_t cmd_with_addr[4] = {0x03};
  memcpy(cmd_with_addr + 1, addr, 3);
  struct spi_ioc_transfer spi_cmd = {.speed_hz = st7789_gt30_spi_speed,
                                     .tx_buf = (uint64_t)cmd_with_addr,
                                     .rx_buf = 0,
                                     .delay_usecs = 0,
                                     .len = 4,
                                     .cs_change = true};
  if (ioctl(st7789_gt30_spi_fd, SPI_IOC_MESSAGE(1), &spi_cmd) < 0) {
    perror("Error:send command and address to gt30 error");
    exit(EXIT_FAILURE);
  }
  struct spi_ioc_transfer spi_data = {.speed_hz = st7789_gt30_spi_speed,
                                      .tx_buf = (uint64_t)data,
                                      .rx_buf = (uint64_t)data,
                                      .delay_usecs = 0,
                                      .len = len};
  if (ioctl(st7789_gt30_spi_fd, SPI_IOC_MESSAGE(1), &spi_data) < 0) {
    perror("Error:send data to gt30 error");
    exit(EXIT_FAILURE);
  }
}

void st7789_gt30_convert_utf8_to_gb2312(uint8_t* str, uint16_t in_len,
                                        uint8_t* outbuf, uint16_t out_len) {
  iconv_t conv;
  if ((conv = iconv_open("GB2312//IGNORE", "UTF-8")) < 0) {
    perror("Error:open iconv_t failed");
    exit(EXIT_FAILURE);
  }
  uint8_t in_buffer[in_len];
  strcpy(in_buffer, str);
  size_t in_buffer_len = strlen(in_buffer);

  size_t out_buffer_len = out_len;

  uint8_t* pinbuf = in_buffer;
  uint8_t* poutbuf = outbuf;
  if (iconv(conv, (char**)&pinbuf, &in_buffer_len, (char**)&poutbuf,
            &out_buffer_len) < 0) {
    perror("Error:iconv convert failed");
    exit(EXIT_FAILURE);
  }
  iconv_close(conv);
}

void st7789_gt30_caculate_chinese_address(fonts_t type, uint8_t msb,
                                          uint8_t lsb, uint8_t* addrbuf) {
  uint32_t address = 0;
  uint32_t baseaddr = 0x0;
  uint8_t n = 0;
  switch (type) {
    case gb2312_12x12:
      baseaddr = 0x0;
      n = 24;
      break;
    case gb2312_15x16:
      baseaddr = 0x2C9D0;
      n = 32;
      break;
    case gb2312_24x24:
      baseaddr = 0x68190;
      n = 72;
      break;
    case gb2312_32x32:
      baseaddr = 0xEDF00;
      n = 128;
      break;
  }

  if (msb >= 0xA1 && msb <= 0xA9 && lsb >= 0xA1)
    address = ((msb - 0xA1) * 94 + (lsb - 0xA1)) * n + baseaddr;
  else if (msb >= 0xB0 && msb <= 0xF7 && lsb >= 0xA1)
    address = ((msb - 0xB0) * 94 + (lsb - 0xA1) + 846) * n + baseaddr;
  addrbuf[0] = (address & 0xff0000) >> 16;
  addrbuf[1] = (address & 0xff00) >> 8;
  addrbuf[2] = address & 0xff;
}