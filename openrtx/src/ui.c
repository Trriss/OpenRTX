/***************************************************************************
 *   Copyright (C) 2020 by Federico Amedeo Izzo IU2NUO,                    *
 *                         Niccolò Izzo IU2KIN,                            *
 *                         Silvano Seva IU2KWO                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>   *
 ***************************************************************************/

/*
 * The graphical user interface (GUI) works by splitting the screen in 
 * horizontal rows, with row height depending on vertical resolution.
 * 
 * The general screen layout is composed by an upper status bar at the
 * top of the screen and a lower status bar at the bottom.
 * The central portion of the screen is filled by two big text/number rows
 * And a small row.
 *
 * Below is shown the row height for two common display densities.
 *
 *        160x128 display (MD380)            Recommended font size
 *      ┌─────────────────────────┐
 *      │  top_status_bar (16 px) │  8 pt font with 4 px vertical padding
 *      ├─────────────────────────┤
 *      │      Line 1 (32px)      │  16 pt font with 8 px vertical padding
 *      │                         │
 *      │      Line 2 (32px)      │  16 pt font with 8 px vertical padding
 *      │                         │
 *      │      Line 3 (32px)      │  16 pt font with 8 px vertical padding
 *      │                         │
 *      ├─────────────────────────┤
 *      │bottom_status_bar (16 px)│  8 pt font with 4 px vertical padding
 *      └─────────────────────────┘
 *
 *         128x64 display (GD77)
 *      ┌─────────────────────────┐
 *      │  top_status_bar (8 px)  │  8 pt font without vertical padding
 *      ├─────────────────────────┤
 *      │      Line 1 (16px)      │
 *      │      Line 2 (16px)      │
 *      │      Line 3 (16px)      │
 *      ├─────────────────────────┤
 *      │ bottom_status_bar (8 px)│  8 pt font without vertical padding
 *      └─────────────────────────┘
 */

#include <stdio.h>
#include "ui.h"
#include "graphics.h"
#include "rtc.h"
#include "platform.h"

color_t color_white = {255, 255, 255};

void ui_drawTopBar()
{
    // Top bar printing position, uses 4 px padding
    point_t top_bar_pos = {0, 5};

    // Print clock on top bar
    char clock_buf[6] = "";
    curTime_t time = rtc_getTime();
    snprintf(clock_buf, sizeof(clock_buf), "%2d:%2d", time.hour, time.minute);
    gfx_print(top_bar_pos, clock_buf, FONT_SIZE_1, TEXT_ALIGN_CENTER, color_white);

    // Print battery voltage on top bar, use 4 px padding
    // TODO: Replace with battery icon
    char bat_buf[6] = "";
    float v_bat = platform_getVbat();
    snprintf(bat_buf, sizeof(bat_buf), "%.1fV ", v_bat);
    gfx_print(top_bar_pos, bat_buf, FONT_SIZE_1, TEXT_ALIGN_RIGHT, color_white);
}

void ui_drawVFO(state_t state)
{
    // Middle line printing positions, uses 8 px padding
    point_t line1_pos = {0, 25};
    point_t line2_pos = {0, 57};
    point_t line3_pos = {0, 89};

    // Print VFO frequencies
    char freq_buf[20] = "";
    snprintf(freq_buf, sizeof(freq_buf), "Rx: %09.5f", state.rx_freq);
    gfx_print(line1_pos, freq_buf, FONT_SIZE_3, TEXT_ALIGN_CENTER, color_white);
    snprintf(freq_buf, sizeof(freq_buf), "Tx: %09.5f", state.tx_freq);
    gfx_print(line2_pos, freq_buf, FONT_SIZE_3, TEXT_ALIGN_CENTER, color_white);
}

void ui_drawMainScreen(state_t state)
{
    ui_drawTopBar();
    ui_drawVFO(state);
}

void ui_init()
{
}

bool ui_update(state_t state, uint32_t keys)
{
    gfx_clearScreen();
    ui_drawMainScreen(state);
    return true;
}

void ui_terminate()
{
}
