## STM32F0 Discovery Overview

See [this page](https://github.com/RIOT-OS/RIOT/wiki/Getting-started-with-STM32F%5B0%7C3%7C4%5Ddiscovery-boards) for a quick getting started guide.

## Hardware

![Stm32f0discovery with RIOT pin names](https://raw.githubusercontent.com/wiki/RIOT-OS/RIOT/images/stm32f0discovery_pinout_RIOT.png)


### MCU
| MCU 		| STM32F051R8T6 		|
|:------------- |:--------------------- |
| Family	| ARM Cortex-M0 	|
| Vendor	| ST Microelectronics	|
| RAM		| 8Kb	|
| Flash		| 64Kb				|
| Frequency	| 48MHz (using the on-board 8MHz Oszillator of the ST-Link) |
| FPU		| no				|
| Timers	| 9 (8x 16-bit, 1x 32-bit [TIM2])	|
| ADCs		| 1x 16-channel 12-bit			|
| UARTs		| 2 				|
| SPIs		| 2					|
| I2Cs		| 2 				|
| Vcc		| 2.0V - 3.6V			|
| Datasheet 	| [Datasheet](http://www.st.com/web/en/resource/technical/document/datasheet/DM00039193.pdf) |
| Reference Manual | [Reference Manual](http://www.st.com/web/en/resource/technical/document/reference_manual/DM00031936.pdf) |
| Programming Manual | [Programming Manual](http://www.st.com/web/en/resource/technical/document/programming_manual/DM00051352.pdf) |
| Board Manual	| [Board Manual](http://www.st.com/st-web-ui/static/active/en/resource/technical/document/user_manual/DM00050135.pdf)|

### Pin mapping in RIOT

Please refer to [this document](https://docs.google.com/spreadsheets/d/1CtaWwjzOiev63Du2gwFeeD0_uFtVtL5Id-AD_w9p9jQ/edit?usp=sharing) for RIOTs static pin mapping chosen for this board. This mapping is completely arbitrary, it can be adjusted in `boards/stm32f0discovery/include/periph_conf.h`

### User Interface

2 Buttons:

| NAME	| USER 	| RESET 	|
|:----- |:----- |:--------- |
| Pin 	| PA0 (IN) | NRST	|

2 LEDs:

| NAME	| LD3	| LD4	|
| -----	| -----	| -----	|
| Color	| green	| blue	|
| Pin	| PC9	| PC8	|


## Supported Toolchains

For using the STM32F3discovery board we strongly recommend the usage of the [GNU Tools for ARM Embedded Processors](https://launchpad.net/gcc-arm-embedded) toolchain.


## Using UART

1. connect your usb tty to: RX=PB7 TX=PB6 and GND=GND
2. done