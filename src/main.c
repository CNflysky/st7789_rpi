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

  // init gpio
  st7789_dc = st7789_gpiod_request_gpio("gpiochip0", "st7789_dc", 199);
  st7789_reset = st7789_gpiod_request_gpio("gpiochip0", "st7789_reset", 198);
  // init main spidev (screen)
  st7789_spi_open("/dev/spidev1.0");
  st7789_spi_set_mode(SPI_MODE_2);
  st7789_spi_set_speed(48000000);  // 48 Mhz

  // init font spidev (on-board font chip)
  st7789_gt30_spi_open("/dev/spidev1.1");
  st7789_gt30_spi_set_mode(SPI_MODE_0);
  st7789_gt30_spi_set_speed(40000000);  // 40 MHz
  st7789_init(240, 240);
  return 0;
}
