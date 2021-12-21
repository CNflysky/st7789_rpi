#include "st7789_spi.h"
#if __SIZEOF_POINTER__ == 4
#define _POINTER_CONVERT_TO_ uint32_t
#else
#define _POINTER_CONVERT_TO_ uint64_t
#endif
void st7789_spi_open(st7789config_t *config, st7789_t *st7789) {
  int fd = open(config->spi_path, O_NONBLOCK);
  if (fd < 0)
    pabort("Error opening spi file descriptor");
  else 
    st7789->spi_fd = fd;
}
void st7789_spi_set_bit(st7789_t *st7789) {
  uint8_t b = 8;
  if (ioctl((st7789->spi_fd), SPI_IOC_WR_BITS_PER_WORD, &b) < 0)
    pabort("Error setting spi bits");
}

void st7789_spi_set_mode(st7789_t *st7789) {
  uint8_t m = SPI_MODE_2;
  if (ioctl((st7789->spi_fd), SPI_IOC_WR_MODE, &m) < 0)
    pabort("Error setting spi mode");
}

void st7789_spi_set_speed(st7789config_t *config, st7789_t *st7789) {
  st7789->spi_speed = config->spi_speed;
  if (ioctl((st7789->spi_fd), SPI_IOC_WR_MODE, &(config->spi_speed)) < 0)
    pabort("Error setting spi speed");
}

void st7789_spi_write_8bit(st7789_t *st7789, datatypes_t type, uint8_t data) {
  uint8_t *buf = &data;
  gpiod_line_set_value(st7789->gpio_dc, type);
  struct spi_ioc_transfer spi = {.tx_buf = (_POINTER_CONVERT_TO_)buf,
                                 .rx_buf = 0,
                                 .delay_usecs = 0,
                                 .len = 1,
                                 .speed_hz = st7789->spi_speed};
  if (ioctl(st7789->spi_fd, SPI_IOC_MESSAGE(1), &spi) < 0)
    pabort("Error writing 8bit data to spi");
}

void st7789_spi_write_16bit(st7789_t *st7789, uint16_t data) {
  union {
    uint16_t val;
    struct {
      uint8_t lsb;
      uint8_t msb;
    };
  } data_u;
  data_u.val = data;
  uint8_t buf[2] = {data_u.msb, data_u.lsb};
  gpiod_line_set_value(st7789->gpio_dc, DATA);
  struct spi_ioc_transfer spi = {.tx_buf = (_POINTER_CONVERT_TO_)buf,
                                 .rx_buf = 0,
                                 .delay_usecs = 0,
                                 .len = 2,
                                 .speed_hz = st7789->spi_speed};
  if (ioctl(st7789->spi_fd, SPI_IOC_MESSAGE(1), &spi) < 0)
    pabort("Error writting 16bit data to spi");
}

void st7789_spi_write_multi(st7789_t *st7789, uint8_t *data, uint16_t len) {
  gpiod_line_set_value(st7789->gpio_dc, DATA);
  struct spi_ioc_transfer spi = {.tx_buf = (_POINTER_CONVERT_TO_)data,
                                 .rx_buf = 0,
                                 .delay_usecs = 0,
                                 .len = len,
                                 .speed_hz = st7789->spi_speed};
  if (ioctl(st7789->spi_fd, SPI_IOC_MESSAGE(1), &spi) < 0)
    pabort("Error writting 8bit bytes to spi");
}

void st7789_spi_write_multi16(st7789_t *st7789, uint16_t *data, uint32_t len) {
  union {
    uint16_t val;
    struct {
      uint8_t lsb;
      uint8_t msb;
    };
  } data_u;
  if (len < 2048) {
    uint8_t buffer[len * 2 - 1];
    memset(buffer, 0x0, sizeof buffer);
    for (uint16_t i = 0; i < len * 2; i++) {
      data_u.val = data[i / 2];
      (i % 2) ? (buffer[i] = data_u.lsb) : (buffer[i] = data_u.msb);
    }
    st7789_spi_write_multi(st7789, buffer, sizeof buffer);
  } else {
    uint8_t buffer[4096] = {0x0};
    uint8_t round = len / 2048;
    uint32_t remain_pixels = len - round * 2048;
    uint32_t end_addr = len - remain_pixels;
    uint32_t start = 0, end = 2048, buffer_mark = 0;
    for (uint8_t r = 0; r < round; r++) {
      for (uint32_t i = start; i < end; i++) {
        data_u.val = data[i];
        buffer[buffer_mark] = data_u.msb;
        buffer[buffer_mark + 1] = data_u.lsb;
        buffer_mark += 2;
      }
      buffer_mark = 0;
      start += 2048;
      end += 2048;
      st7789_spi_write_multi(st7789, buffer, 4096);
    }
    if (remain_pixels > 0) {
      uint8_t buffer[remain_pixels * 2];
      memset(buffer, 0x0, sizeof buffer);
      for (uint32_t i = end_addr; i < len; i++) {
        data_u.val = data[i];
        buffer[buffer_mark] = data_u.msb;
        buffer[buffer_mark + 1] = data_u.lsb;
        buffer_mark += 2;
      }
      st7789_spi_write_multi(st7789, buffer, sizeof buffer);
    }
  }
}

void st7789_spi_close(st7789_t *st7789) { close(st7789->spi_fd); }