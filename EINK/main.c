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

#include "ch.h"
#include "hal.h"
#include <gfx.h>

//#include "eink.h"

// #ifndef GDISP_SCREEN_HEIGHT
// #       define GDISP_SCREEN_HEIGHT 600
// #endif
//
// #ifndef GDISP_SCREEN_WIDTH
// #       define GDISP_SCREEN_WIDTH 800
// #endif
//
//
// /** Fast vertical clock pulse for gate driver, used during initializations */
// static void vclock_quick(void)
// {
// 		setpin_ckv(TRUE);
// 		eink_delay(1);
// 		setpin_ckv(FALSE);
// 		eink_delay(4);
// }
//
// /** Horizontal clock pulse for clocking data into source driver */
// static void hclock(void)
// {
//     clockdelay();
//     setpin_cl(TRUE);
//     clockdelay();
//     setpin_cl(FALSE);
// }
//
// /** Start a new vertical gate driver scan from top.
//  * Note: Does not clear any previous bits in the shift register,
//  *       so you should always scan through the whole display before
//  *       starting a new scan.
//  */
// static void vscan_start(void)
// {
//     setpin_gmode(TRUE);
//     vclock_quick();
//     setpin_spv(FALSE);
// 				vclock_quick();
//     setpin_spv(TRUE);
//     vclock_quick();
// }
//
// /** Waveform for strobing a row of data onto the display.
//  * Attempts to minimize the leaking of color to other rows by having
//  * a long idle period after a medium-length strobe period.
//  */
// static void vscan_write(void)
// {
//     setpin_ckv(TRUE);
//     setpin_oe(TRUE);
//     eink_delay(5);
//     setpin_oe(FALSE);
//     setpin_ckv(FALSE);
//     eink_delay(200);
// }
//
// /** Waveform used when clearing the display. Strobes a row of data to the
//  * screen, but does not mind some of it leaking to other rows.
//  */
// static void vscan_bulkwrite(void)
// {
//     setpin_ckv(TRUE);
//     eink_delay(20);
//     setpin_ckv(FALSE);
//     eink_delay(200);
// }
//
// /** Waveform for skipping a vertical row without writing anything.
//  * Attempts to minimize the amount of change in any row.
//  */
// static void vscan_skip(void)
// {
//     setpin_ckv(TRUE);
//     eink_delay(1);
//     setpin_ckv(FALSE);
//     eink_delay(100);
// }
//
// /** Stop the vertical scan. The significance of this escapes me, but it seems
//  * necessary or the next vertical scan may be corrupted.
//  */
// static void vscan_stop(void)
// {
//     setpin_gmode(FALSE);
//     vclock_quick();
//     vclock_quick();
//     vclock_quick();
//     vclock_quick();
//     vclock_quick();
// }
//
// /** Start updating the source driver data (from left to right). */
// static void hscan_start(void)
// {
//     /* Disable latching and output enable while we are modifying the row. */
//     setpin_le(FALSE);
//     setpin_oe(FALSE);
//
//     /* The start pulse should remain low for the duration of the row. */
//     setpin_sph(FALSE);
// }
//
// /** Write data to the horizontal row. */
// static void hscan_write(const uint8_t *data, int count)
// {
//     while (count--)
//     {
//         /* Set the next byte on the data pins */
//         setpins_data(*data++);
//
//         /* Give a clock pulse to the shift register */
//         hclock();
//     }
// }
//
// /** Finish and transfer the row to the source drivers.
//  * Does not set the output enable, so the drivers are not yet active. */
// static void hscan_stop(void)
// {
//     /* End the scan */
//     setpin_sph(TRUE);
//     hclock();
//
//     /* Latch the new data */
//     setpin_le(TRUE);
//     clockdelay();
//     setpin_le(FALSE);
// }
//
// /** Turn on the power to the E-Ink panel, observing proper power sequencing. */
// static void power_on(void)
// {
//     unsigned i;
//
//     /* First the digital power supply and signal levels. */
//     setpower_vdd(TRUE);
//     setpin_le(FALSE);
//     setpin_oe(FALSE);
//     setpin_cl(FALSE);
//     setpin_sph(TRUE);
//     setpins_data(0);
//     setpin_ckv(FALSE);
//     setpin_gmode(FALSE);
//     setpin_spv(TRUE);
//
//     /* Min. 100 microsecond delay after digital supply */
//     eink_delay(100);
//
//     /* Then negative voltages and min. 1000 microsecond delay. */
//     setpower_vneg(TRUE);
//     eink_delay(1000);
//
//     /* Finally the positive voltages. */
//     setpower_vpos(TRUE);
//
//     /* Clear the vscan shift register */
//     vscan_start();
//     for (i = 0; i < GDISP_SCREEN_HEIGHT; i++)
//         vclock_quick();
//     vscan_stop();
// }
//
// /** Turn off the power, observing proper power sequencing. */
// static void power_off()
// {
//     /* First the high voltages */
//     setpower_vpos(FALSE);
//     setpower_vneg(FALSE);
//
//     /* Wait for any capacitors to drain */
//     chThdSleepMilliseconds(100);
//
//     /* Then put all signals and digital supply to ground. */
//     setpin_le(FALSE);
//     setpin_oe(FALSE);
//     setpin_cl(FALSE);
//     setpin_sph(FALSE);
//     setpins_data(0);
//     setpin_ckv(FALSE);
//     setpin_gmode(FALSE);
//     setpin_spv(FALSE);
//     setpower_vdd(FALSE);
// }
//
//
// #define BYTE_WHITE 0xAA
// #define BYTE_BLACK 0x55
//
// static void subclear(void)
// {
//     unsigned x, y;
//     uint8_t byte;
//
//     hscan_start();
//     //byte = color ? BYTE_WHITE : BYTE_BLACK;
// 				byte = BYTE_BLACK;
//     for (x = 0; x < GDISP_SCREEN_WIDTH; x++)
//     {
//         hscan_write(&byte, 1);
//     }
//     hscan_stop();
//
//     setpin_oe(TRUE);
//     vscan_start();
//     for (y = 0; y < GDISP_SCREEN_HEIGHT; y++)
//     {
//         vscan_bulkwrite();
//     }
//     vscan_stop();
//     setpin_oe(FALSE);
// }
//

