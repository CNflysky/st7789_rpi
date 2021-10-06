#ifndef _ST7789_SPI_H_
#define _ST7789_SPI_H_

#include <fcntl.h>
#include <linux/spi/spidev.h>
#include <stdint.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "st7789_gpio.h"
int st7789_spi_fd;
uint8_t st7789_spi_mode;
uint64_t st7789_spi_speed;
typedef enum { COMMAND, DATA } datatype_t;
void st7789_spi_open(const uint8_t *spidev_path);
void st7789_spi_set_mode(uint8_t mode);
void st7789_spi_set_speed(uint32_t speed);
void st7789_spi_write_8bit(datatype_t type, uint8_t data);
void st7789_spi_write_16bit(uint16_t data);
bool st7789_spi_fd_close();
void st7789_spi_write_multi16(uint16_t *data, uint32_t len);
void st7789_spi_write_multi(uint8_t *data, uint16_t len);

#endif