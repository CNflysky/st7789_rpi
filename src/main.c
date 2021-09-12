#include <signal.h>

#include "st7789_ips.h"

void signal_handler(int sig) {
  st7789_clear_screen();
  st7789_spi_fd_close();
}

int main() {
  signal(SIGINT, signal_handler);
  /*st7789_dc = st7789_gpiod_request_gpio("gpiochip1", "st7789_dc", 70);
  st7789_reset = st7789_gpiod_request_gpio("gpiochip1", "st7789_reset", 69);
  st7789_spi_open("/dev/spidev1.1");*/

  st7789_dc = st7789_gpiod_request_gpio("gpiochip0", "st7789_dc", 18);
  st7789_reset = st7789_gpiod_request_gpio("gpiochip0", "st7789_reset", 17);
  st7789_spi_open("/dev/spidev0.0");
  st7789_gt30_spi_open("/dev/spidev0.1");
  st7789_gt30_spi_set_mode(SPI_MODE_0);
  st7789_gt30_spi_set_speed(40000000);

  st7789_spi_set_mode(SPI_MODE_2);
  st7789_spi_set_speed(40000000);
  st7789_init(240, 240);
  while (1) {
    for (uint8_t i = 'A'; i < 'Z' + 1; i++) {
      /*st7789_draw_chinese_string(0, 0, gb2312_12x12, "树莓派测试", 0xFFFF,
                                 0x0000);
      st7789_delay(500);
      st7789_clear_screen();
      st7789_draw_chinese_string(0, 0, gb2312_15x16, "树莓派测试", 0xFFFF,
                                 0x0000);
      st7789_delay(500);
      st7789_clear_screen();

      st7789_draw_chinese_string(0, 0, gb2312_24x24, "树莓派测试", 0xFFFF,
                                 0x0000);
      st7789_delay(500);
      st7789_clear_screen();*/

      st7789_draw_chinese_string(0, 0, gb2312_32x32, "树莓派测试", 0xFFFF,
                                 0x0000);
      st7789_delay(500);
      //st7789_clear_screen();
    }
  }
  return 0;
}