// void gate_waveform(void){
// 		unsigned a = 0;
//
// 		chSysLockFromISR();
// 		setpin_gmode(true);
// 		eink_delay(3);
//
// 		setpin_spv(false);
// 		eink_delay(3);
//
// 		vclock_quick();
// 		eink_delay(3);
//
// 		setpin_spv(true);
// 		eink_delay(3);
//
// 		for (a = 0; a < GDISP_SCREEN_HEIGHT; a++)
// 							vscan_bulkwrite();
//
// 		setpin_gmode(false);
// 		eink_delay(3);
//
// 		vclock_quick();
// 		chSysUnlockFromISR();
// 		chThdSleepMilliseconds(1);
// }

/*
 * Red LED blinker thread, times are in milliseconds.
 */
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {
  (void)arg;

		chRegSetThreadName("data");
  while (true) {
			chThdSleepMilliseconds(1);
			// gate_waveform();
			// subclear();
  }
}

static THD_WORKING_AREA(waThread2, 128);
static THD_FUNCTION(Thread2, arg) {
  (void)arg;

		chRegSetThreadName("blinker");
  while (true) {
			if(palReadPad(GPIOB,GPIOB_BUTTON))
				palSetPad(GPIOA,GPIOA_RGB_RED);
			else
				palSetPad(GPIOA,GPIOA_RGB_GREEN);

			chThdSleepMilliseconds(50);

			if(palReadPad(GPIOB,GPIOB_BUTTON))
				palClearPad(GPIOA,GPIOA_RGB_RED);
			else
				palClearPad(GPIOA,GPIOA_RGB_GREEN);

			chThdSleepMilliseconds(50);
  }
}



/*
 * Application entry point.
 */
int main(void) {
  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

		// e-ink related
		//power_on();
		//setpins_data(0xFF);
		gfxInit();


	


  /*
   * Activates the serial driver 3 using the driver default configuration.
   */
  sdStart(&SD3, NULL);

  /*
   * Creates the blinker thread.
   */
  chThdCreateStatic(waThread1, sizeof(waThread1), HIGHPRIO, Thread1, NULL);
		chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, Thread2, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state.
   */
  while (true) {

				chThdSleepMicroseconds(1);

  }
}
