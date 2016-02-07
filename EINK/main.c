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
#include "shell.h"
#include "chprintf.h"
#include "eink-shell.h"

/*===========================================================================*/
/* Main and generic code.                                                    */
/*===========================================================================*/


/*
* LEDs blinker thread, times are in milliseconds.
*/
static THD_WORKING_AREA(waBlinkerThread, 128);
static THD_FUNCTION(blinker_thread, arg) {

  (void)arg;
  chRegSetThreadName("blinker");
  while (TRUE) {
    palSetPad(GPIOB, GPIOA_RGB_RED);
    chThdSleepMilliseconds(250);
    palClearPad(GPIOB, GPIOA_RGB_RED);
    chThdSleepMilliseconds(250);
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

  /*
   * Shell manager initialization.
   */
		einkShellInit();
		einkShellRestart();
  /*
   * Creates the blinker thread.
   */
  chThdCreateStatic(waBlinkerThread, sizeof(waBlinkerThread), NORMALPRIO, blinker_thread, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and listen for events.
   */
			while(TRUE){
				chThdSleepMilliseconds(500);
}
}
