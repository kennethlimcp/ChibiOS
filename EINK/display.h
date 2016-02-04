/* Manages the state of the display, including the graph contents and current
 * numeric readings. Keeps track of what needs to be redrawn. */

#pragma once

#include <ch.h>

void display_init(void);
void display_clear(void);
void display_digit(void);
// int display_samplecount();
// void display_export_csv(BaseSequentialStream *chp);
// void display_update_temperature();
// void display_set_alarm(int celcius);

// static inline void display_full_redraw();
// static inline void display_partial_redraw();
