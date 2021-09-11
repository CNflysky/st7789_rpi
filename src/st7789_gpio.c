#include "st7789_gpio.h"
struct gpiod_line *st7789_gpiod_request_gpio(const uint8_t *gpiochip,
                                             const uint8_t *linename, int pin) {
  struct gpiod_chip *chip = gpiod_chip_open_by_name(gpiochip);
  if (!chip) {
    perror("Error:open chip failed");
    exit(1);
  }
  struct gpiod_line *line = gpiod_chip_get_line(chip, pin);
  if (!line) {
    perror("Error:get gpio line failed");
    exit(1);
  }
  if (gpiod_line_request_output(line, linename, 0) < 0) {
    perror("Error:set gpio to output failed");
    exit(1);
  }
  return line;
}