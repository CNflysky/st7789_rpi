#ifndef _ST7789_FONT_H_
#define _ST7789_FONT_H_
/*
  enum for fonts.
*/
typedef enum {
  gb2312_12x12,
  gb2312_15x16,
  gb2312_24x24,
  gb2312_32x32,
  gb2312_extend_6x12,
  gb2312_extend_8x16,
  gb2312_extend_12x24,
  gb2312_extend_16x32,
  gb2312_special_8x16,
  ascii_standard_5x7,
  ascii_standard_7x8,
  ascii_standard_6x12,
  ascii_standard_8x16,
  ascii_12x24,
  ascii_16x32,
  ascii_arial_10x12,
  ascii_arial_12x16,
  ascii_arial_20x24,
  ascii_arial_25x32,
  ascii_times_10x12,
  ascii_times_12x16,
  ascii_times_20x24,
  ascii_times_25x32
} fonts_t;

// font param types.
typedef enum { BASEADDR, SIZE, WIDTH, HEIGHT, OFFSET } fontdata_t;

#include <iconv.h>

#include "st7789_spi.h"

int st7789_gt30_spi_fd;
int st7789_gt30_spi_speed;
/**
 *
 * @brief open spi file descriptor for the GT30 font chip.
 * @param path spidev file path (e.g. /dev/spidev0.0)
 * @return None
 * @note
 */
void st7789_gt30_spi_open(uint8_t* path);

/**
 *
 * @brief set gt30 spi mode
 * @param mode spi mode(can be SPI_MODE0,SPI_MODE1,SPI_MODE2 and SPI_MODE3).
 * @return None
 * @note
 */
void st7789_gt30_spi_set_mode(uint8_t mode);

/**
 *
 * @brief set gt20 spi speed
 * @param speed spi speed (in hz)
 * @return None
 * @note
 */
void st7789_gt30_spi_set_speed(uint32_t speed);

/**
 *
 * @brief read character data from addr to data buffer with specified length.
 * @param addr 3 bytes buffer stored character address.
 * @param data buffer used to receive character pixel data.
 * @param len data length
 * @return None
 * @note
 */
void st7789_gt30_read_data(uint8_t* addr, uint8_t* data, uint16_t len);

/**
 *
 * @brief convert utf8 char into gb2312 char code.
 * @param str a chinese char
 * @param in_len str's length
 * @param outbuf buffer used to store converted code
 * @param out_len outbuf's length
 * @return None
 * @note
 */
void st7789_gt30_convert_utf8_to_gb2312(uint8_t* str, uint16_t in_len,
                                        uint8_t* outbuf, uint16_t out_len);

/**
 *
 * @brief get gb2312 char address in gt30 chip with given font type,character
 * code and font group base address.
 * @param type font type
 * @param msb character code msb
 * @param lsb character code lsb
 * @param addr baseaddr of specified font type
 * @param size font pixel data size
 * @param addrbuf buffer used to store char address.
 * @return None
 * @note
 * @see fonts_t
 */
void st7789_gt30_get_gb2312_addr(fonts_t type, uint8_t msb, uint8_t lsb,
                                 uint32_t addr, uint8_t size, uint8_t* addrbuf);

/**
 *
 * @brief get ascii char address in gt30 chip.
 * @param baseaddr baseaddr of specified font type
 * @param fontsize font pixel data size
 * @param ch char.
 * @return None
 * @note
 * @see fonts_t
 */
uint32_t st7789_gt30_get_ascii_addr(uint32_t baseaddr, uint16_t fontsize,
                                    uint8_t ch);

/**
 *
 * @brief get a font's param
 * @param font font type
 * @param type param type(see fontdata_t)
 * @return param
 * @note
 */
uint32_t st7789_gt30_get_font_param(fonts_t font, fontdata_t type);
/**
 *
 * @brief close spi file descriptor
 * @param None
 * @return None
 * @note
 */
void st7789_gt30_close_spi_fd();

#endif