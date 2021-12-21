#include "st7789_gpio.h"
void st7789_gpiod_request_gpio(st7789config_t *config, st7789_t *st7789) {
  struct gpiod_chip *chip = gpiod_chip_open_by_name(config->gpio_dc_chip);

  st7789->gpio_dc = gpiod_chip_get_line(chip, config->dc_pin);
  if (!(st7789->gpio_dc)) pabort("Error:get gpio line failed");
  if (gpiod_line_request_output(st7789->gpio_dc, "gpio_dc", 0) < 0)
    pabort("Error:set gpio to output failed");

  chip = gpiod_chip_open_by_name(config->gpio_reset_chip);
  st7789->gpio_reset = gpiod_chip_get_line(chip, config->reset_pin);
  if (!(st7789->gpio_reset)) pabort("Error:get gpio line failed");
  if (gpiod_line_request_output(st7789->gpio_reset, "gpio_reset", 1) < 0)
    pabort("Error:set gpio to output failed");
}