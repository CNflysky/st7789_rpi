# st7789_rpi
simple st7789 panel driver for Raspberry Pi / Linux-based development boards written in pure c.
Display module must connected to board using **Hardware SPI**.

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

## Setup software
Enter `raspi-config`,enable `SPI Interface` and exit.  
You may need to install the `gpiod` and `make` package as well:  
`sudo apt install libgpiod-dev gpiod make`  
## Clone this repository  
`git clone https://github.com/CNflysky/st7789_rpi.git`  
## Compile and run 
`make && ./st7789`
