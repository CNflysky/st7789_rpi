#ifndef _ST7789_DEF_H_
#define _ST7789_DEF_H_

#include <errno.h>
#include <fcntl.h>
#include <gpiod.h>
#include <linux/spi/spidev.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdarg.h>

typedef struct {
  const char *spi_path;
  int spi_speed;
  const char *gpio_dc_chip;
  const char *gpio_reset_chip;
  int dc_pin;
  int reset_pin;
  uint16_t width;
  uint16_t height;
} st7789config_t;

typedef struct {
  int spi_fd;
  int spi_speed;
  struct gpiod_line *gpio_dc;
  struct gpiod_line *gpio_reset;
  uint16_t width;
  uint16_t height;
  uint16_t display_buffer[320 * 240];  // max resolution:320*240
} st7789_t;

typedef enum { COMMAND, DATA } datatypes_t;

typedef enum {
  RED = 0xF800,
  YELLOW = 0xFFE0,
  BLUE = 0x001F,
  GREEN = 0x0400,
  WHITE = 0xFFFF,
  BLACK = 0x0000
} colors_t;

void pabort(const char *str);

#endif