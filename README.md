# st7789_rpi
[Simplified Chinese](https://github.com/CNflysky/st7789_rpi/blob/main/README_zh.md)  
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

## Setup software
### Raspberry Pi
Enter `raspi-config`,enable `SPI Interface` and exit.  
You may need to install the `gpiod` , `make` and `cmake` package as well:  
`sudo apt install libgpiod-dev gpiod make cmake`  

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
                target = <&pio>;
                __overlay__ {
                        spi1_cs1: spi1_cs1 {
                                pins = "PA10";
                                function = "gpio_out";
                                output-high;
                        };
                };
        };

    fragment@2 {
                target = <&spi0>;
                __overlay__ {
                        #address-cells = <1>;
                        #size-cells = <0>;
                        status = "okay";
                        spidev {
                                compatible = "spidev";
                                status = "okay";
                                reg = <0>;
                                spi-max-frequency = <1000000>;
                        };
                };
        };

        fragment@3 {
                target = <&spi1>;
                __overlay__ {
                        #address-cells = <1>;
                        #size-cells = <0>;
                        status = "okay";
            			pinctrl-names = "default", "default";
                        pinctrl-1 = <&spi1_cs1>;
                        cs-gpios = <0>, <&pio 0 10 0>;
                        spidev@0 {
                                compatible = "spidev";
                                status = "okay";
                                reg = <0>;
                                spi-max-frequency = <1000000>;
                        };
						
           	 			spidev@1 {
                                compatible = "spidev";
                                status = "okay";
                                reg = <1>;
                                spi-max-frequency = <1000000>;
                        };
                };
        };
};
```
It will enable two spi interfaces and enable two cs pins(/dev/spidev1.0 and /dev/spidev1.1).  
use `armbian-add-overlay` to apply it.

You may need to install the `gpiod` , `make` and `cmake` package as well:  
`sudo apt install libgpiod-dev gpiod make cmake`  

## Clone this repository  
`git clone https://github.com/CNflysky/st7789_rpi.git`  

## Modify Pin selection
open `examples/single_device_test.c`, uncomment the following line for board selection:
```c
// #define OPIZERO
// #define RPI4B
```
and look for `st7789config_t config` struct,modify `dc_pin` and `cs_pin`.
```c
st7789config_t config = {.dc_pin = 18,
                         .reset_pin = 17,
                         .gpio_dc_chip = "gpiochip0",
                         .gpio_reset_chip = "gpiochip0",
                         .height = 240,
                         .width = 240,
                         .spi_path = "/dev/spidev0.0",
                         .spi_speed = 40000000};
gt30config_t gt30conf = {.spi_path = "/dev/spidev0.1", .spi_speed = 40000000};
```

## Compile and run 
```bash
mkdir build
cd build
cmake ..
make -j8
./st7789
```
If runs failed,try `sudo`.
