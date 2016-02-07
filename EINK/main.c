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


#define serialDriver                  (&SD3)
#define stream_driver                 ((BaseSequentialStream *)serialDriver)

/*===========================================================================*/
/* Command line related.                                                     */
/*===========================================================================*/

static void cmd_mem(BaseSequentialStream *chp, int argc, char *argv[])
{
  size_t n, size;

  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: mem\r\n");
    return;
  }
  n = chHeapStatus(NULL, &size);
  chprintf(chp, "core free memory : %u bytes\r\n", chCoreGetStatusX());
  chprintf(chp, "heap fragments   : %u\r\n", n);
  chprintf(chp, "heap free total  : %u bytes\r\n", size);
}

static void cmd_threads(BaseSequentialStream *chp, int argc, char *argv[])
{
  static const char *states[] = {CH_STATE_NAMES};
  thread_t *tp;

  (void)argv;
  if (argc > 0) {
    chprintf(chp, "Usage: threads\r\n");
    return;
  }
  chprintf(chp, " addr     pc       stack    prio refs state         name\r\n");
  tp = chRegFirstThread();
  do {
    chprintf(chp, " %-8lx %-8lx %-8lx %4lu %4lu %-12s  %-10s\r\n",
      (uint32_t)tp, (uint32_t)tp->p_ctx.r13->lr, (uint32_t)tp->p_ctx.r13,
      (uint32_t)tp->p_prio, (uint32_t)(tp->p_refs - 1),
      states[tp->p_state],
      tp->p_name);
    tp = chRegNextThread(tp);
  } while (tp != NULL);
}

static const ShellCommand commands[] = {
  {"mem", cmd_mem},
  {"threads", cmd_threads},
  {NULL, NULL}
};

static const ShellConfig shellConfig = {
  (BaseSequentialStream *)serialDriver,
  commands
};

static thread_t *shelltp = NULL;
static THD_WORKING_AREA(waShellThread, 768);

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
   * Activates the serial driver 1 and SDC driver 1 using default
   * configuration.
   */
  sdStart(serialDriver, NULL);
  //sdcStart(&SDCD1, NULL);

  /*
   * Shell manager initialization.
   */
  shellInit();

  /*
   * Creates the blinker thread.
   */
  chThdCreateStatic(waBlinkerThread, sizeof(waBlinkerThread), NORMALPRIO, blinker_thread, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and listen for events.
   */
  while (TRUE) {
    if (!shelltp)
      shelltp = shellCreateStatic(&shellConfig, waShellThread, sizeof(waShellThread), NORMALPRIO);
    else if (chThdTerminatedX(shelltp)) {
      chThdRelease(shelltp);    /* Recovers memory of the previous shell.   */
      shelltp = NULL;           /* Triggers spawning of a new shell.        */
    }
  }
}
