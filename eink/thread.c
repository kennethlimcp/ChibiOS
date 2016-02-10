
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

	/*
	 * Creates the blinker thread.
	 */
	// chThdCreateStatic(waThread1, sizeof(waThread1), HIGHPRIO, Thread1, NULL);
	// chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO, Thread2, NULL);

	/*
	 * Normal main() thread activity, in this demo it does nothing except
	 * sleeping in a loop and check the button state.
	 */
