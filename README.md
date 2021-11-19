# st7789_rpi
[Simplified Chinese](https://github.com/CNflysky/ssd1315_monitor/blob/main/README_zh.md)  
simple st7789 panel driver for Raspberry Pi / Linux-based development boards written in pure c.
Display module must connected to board using **Hardware SPI**.

# Screen Model 

1'3 inch IPS,ST7789V driver IC,with GT30L32 font chip & MicroSD card slot.  

# Tested platforms

Raspberry Pi 4 Model B w/ 4GB RAM  
Orange Pi Zero  
Orange Pi Zero 2  

# How to use
## Wire your module to the board:  
| ST7789 PIN | RPI 4B |
| - | - |  
| VCC | 3.3V |  
| GND | 0V/GND |  
| SCL | GPIO11 |  
| SDA | GPIO10 |  
| RES | GPIO17 |  
| DC | GPIO18 |  
| CS | GPIO8/GND |

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

## Setup software
### Raspberry Pi
Enter `raspi-config`,enable `SPI Interface` and exit.  
You may need to install the `gpiod` and `make` package as well:  
`sudo apt install libgpiod-dev gpiod make`  

### Orange Pi Zero

import this dts file:
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
It will enable two spi interfaces and enable two cs pins(/dev/spidev1.0 and /dev/spidev1.1).  
use `armbian-add-overlay` to apply it.

You may need to install the `gpiod` and `make` package as well:  
`sudo apt install libgpiod-dev gpiod make`  

## Clone this repository  
`git clone https://github.com/CNflysky/st7789_rpi.git`  

## Modify Pin selection
open `src/st7789_main.c`, go to the following line:
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
Modify pin selection according to comments.

## Compile and run 
`make -j8 && ./st7789` 
If runs failed,try `sudo`.
