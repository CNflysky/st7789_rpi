#ifndef _ST7789_SPI_H_
#define _ST7789_SPI_H_

#include "st7789_def.h"

void st7789_spi_open(st7789config_t *config, st7789_t *st7789);
void st7789_spi_set_bit(st7789_t *st7789);
void st7789_spi_set_mode(st7789_t *st7789);
void st7789_spi_set_speed(st7789config_t *config, st7789_t *st7789);
void st7789_spi_write_8bit(st7789_t *st7789, datatypes_t type, uint8_t data);
void st7789_spi_write_16bit(st7789_t *st7789, uint16_t data);
void st7789_spi_write_multi(st7789_t *st7789, uint8_t *data, uint16_t len);
void st7789_spi_write_multi16(st7789_t *st7789, uint16_t *data, uint32_t len);

#endif