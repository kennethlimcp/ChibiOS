#include "display.h"
#include <hal.h>
#include <gfx.h>
// #include <chprintf.h>
// #include <stdio.h>
// #include <stdlib.h>

static font_t bigfont;
static font_t mediumfont;

void display_init(void)
{
    bigfont = gdispOpenFont("bigfont");
    mediumfont = gdispOpenFont("mediumfont");

    display_clear();
}

void display_clear(void)
{

}


static void draw_temp_digit(int i, char c)
{
    const uint8_t charw[5] = {70, 75, 75, 35, 75};
    const uint8_t charpos[5] = {0, 70, 145, 220, 255};
    int x = 6 + charpos[i];
    int y = 65;

    char buf[2] = {c, '\0'};
    gdispFillArea(x, y - 1, charw[i], 130, 1);
    gdispDrawString(x, y, buf, bigfont, 0);
}

void display_digit(void){
	gdispDrawString(400, 140, "Akku vähissä!", mediumfont, 0);
}

// static void draw_samples(int start)
// {
//     for (int i = start;
//          i < g_ephemerals.samplecount;
//          i++)
//     {
//         int x1 = g_samples[i].time;
//         int y1 = g_samples[i].temperature;
//         int x0 = x1, y0 = y1;
//
//         if (i > 0)
//         {
//             x0 = g_samples[i - 1].time;
//             y0 = g_samples[i - 1].temperature;
//         }
//
//         if (x1 - x0 > g_ephemerals.timescale * 3 &&
//             x1 - x0 > 300)
//             continue; // Don't connect samples that are way apart
//
//         graph_drawline(x0, y0, x1, y1);
//     }
// }

// static void draw_alarm(const char *alarm, bool white_on_black, bool full_clear)
// {
//     int x = 370, y = 60, w = 80, h = 50;
//
//     if (white_on_black)
//     {
//         // Draw value with white-on-black during changes to avoid persistence.
//         gdispFillArea(x, y, w, h, Black);
//         gdispDrawStringBox(x, y, w, h, alarm, mediumfont, White, justifyRight);
//     }
//     else if (full_clear)
//     {
//         // Intensively clear the background to get rid of persistence
//         for (int i = 0; i < 3; i++)
//         {
//             gdispFillArea(x - 2, y - 2, w + 4, h + 4, White);
//             gdispDrawStringBox(x, y, w, h, alarm, mediumfont, Black, justifyRight);
//             gdispFlush();
//         }
//     }
//     else
//     {
//         // Just normal draw
//         gdispDrawStringBox(x, y, w, h, alarm, mediumfont, Black, justifyRight);
//     }
// }
//
// // static void draw_alarmtime()
// // {
// //     int x = 500, y = 60, w = 270, h = 50;
// //     gdispFillArea(x - 1, y - 1, w + 2, h + 2, White);
// //     gdispDrawStringBox(x, y, w, h, g_ephemerals.alarmtime, mediumfont, Black, justifyRight);
// // }
//
// static void draw_lowbatt()
// {
//     gdispDrawString(400, 140, "Akku vähissä!", mediumfont, 0);
// }

// void display_full_redraw()
// {
//     cull_samples();
//     update_ylimits();
//     update_prediction();
//     update_alarmtime();
//
//     gdispSetPowerMode(powerOn);
//     gdispClear(1);
//
//     g_ephemerals.batt_low = battery_low();
//
//     // Draw battery low indicator text
//     if (g_ephemerals.batt_low)
//     {
//         draw_lowbatt();
//     }
//
//     // Current temperature
//     gdispDrawRoundedBox(5, 5, 350, 200, 16, 0);
//     gdispDrawString(15, 15, "Nyt ", mediumfont, 0);
//     for (int i = 0; i < 5; i++)
//     {
//         draw_temp_digit(i, g_ephemerals.temperature[i]);
//     }
//     gdispDrawString(295, 15, "°C", mediumfont, 0);
//
//     // Alarm limit
//     gdispDrawRoundedBox(360, 5, 435, 120, 16, 0);
//     gdispDrawString(370, 15, "Hälytys", mediumfont, 0);
//     gdispDrawString(450, 60, "°C", mediumfont, 0);
//     draw_alarm(g_ephemerals.alarm, false, false);
//     draw_alarmtime();
//
//     // Graph
//     graph_drawgrid(0, g_ephemerals.xrange,
//                    g_ephemerals.ymin, g_ephemerals.ymax);
//
//     // Draw all samples
//     draw_samples(0);
//
//     // Draw prediction
//     if (g_ephemerals.have_prediction)
//     {
//         graph_drawlinear(g_ephemerals.pred_x0, g_ephemerals.pred_y0, g_ephemerals.pred_uc_per_sec);
//     }
//
//     gdispSetPowerMode(powerOff);
//
//     g_ephemerals.need_full_update = false;
//     g_prev_ephemerals = g_ephemerals;
// }
//
// void display_partial_redraw()
// {
//     if (g_ephemerals.need_full_update)
//     {
//         display_full_redraw();
//         return;
//     }
//
//     if (memcmp(&g_prev_ephemerals, &g_ephemerals, sizeof(g_ephemerals)) == 0)
//         return;
//
//     gdispSetPowerMode(powerOn);
//     g_ephemerals.batt_low |= battery_low();
//
//     // Draw battery low indicator text
//     if (g_ephemerals.batt_low && !g_prev_ephemerals.batt_low)
//     {
//         draw_lowbatt();
//     }
//
//     // Draw current temperature
//     for (int i = 0; i < 5; i++)
//     {
//         if (g_ephemerals.temperature[i] != g_prev_ephemerals.temperature[i])
//             draw_temp_digit(i, g_ephemerals.temperature[i]);
//     }
//
//     // Draw new samples
//     draw_samples(g_prev_ephemerals.samplecount);
//
//     // Draw alarm limit
//     bool alarm_changed = false;
//     if (strcmp(g_ephemerals.alarm, g_prev_ephemerals.alarm) != 0)
//     {
//         alarm_changed = true;
//         draw_alarm(g_ephemerals.alarm, true, false);
//     }
//     else if (g_prev_ephemerals.alarm_white_on_black)
//     {
//         draw_alarm(g_ephemerals.alarm, false, true);
//     }
//
//     // Draw alarm time estimate
//     if (!alarm_changed)
//         update_alarmtime();
//
//     if (strcmp(g_ephemerals.alarmtime, g_prev_ephemerals.alarmtime) != 0)
//         draw_alarmtime();
//
//     gdispSetPowerMode(powerOff);
//     memcpy(&g_prev_ephemerals, &g_ephemerals, sizeof(g_ephemerals));
//
//     // Track whether we still need to redraw alarm field
//     g_prev_ephemerals.alarm_white_on_black = alarm_changed;
//     g_ephemerals.alarm_white_on_black = false;
// }
