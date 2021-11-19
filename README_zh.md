# st7789_rpi
一个简单的Linux平台ST7789驱动库，使用纯C编写。  
屏幕必须与开发板使用**硬件SPI**的方式进行连接。  

# 屏幕型号

1.3英寸IPS屏幕，驱动IC ST7789V，板载GT30L32字库芯片与MicroSD卡槽。

# 测试过的平台

树莓派4B 4G内存
香橙派Zero 
香橙派Zero2

# 如何使用
## 将你的模组连接在板子上:  
| ST7789 PIN | RPI 4B |
| - | - |  
| VCC | 3.3V |  
| GND | 0V/GND |  
| SCL | GPIO11 |  
| SDA | GPIO10 |  
| RES | GPIO17 |  
| DC | GPIO18 |  
| CS1 | GPIO8 |
| CS2 | GPIO7 |
| FSO | GPIO9 |

| ST7789 PIN | OPI Zero |
| - | - |  
| VCC | 3.3V |  
| GND | 0V/GND |  
| SCL | PA14 |  
| SDA | PA15 |  
| RES | PG06 |  
| DC | PG07 |  
| CS1 | PA13 |
| CS2 | PA10 |
| FSO | PA16 |

## 软件设置
### Raspberry Pi
进入 `raspi-config`,启用 `SPI Interface` 然后退出.  
你可能还需要安装 `gpiod` 和 `make` 软件包:  
`sudo apt install libgpiod-dev gpiod make`  

### Orange Pi Zero

导入下面这个dts文件：  
```dts
/dts-v1/;
/plugin/;

/ {
	compatible = "allwinner,sun8i-h3";

	fragment@0 {
		target-path = "/aliases";
		__overlay__ {
			spi0 = "/soc/spi@01c68000";
			spi1 = "/soc/spi@01c69000";
		};
	};

	fragment@1 {
		target = <&spi0>;
		__overlay__ {
			#address-cells = <1>;
			#size-cells = <0>;
			spidev {
				compatible = "spidev";
				status = "disabled";
				reg = <0>;
				spi-max-frequency = <1000000>;
			};
		};
	};

	fragment@2 {
		target = <&spi1>;
		__overlay__ {
			#address-cells = <1>;
			#size-cells = <0>;
			spidev {
				compatible = "spidev";
				status = "disabled";
				reg = <0>;
				spi-max-frequency = <1000000>;
			};
		};
	};

	fragment@3 {
		target = <&spi0>;
		__overlay__ {
			#address-cells = <1>;
			#size-cells = <0>;
			status = "okay";

			spidev@0 {
				reg = <0>; /* Chip Select 0 */
				compatible = "spidev";
				spi-max-frequency = <1000000>;
				status = "okay";
			};
		};
	};

	fragment@4 {
		target = <&pio>;
		__overlay__ {
			spi1_cs1: spi1_cs1 {
				pins = "PA10";
				function = "gpio_out";
				output-high;
			};
		};
	};

	fragment@5 {
		target = <&spi1>;
		__overlay__ {
			pinctrl-names = "default", "default";
			pinctrl-1 = <&spi1_cs1>;
			cs-gpios = <0>, <&pio 0 10 0>; /* PA10 */
		};
	};

	fragment@6 {
		target = <&spi1>;
		__overlay__ {
			#address-cells = <1>;
			#size-cells = <0>;
			status = "okay";

			spidev@0 {
				reg = <0>; /* Chip Select 0 */
				compatible = "spidev";
				spi-max-frequency = <1000000>;
				status = "okay";
			};
			spidev@1 {
				reg = <1>; /* Chip Select 1 */
				compatible = "spidev";
				spi-max-frequency = <1000000>;
				status = "okay";
			};
		};
	};
};
```
这个文件会启用两个SPI总线和两根CS线(/dev/spidev1.0 和 /dev/spidev1.1).  
使用 `armbian-add-overlay` 来应用它。

你可能还需要安装 `gpiod` 和 `make` 软件包:  
`sudo apt install libgpiod-dev gpiod make`  

## 克隆仓库
`git clone https://github.com/CNflysky/st7789_rpi.git`  

## 修改引脚定义
打开 `src/st7789_main.c`, 看下面的代码:
```c
int main() {
  /*
  Typically usage:
  1st: acquire 'st7789_dc' & 'st7789_reset' these 2 gpios.
  2nd: open spidev and set main spi param.
  optional:set font chip spi param.
  3rd: init screen.
  4th: clear_buf()
  5th: draw sth on screen.
  6th: send_buf().
  */
  signal(SIGINT, exit_handler);

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
  st7789_test_procedure();
  return 0;
}
```
根据注释来修改代码.

## Compile and run 
`make -j8 && ./st7789`  
如果运行失败，试试 `sudo`.
