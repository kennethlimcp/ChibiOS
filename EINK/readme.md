Eink driver
======

- Running on the v0.2.0 board
- STM32F103RB, 128KB memory

This is initially designed to run the Particle firmware for the Spark core without the CC3000 code but somehow the bootloader kept entering the HardFault handler and it was taking too much of my time to get something basic working.

So ChibiOS it is! I thought it would be a steep learning curve ahead but managed to make the RGB led blink alternate colour within 5 minutes of hacking the demo code. That make things so much more fun so i decided to dive deeper and use it as the OS for this version.
