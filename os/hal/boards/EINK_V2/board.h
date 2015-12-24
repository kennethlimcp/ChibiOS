/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for the ST INEMO-M1 Discovery board.
 */

/*
 * Board identifier.
 */
#define EINK_V2
#define BOARD_NAME              "Eink v0.2.0 driver"

//#define NUCLEO_HSE_CRYSTAL
/*
 * Board frequencies.
 */
#define STM32_LSECLK            32768

//#if defined(NUCLEO_EXTERNAL_OSCILLATOR)
//#define STM32_HSECLK            8000000
//#define STM32_HSE_BYPASS

//#elif defined(NUCLEO_HSE_CRYSTAL)
#define STM32_HSECLK            8000000

//#else
//#define STM32_HSECLK            0
//#endif

/*
 * MCU type, supported types are defined in ./os/hal/platforms/hal_lld.h.
 */
#define STM32F10X_MD

/*
 * IO pins assignments.
 */
#define GPIO_EINK_D0												0
#define GPIO_EINK_D1												1
#define GPIO_EINK_D2												2
#define GPIO_EINK_D3												3
#define GPIO_EINK_D4												4
#define GPIO_EINK_D5												5
#define GPIO_EINK_D6												6
#define GPIO_EINK_D7												7
#define GPIOA_RGB_GREEN									8
#define GPIOA_RGB_BLUE										9
#define GPIOA_RGB_RED											10
#define GPIOA_PA11														11	//USBM
#define GPIOA_PA12														12	//USBP
#define GPIOA_SWDIO													13	//JTMS
#define GPIOA_SWCLK													14	//JTCK
#define GPIOA_PA15														15	//JTDI

#define GPIOB_BM_PGOO           0
#define GPIOB_BM_CHG            1
#define GPIOB_PB2               2
#define GPIOB_SWO               3	//JTDO
#define GPIOB_PB4               4	//JNTRST
#define GPIOB_USB_DISC          5	//USB_DISC
#define GPIOB_SCL               6	//I2C SCL
#define GPIOB_SDA               7	//I2C SDA
#define GPIOB_BUTTON            8 //MODE button
#define GPIOB_EINK_VDD          9
#define GPIOB_UART_TX           10
#define GPIOB_UART_RX           11
#define GPIOB_SD_CS             12
#define GPIOB_SPI_SCK           13
#define GPIOB_SPI_MISO          14
#define GPIOB_SPI_MOSI          15

#define GPIOC_EINK_CL           0
#define GPIOC_EINK_LE           1
#define GPIOC_EINK_OE           2
#define GPIOC_EINK_SHR          3
#define GPIOC_EINK_SPH          4
#define GPIOC_EINK_GMODE        5
#define GPIOC_EINK_RL           6
#define GPIOC_EINK_SPV										7
#define GPIOC_EINK_VBORDER      8
#define GPIOC_EINK_CKV          9
#define GPIOC_SMPS_ON           10
#define GPIOC_POS_EN            11
#define GPIOC_NEG_EN            12
#define GPIOC_POS_ON            13
#define GPIOC_OSC32_IN          14
#define GPIOC_OSC32_OUT         15

#define GPIOD_OSC_IN            0
#define GPIOD_OSC_OUT           1
#define GPIOD_PD2               2

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 *
 * The digits have the following meaning:
 *   0 - Analog input.
 *   1 - Push Pull output 10MHz.
 *   2 - Push Pull output 2MHz.
 *   3 - Push Pull output 50MHz.
 *   4 - Digital input.
 *   5 - Open Drain output 10MHz.
 *   6 - Open Drain output 2MHz.
 *   7 - Open Drain output 50MHz.
 *   8 - Digital input with PullUp or PullDown resistor depending on ODR.
 *   9 - Alternate Push Pull output 10MHz.
 *   A - Alternate Push Pull output 2MHz.
 *   B - Alternate Push Pull output 50MHz.
 *   C - Reserved.
 *   D - Alternate Open Drain output 10MHz.
 *   E - Alternate Open Drain output 2MHz.
 *   F - Alternate Open Drain output 50MHz.
 * Please refer to the STM32 Reference Manual for details.
 */

/*
 * Port A setup.
 * PA0  - PA10, OUTPUT
 * PA11 - PA12, OPENDRAIN OUTPUT
 * PA11 - PA15, INPUT
 */
#define VAL_GPIOACRL            0x33333333      /*  PA7...PA0 */
#define VAL_GPIOACRH            0x88888333      /* PA15...PA8 */
#define VAL_GPIOAODR            0xFFFFF800

/*
 * Port B setup.
 * All set to input for now,
 * PB05  -
 * PB10  - Alternate output  (USART3 TX)
 * PB11  - Normal input      (USART3 RX)
 */
#define VAL_GPIOBCRL            0x77377777      /*  PB7...PB0 */
#define VAL_GPIOBCRH            0x88884B37      /* PB15...PB8 */
#define VAL_GPIOBODR            0xFFFFF200

/*
 * Port C setup.
 */
#define VAL_GPIOCCRL            0x33333333      /*  PC7...PC0 */
#define VAL_GPIOCCRH            0x00733733     /* PC15...PC8 */
#define VAL_GPIOCODR            0xFFFFFF00

/*
 * Port D setup.
 * Everything input with pull-up except:
 * PD0  - Normal input              (GPIOD_OSC_IN).
 * PD1  - Normal input              (GPIOD_OSC_OUT).
 */
#define VAL_GPIODCRL            0x88888800      /*  PD7...PD0 */
#define VAL_GPIODCRH            0x88888888      /* PD15...PD8 */
#define VAL_GPIODODR            0xFFFFE400

/*
 * Port E setup.
 * Everything input with pull-up except:
 */
#define VAL_GPIOECRL            0x88888888      /*  PE7...PE0 */
#define VAL_GPIOECRH            0x88888888      /* PE15...PE8 */
#define VAL_GPIOEODR            0xFFFFFFFF

/*
 * USB bus activation macro, required by the USB driver.
 */
#define usb_lld_connect_bus(usbp) palClearPad(GPIOB, GPIOB_USB_DISC)

/*
 * USB bus de-activation macro, required by the USB driver.
 */
#define usb_lld_disconnect_bus(usbp) palSetPad(GPIOB, GPIOB_USB_DISC)

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
