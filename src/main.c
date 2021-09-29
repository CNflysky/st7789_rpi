#include <signal.h>

#include "st7789_ips.h"

void signal_handler(int sig) {
  st7789_clear_screen();
  st7789_send_buf();
  st7789_spi_fd_close();
}

void st7789_draw_outline(uint8_t* str) {
  st7789_draw_line(0, 20, 239, 20, WHITE);
  st7789_draw_string_mixed(3, 3, ascii_standard_8x16, gb2312_15x16,
                           "ST7789 1.3寸 IPS屏幕 测试程序", WHITE);
  st7789_draw_line(0, st7789_height - 20, st7789_width - 1, st7789_height - 20,
                   WHITE);
  st7789_draw_string_mixed(0, st7789_height - 17, ascii_standard_8x16,
                           gb2312_15x16, str, WHITE);
}

void st7789_test_procedure() {
  while (1) {
    st7789_clear_buf();
    st7789_fill_screen(BLUE);
    st7789_draw_outline("中文显示测试");
    st7789_draw_chinese_string(0, 25, gb2312_12x12, "你好世界", WHITE);
    st7789_draw_chinese_string(0, 42, gb2312_15x16, "你好世界", WHITE);
    st7789_draw_chinese_string(0, 67, gb2312_24x24, "你好世界", WHITE);
    st7789_draw_chinese_string(0, 100, gb2312_32x32, "你好世界", WHITE);
    st7789_send_buf();
    sleep(2);

    st7789_clear_buf();
    st7789_fill_screen(BLUE);
    st7789_draw_outline("标准ASCII字符显示测试");
    st7789_draw_ascii_string(0, 25, ascii_standard_5x7, "hello,world!", WHITE);
    st7789_draw_ascii_string(0, 34, ascii_standard_7x8, "hello,world!", WHITE);
    st7789_draw_ascii_string(0, 47, ascii_standard_6x12, "hello,world!", WHITE);
    st7789_draw_ascii_string(0, 64, ascii_standard_8x16, "hello,world!", WHITE);
    st7789_send_buf();
    sleep(2);

    st7789_clear_buf();
    st7789_fill_screen(BLUE);
    st7789_draw_outline("Arial ASCII字符显示测试");
    st7789_draw_ascii_string(0, 25, ascii_arial_10x12, "hello,world!", WHITE);
    st7789_draw_ascii_string(0, 38, ascii_arial_12x16, "hello,world!", WHITE);
    st7789_draw_ascii_string(0, 63, ascii_arial_20x24, "hello,world!", WHITE);
    st7789_draw_ascii_string(0, 87, ascii_arial_25x32, "hello,world!", WHITE);
    st7789_send_buf();
    sleep(2);

    st7789_clear_buf();
    st7789_fill_screen(BLUE);
    st7789_draw_outline("Times ASCII字符显示测试");
    st7789_draw_ascii_string(0, 25, ascii_times_10x12, "hello,world!", WHITE);
    st7789_draw_ascii_string(0, 38, ascii_times_12x16, "hello,world!", WHITE);
    st7789_draw_ascii_string(0, 63, ascii_times_20x24, "hello,world!", WHITE);
    st7789_draw_ascii_string(0, 87, ascii_times_25x32, "hello,world!", WHITE);
    st7789_send_buf();
    sleep(2);

    st7789_clear_buf();
    st7789_fill_screen(BLUE);
    st7789_draw_outline("中英文字符混合显示测试");
    st7789_draw_string_mixed(0, 25, ascii_standard_6x12, gb2312_12x12,
                             "Written by CNflysky 由CNflysky编写", WHITE);
    st7789_draw_string_mixed(0, 42, ascii_standard_8x16, gb2312_15x16,
                             "ST7789 由Linux硬件SPI驱动", WHITE);
    st7789_draw_string_mixed(0, 67, ascii_arial_20x24, gb2312_24x24,
                             "ST7789驱动", WHITE);
    st7789_draw_string_mixed(0, 100, ascii_times_25x32, gb2312_32x32,
                             "ST7789驱动", WHITE);
    st7789_send_buf();
    sleep(2);

    st7789_clear_buf();
    st7789_fill_screen(BLUE);
    st7789_draw_outline("画圆测试");
    st7789_draw_circle(50, 50, 10, WHITE, false);
    st7789_draw_circle(50, 100, 10, WHITE, true);
    st7789_send_buf();
    sleep(2);

    st7789_clear_buf();
    st7789_fill_screen(BLUE);
    st7789_draw_outline("画长方形测试");
    st7789_draw_rectangle(30, 30, 80, 80, WHITE, false);
    st7789_draw_rectangle(90, 30, 140, 80, WHITE, true);
    st7789_send_buf();
    sleep(2);

    st7789_clear_buf();
    st7789_fill_screen(BLUE);
    st7789_draw_outline("画线测试");
    st7789_draw_line(30, 30, 70, 70, WHITE);
    st7789_draw_line(70, 70, 119, 30, WHITE);
    st7789_send_buf();
    sleep(2);
    st7789_clear_buf();
    st7789_fill_screen(BLUE);
    st7789_draw_outline("颜色填充测试");
    st7789_draw_string_mixed(0, 100, ascii_times_20x24, gb2312_24x24,
                             "2秒后开始填充测试", WHITE);
    st7789_send_buf();
    sleep(2);

    st7789_clear_buf();
    st7789_fill_screen(RED);
    st7789_send_buf();
    sleep(2);
    st7789_clear_buf();
    st7789_fill_screen(YELLOW);
    st7789_send_buf();
    sleep(2);
    st7789_clear_buf();
    st7789_fill_screen(GREEN);
    st7789_send_buf();
    sleep(2);
    st7789_clear_buf();
    st7789_fill_screen(BLUE);
    st7789_send_buf();
    sleep(2);
  }
}

int main() {
  signal(SIGINT, signal_handler);
  /*st7789_dc = st7789_gpiod_request_gpio("gpiochip1", "st7789_dc", 70);
  st7789_reset = st7789_gpiod_request_gpio("gpiochip1", "st7789_reset", 69);
  st7789_spi_open("/dev/spidev1.1");*/

  // init gpio
  st7789_dc = st7789_gpiod_request_gpio("gpiochip0", "st7789_dc", 18);
  st7789_reset = st7789_gpiod_request_gpio("gpiochip0", "st7789_reset", 17);
  // init main spidev (screen)
  st7789_spi_open("/dev/spidev0.0");
  st7789_spi_set_mode(SPI_MODE_2);
  st7789_spi_set_speed(40000000);  // 48 Mhz

  // init font spidev (on-board font chip)
  st7789_gt30_spi_open("/dev/spidev0.1");
  st7789_gt30_spi_set_mode(SPI_MODE_0);
  st7789_gt30_spi_set_speed(40000000);  // 40 MHz
  st7789_init(240, 240);
  st7789_test_procedure();
  return 0;
}
