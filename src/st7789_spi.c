#include "st7789_spi.h"
#if __SIZEOF_POINTER__ == 4
# define _POINTER_CONVERT_TO_ uint32_t
#else
# define _POINTER_CONVERT_TO_ uint64_t
#endif

void st7789_spi_open(const uint8_t *spidev_path) {
  if ((st7789_spi_fd = open(spidev_path, O_NONBLOCK)) < 0) {
    perror("Error opening spidev file");
    exit(EXIT_FAILURE);
  } else {
    int bitsperword = 8;
    ioctl(st7789_spi_fd, SPI_IOC_WR_BITS_PER_WORD, &bitsperword);
  }
}

void st7789_spi_set_mode(uint8_t mode) {
  st7789_spi_mode = mode;
  if (ioctl(st7789_spi_fd, SPI_IOC_WR_MODE, &st7789_spi_mode) < 0) {
    perror("Error setting spi mode");
    exit(EXIT_FAILURE);
  }
}

void st7789_spi_set_speed(uint32_t speed) {
  st7789_spi_speed = speed;
  if (ioctl(st7789_spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &st7789_spi_speed) < 0) {
    perror("Error setting spi speed");
    exit(EXIT_FAILURE);
  }
}

void st7789_spi_write_8bit(datatype_t type, uint8_t data) {
  uint8_t *buf = &data;
  gpiod_line_set_value(st7789_dc, type);
  struct spi_ioc_transfer spi = {.tx_buf = (_POINTER_CONVERT_TO_)buf,
                                 .rx_buf = 0,
                                 .delay_usecs = 0,
                                 .len = 1,
                                 .speed_hz = st7789_spi_speed};
  if (ioctl(st7789_spi_fd, SPI_IOC_MESSAGE(1), &spi) < 0) {
    perror("Error writing 8bit data to spi");
    exit(EXIT_FAILURE);
  }
}

void st7789_spi_write_16bit(uint16_t data) {
  union {
    uint16_t val;
    struct {
      uint8_t lsb;
      uint8_t msb;
    };
  } data_u;
  data_u.val = data;
  uint8_t buf[2] = {data_u.msb, data_u.lsb};
  gpiod_line_set_value(st7789_dc, DATA);
  struct spi_ioc_transfer spi = {.tx_buf = (_POINTER_CONVERT_TO_)buf,
                                 .rx_buf = 0,
                                 .delay_usecs = 0,
                                 .len = 2,
                                 .speed_hz = st7789_spi_speed};
  if (ioctl(st7789_spi_fd, SPI_IOC_MESSAGE(1), &spi) < 0) {
    perror("Error writting 16bit data to spi");
    exit(EXIT_FAILURE);
  }
}

void st7789_spi_write_8bytes(uint8_t *data, uint16_t len) {
  gpiod_line_set_value(st7789_dc, DATA);
  struct spi_ioc_transfer spi = {.tx_buf = (_POINTER_CONVERT_TO_)data,
                                 .rx_buf = 0,
                                 .delay_usecs = 0,
                                 .len = len,
                                 .speed_hz = st7789_spi_speed};
  if (ioctl(st7789_spi_fd, SPI_IOC_MESSAGE(1), &spi) < 0) {
    perror("Error writting 8bit bytes to spi");
    exit(EXIT_FAILURE);
  }
}

void st7789_spi_write_16bytes(uint16_t *data, uint16_t len) {
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
    st7789_spi_write_8bytes(buffer, sizeof buffer);
  } else {
    uint8_t buffer[4096] = {0x0};
    uint8_t round = len / 2048;
    uint16_t remain_pixels = len - round * 2048;
    uint16_t end_addr = len - remain_pixels;
    uint16_t start = 0, end = 2048, buffer_mark = 0;
    for (uint8_t r = 0; r < round; r++) {
      for (uint16_t i = start; i < end; i++) {
        data_u.val = data[i];
        buffer[buffer_mark] = data_u.msb;
        buffer[buffer_mark + 1] = data_u.lsb;
        buffer_mark += 2;
      }
      buffer_mark = 0;
      start += 2048;
      end += 2048;
      st7789_spi_write_8bytes(buffer, 4096);
    }
    if (remain_pixels > 0) {
      uint8_t buffer[remain_pixels * 2];
      memset(buffer, 0x0, sizeof buffer);
      for (uint16_t i = end_addr; i < len; i++) {
        data_u.val = data[i];
        buffer[buffer_mark] = data_u.msb;
        buffer[buffer_mark + 1] = data_u.lsb;
        buffer_mark += 2;
      }
      st7789_spi_write_8bytes(buffer, sizeof buffer);
    }
  }
}

bool st7789_spi_fd_close() {
  if (close(st7789_spi_fd) < 0)
    return false;
  else
    return true;
}