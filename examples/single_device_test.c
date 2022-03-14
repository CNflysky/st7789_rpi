#include <signal.h>

#include "qrcode.h"
#include "st7789_ips.h"

// #define OPIZERO
#define RPI4B

#ifdef OPIZERO
st7789config_t config = {.dc_pin = 2,
                         .reset_pin = 3,
                         .gpio_dc_chip = "gpiochip0",
                         .gpio_reset_chip = "gpiochip0",
                         .height = 240,
                         .width = 240,
                         .spi_path = "/dev/spidev1.0",
                         .spi_speed = 40000000};
gt30config_t gt30conf = {.spi_path = "/dev/spidev1.1", .spi_speed = 40000000};
#elif defined RPI4B
st7789config_t config = {.dc_pin = 18,
                         .reset_pin = 17,
                         .gpio_dc_chip = "gpiochip0",
                         .gpio_reset_chip = "gpiochip0",
                         .height = 240,
                         .width = 240,
                         .spi_path = "/dev/spidev0.0",
                         .spi_speed = 40000000};
gt30config_t gt30conf = {.spi_path = "/dev/spidev0.1", .spi_speed = 40000000};
#endif

st7789_t st7789 = {0};
gt30_t gt30 = {0};
void st7789_test_procedure();

void exit_handler() {
  st7789_clear_screen();
  st7789_send_buf(&st7789);
  st7789_gt30_close_spi_fd(&gt30);
}

int main() {
  signal(SIGINT, exit_handler);
  st7789_init(&config, &st7789);  // modify me!
  st7789_gt30_init(&gt30conf, &gt30);
  st7789_set_default_device(&st7789);
  st7789_set_default_fontchip(&gt30);
  st7789_test_procedure();
}

void st7789_draw_outline(uint8_t *str) {
  st7789_draw_line(0, 20, 239, 20, WHITE);
  st7789_draw_string(3, 3, ascii_standard_8x16, gb2312_15x16,
                     "ST7789 1.3寸 IPS屏幕 测试程序", WHITE);
  st7789_draw_line(0, st7789.height - 20, st7789.width - 1, st7789.height - 20,
                   WHITE);
  st7789_draw_string(0, st7789.height - 17, ascii_standard_8x16, gb2312_15x16,
                     str, WHITE);
}

void st7789_test_procedure() {
  while (1) {
    st7789_clear_buf();
    st7789_fill_screen(BLUE);
    st7789_send_buf();
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
    st7789_draw_string(0, 25, ascii_standard_6x12, gb2312_12x12,
                       "Written by CNflysky 由CNflysky编写", WHITE);
    st7789_draw_string(0, 42, ascii_standard_8x16, gb2312_15x16,
                       "ST7789 由Linux硬件SPI驱动", WHITE);
    st7789_draw_string(0, 67, ascii_arial_20x24, gb2312_24x24, "ST7789驱动",
                       WHITE);
    st7789_draw_string(0, 100, ascii_times_25x32, gb2312_32x32, "ST7789驱动",
                       WHITE);
    st7789_send_buf();
    sleep(2);

    st7789_clear_buf();
    st7789_fill_screen(BLUE);
    st7789_draw_outline("st7789_printf测试");
    st7789_printf(0, 25, ascii_standard_6x12, gb2312_12x12, WHITE,
                  "%s 由%s编写", "Written by CNflysky", "CNflysky");
    st7789_printf(0, 42, ascii_standard_8x16, gb2312_15x16, WHITE,
                  "ST%d 由Linux硬件SPI驱动", 7789);
    st7789_printf(0, 67, ascii_arial_20x24, gb2312_24x24, WHITE, "ST%d驱动",
                  7789);
    st7789_printf(0, 100, ascii_times_25x32, gb2312_32x32, WHITE, "ST%d驱动",
                  7789);
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
    st7789_draw_string(0, 100, ascii_times_20x24, gb2312_24x24,
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
    st7789_draw_outline("图片显示测试");
    st7789_draw_string(20, 100, ascii_times_20x24, gb2312_24x24, "2秒后开始",
                       WHITE);
    st7789_send_buf();
    sleep(2);
    st7789_clear_buf();
    st7789_draw_pic(0, 0, 240, 240, (uint8_t *)gImage_qr);
    st7789_send_buf();
    sleep(2);
  }
}
