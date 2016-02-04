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
#include "display.h"
#include <gfx.h>

/*
 * Red LED blinker thread, times are in milliseconds.
 */
// static THD_WORKING_AREA(waThread1, 128);
// static THD_FUNCTION(Thread1, arg) {
//   (void)arg;
//
// 		chRegSetThreadName("data");
//   while (true) {
// 			chThdSleepMilliseconds(1);
// 			// gate_waveform();
// 			// subclear();
//   }
// }

// static THD_WORKING_AREA(waThread2, 128);
// static THD_FUNCTION(Thread2, arg) {
//   (void)arg;
//
// 		chRegSetThreadName("blinker");
//   while (true) {
// 			if(palReadPad(GPIOB,GPIOB_BUTTON))
// 				palSetPad(GPIOA,GPIOA_RGB_RED);
// 			else
// 				palSetPad(GPIOA,GPIOA_RGB_GREEN);
//
// 			chThdSleepMilliseconds(50);
//
// 			if(palReadPad(GPIOB,GPIOB_BUTTON))
// 				palClearPad(GPIOA,GPIOA_RGB_RED);
// 			else
// 				palClearPad(GPIOA,GPIOA_RGB_GREEN);
//
// 			chThdSleepMilliseconds(50);
//   }
// }
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
	gfxInit();
	gdispSetPowerMode(powerOn);
		// palSetPad(GPIOC,GPIOC_EINK_RL);
		// palSetPad(GPIOC,GPIOC_EINK_SHR);
		// palSetPad(GPIOC,GPIOC_EINK_SPH);
	display_init();

	/*
		* Activates the serial driver 3 using the driver default configuration.
		*/
	sdStart(&SD3, NULL);

	/*
	 * Creates the blinker thread.
	 */
	// chThdCreateStatic(waThread1, sizeof(waThread1), HIGHPRIO, Thread1, NULL);
	// chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, Thread2, NULL);

	/*
	 * Normal main() thread activity, in this demo it does nothing except
	 * sleeping in a loop and check the button state.
	 */

	palClearPad(GPIOA,GPIOA_RGB_RED);

	while (true) {
		palWritePad(GPIOC, GPIOC_EINK_CKV, TRUE);
		chSysPolledDelayX(US2ST(10));
		palWritePad(GPIOC, GPIOC_EINK_CKV, FALSE);
		chSysPolledDelayX(US2ST(1));
		// palSetPad(GPIOA,GPIOA_RGB_RED);
		// chThdSleepMilliseconds(50);
		// palClearPad(GPIOA,GPIOA_RGB_RED);
		// chThdSleepMilliseconds(50);
	}
}
