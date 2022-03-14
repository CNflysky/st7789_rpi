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
你可能还需要安装 `gpiod` , `make` 和 `cmake` 软件包:  
`sudo apt install libgpiod-dev gpiod make cmake`  
打开 ``examples/single_device_test.c`,取消`RPI4B`这行的注释:
```c
// #define OPIZERO
#define RPI4B
```

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
这个文件会启用两个SPI总线和两根CS线(/dev/spidev1.0 和 /dev/spidev1.1).  
使用 `armbian-add-overlay` 来应用它。

你可能还需要安装 `gpiod` , `make` 和 `cmake` 软件包:  
`sudo apt install libgpiod-dev gpiod make cmake`  

打开 ``examples/single_device_test.c`,取消`OPIZERO`这行的注释:
```c
#define OPIZERO
// #define RPI4B
```

## 克隆仓库
`git clone https://github.com/CNflysky/st7789_rpi.git`  

## 修改引脚定义
打开 ``examples/single_device_test.c`,注意观察 `st7789config_t config` 结构体,修改 `dc_pin` 和 `cs_pin`.
如果有必要，修改 `gpio_dc_chip` 与 `gpio_reset_chip` 以配合你的引脚设定.
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


## 编译并运行 
```bash
mkdir build
cd build
cmake ..
make -j8
./st7789
```
如果运行失败，试试 `sudo`.
