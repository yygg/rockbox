/***************************************************************************
 *             __________               __   ___.
 *   Open      \______   \ ____   ____ |  | _\_ |__   _______  ___
 *   Source     |       _//  _ \_/ ___\|  |/ /| __ \ /  _ \  \/  /
 *   Jukebox    |    |   (  <_> )  \___|    < | \_\ (  <_> > <  <
 *   Firmware   |____|_  /\____/ \___  >__|_ \|___  /\____/__/\_ \
 *                     \/            \/     \/    \/            \/
 * $Id$
 *
 * Copyright (C) 2002 Daniel Stenberg
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 **************************************************************************/
#include "plugin.h"
#include "time.h"
#include "lib/fixedpoint.h"



#define SS_TITLE       "Bouncer"

#define YSPEED 2
#define XSPEED 3
#define YADD -4

/* variable button definitions */
#if CONFIG_KEYPAD == RECORDER_PAD
#define BOUNCE_LEFT BUTTON_LEFT
#define BOUNCE_RIGHT BUTTON_RIGHT
#define BOUNCE_UP   BUTTON_UP
#define BOUNCE_DOWN BUTTON_DOWN
#define BOUNCE_QUIT (BUTTON_OFF | BUTTON_REL)
#define BOUNCE_MODE (BUTTON_ON | BUTTON_REL)

#elif CONFIG_KEYPAD == ARCHOS_AV300_PAD
#define BOUNCE_LEFT BUTTON_LEFT
#define BOUNCE_RIGHT BUTTON_RIGHT
#define BOUNCE_UP   BUTTON_UP
#define BOUNCE_DOWN BUTTON_DOWN
#define BOUNCE_QUIT (BUTTON_OFF | BUTTON_REL)
#define BOUNCE_MODE (BUTTON_ON | BUTTON_REL)

#elif CONFIG_KEYPAD == ONDIO_PAD
#define BOUNCE_LEFT BUTTON_LEFT
#define BOUNCE_RIGHT BUTTON_RIGHT
#define BOUNCE_UP   BUTTON_UP
#define BOUNCE_DOWN BUTTON_DOWN
#define BOUNCE_QUIT (BUTTON_OFF | BUTTON_REL)
#define BOUNCE_MODE (BUTTON_MENU | BUTTON_REL)

#elif (CONFIG_KEYPAD == IRIVER_H100_PAD) || \
      (CONFIG_KEYPAD == IRIVER_H300_PAD)
#define BOUNCE_LEFT BUTTON_LEFT
#define BOUNCE_RIGHT BUTTON_RIGHT
#define BOUNCE_UP   BUTTON_UP
#define BOUNCE_DOWN BUTTON_DOWN
#define BOUNCE_QUIT (BUTTON_OFF | BUTTON_REL)
#define BOUNCE_MODE (BUTTON_SELECT | BUTTON_REL)

#define BOUNCE_RC_QUIT (BUTTON_RC_STOP | BUTTON_REL)

#elif (CONFIG_KEYPAD == IPOD_4G_PAD) || \
      (CONFIG_KEYPAD == IPOD_3G_PAD) || \
      (CONFIG_KEYPAD == IPOD_1G2G_PAD)
#define BOUNCE_LEFT BUTTON_LEFT
#define BOUNCE_RIGHT BUTTON_RIGHT
#define BOUNCE_UP   BUTTON_SCROLL_BACK
#define BOUNCE_DOWN BUTTON_SCROLL_FWD
#define BOUNCE_QUIT (BUTTON_MENU | BUTTON_REL)
#define BOUNCE_MODE (BUTTON_SELECT | BUTTON_REL)

#elif (CONFIG_KEYPAD == IAUDIO_X5M5_PAD)
#define BOUNCE_LEFT BUTTON_LEFT
#define BOUNCE_RIGHT BUTTON_RIGHT
#define BOUNCE_UP   BUTTON_UP
#define BOUNCE_DOWN BUTTON_DOWN
#define BOUNCE_QUIT BUTTON_POWER
#define BOUNCE_MODE BUTTON_PLAY

#elif (CONFIG_KEYPAD == GIGABEAT_PAD)
#define BOUNCE_LEFT BUTTON_LEFT
#define BOUNCE_RIGHT BUTTON_RIGHT
#define BOUNCE_UP   BUTTON_UP
#define BOUNCE_DOWN BUTTON_DOWN
#define BOUNCE_QUIT BUTTON_POWER
#define BOUNCE_MODE BUTTON_A

#elif (CONFIG_KEYPAD == SANSA_E200_PAD)
#define BOUNCE_LEFT BUTTON_LEFT
#define BOUNCE_RIGHT BUTTON_RIGHT
#define BOUNCE_UP   BUTTON_SCROLL_BACK
#define BOUNCE_DOWN BUTTON_SCROLL_FWD
#define BOUNCE_QUIT BUTTON_POWER
#define BOUNCE_MODE BUTTON_SELECT

#elif (CONFIG_KEYPAD == SANSA_FUZE_PAD)
#define BOUNCE_LEFT BUTTON_LEFT
#define BOUNCE_RIGHT BUTTON_RIGHT
#define BOUNCE_UP   BUTTON_SCROLL_BACK
#define BOUNCE_DOWN BUTTON_SCROLL_FWD
#define BOUNCE_QUIT (BUTTON_HOME|BUTTON_REPEAT)
#define BOUNCE_MODE BUTTON_SELECT

#elif CONFIG_KEYPAD == SANSA_C200_PAD || \
      CONFIG_KEYPAD == SANSA_CLIP_PAD || \
      CONFIG_KEYPAD == SANSA_M200_PAD
#define BOUNCE_LEFT BUTTON_LEFT
#define BOUNCE_RIGHT BUTTON_RIGHT
#define BOUNCE_UP   BUTTON_UP
#define BOUNCE_DOWN BUTTON_DOWN
#define BOUNCE_QUIT BUTTON_POWER
#define BOUNCE_MODE BUTTON_SELECT

#elif (CONFIG_KEYPAD == IRIVER_H10_PAD)
#define BOUNCE_LEFT BUTTON_LEFT
#define BOUNCE_RIGHT BUTTON_RIGHT
#define BOUNCE_UP   BUTTON_SCROLL_UP
#define BOUNCE_DOWN BUTTON_SCROLL_DOWN
#define BOUNCE_QUIT BUTTON_POWER
#define BOUNCE_MODE BUTTON_PLAY

#elif (CONFIG_KEYPAD == GIGABEAT_S_PAD)
#define BOUNCE_LEFT BUTTON_LEFT
#define BOUNCE_RIGHT BUTTON_RIGHT
#define BOUNCE_UP   BUTTON_UP
#define BOUNCE_DOWN BUTTON_DOWN
#define BOUNCE_QUIT BUTTON_BACK
#define BOUNCE_MODE BUTTON_MENU

#elif (CONFIG_KEYPAD == MROBE100_PAD)
#define BOUNCE_LEFT BUTTON_LEFT
#define BOUNCE_RIGHT BUTTON_RIGHT
#define BOUNCE_UP   BUTTON_UP
#define BOUNCE_DOWN BUTTON_DOWN
#define BOUNCE_QUIT BUTTON_POWER
#define BOUNCE_MODE BUTTON_DISPLAY

#elif CONFIG_KEYPAD == IAUDIO_M3_PAD
#define BOUNCE_LEFT BUTTON_RC_REW
#define BOUNCE_RIGHT BUTTON_RC_FF
#define BOUNCE_UP   BUTTON_RC_VOL_UP
#define BOUNCE_DOWN BUTTON_RC_VOL_DOWN
#define BOUNCE_QUIT BUTTON_RC_REC
#define BOUNCE_MODE BUTTON_RC_MODE

#elif (CONFIG_KEYPAD == COWON_D2_PAD)
#define BOUNCE_QUIT BUTTON_POWER
#define BOUNCE_MODE BUTTON_MENU

#elif CONFIG_KEYPAD == CREATIVEZVM_PAD
#define BOUNCE_LEFT BUTTON_LEFT
#define BOUNCE_RIGHT BUTTON_RIGHT
#define BOUNCE_UP   BUTTON_UP
#define BOUNCE_DOWN BUTTON_DOWN
#define BOUNCE_QUIT BUTTON_BACK
#define BOUNCE_MODE BUTTON_MENU

#elif CONFIG_KEYPAD == PHILIPS_HDD1630_PAD
#define BOUNCE_LEFT BUTTON_LEFT
#define BOUNCE_RIGHT BUTTON_RIGHT
#define BOUNCE_UP   BUTTON_UP
#define BOUNCE_DOWN BUTTON_DOWN
#define BOUNCE_QUIT BUTTON_POWER
#define BOUNCE_MODE BUTTON_MENU

#elif CONFIG_KEYPAD == PHILIPS_HDD6330_PAD
#define BOUNCE_LEFT BUTTON_PREV
#define BOUNCE_RIGHT BUTTON_NEXT
#define BOUNCE_UP   BUTTON_UP
#define BOUNCE_DOWN BUTTON_DOWN
#define BOUNCE_QUIT BUTTON_POWER
#define BOUNCE_MODE BUTTON_MENU

#elif CONFIG_KEYPAD == PHILIPS_SA9200_PAD
#define BOUNCE_LEFT BUTTON_PREV
#define BOUNCE_RIGHT BUTTON_NEXT
#define BOUNCE_UP   BUTTON_UP
#define BOUNCE_DOWN BUTTON_DOWN
#define BOUNCE_QUIT BUTTON_POWER
#define BOUNCE_MODE BUTTON_MENU

#elif (CONFIG_KEYPAD == ONDAVX747_PAD)
#define BOUNCE_QUIT BUTTON_POWER
#define BOUNCE_MODE BUTTON_MENU

#elif (CONFIG_KEYPAD == ONDAVX777_PAD)
#define BOUNCE_QUIT BUTTON_POWER

#elif CONFIG_KEYPAD == MROBE500_PAD
#define BOUNCE_QUIT BUTTON_POWER

#elif CONFIG_KEYPAD == SAMSUNG_YH_PAD
#define BOUNCE_LEFT  BUTTON_LEFT
#define BOUNCE_RIGHT BUTTON_RIGHT
#define BOUNCE_UP    BUTTON_UP
#define BOUNCE_DOWN  BUTTON_DOWN
#define BOUNCE_QUIT  BUTTON_FFWD
#define BOUNCE_MODE  BUTTON_PLAY

#elif CONFIG_KEYPAD == PBELL_VIBE500_PAD
#define BOUNCE_LEFT  BUTTON_PREV
#define BOUNCE_RIGHT BUTTON_NEXT
#define BOUNCE_UP    BUTTON_UP
#define BOUNCE_DOWN  BUTTON_DOWN
#define BOUNCE_QUIT  BUTTON_REC
#define BOUNCE_MODE  BUTTON_MENU

#elif CONFIG_KEYPAD == MPIO_HD200_PAD
#define BOUNCE_LEFT BUTTON_VOL_DOWN
#define BOUNCE_RIGHT BUTTON_VOL_UP
#define BOUNCE_UP   BUTTON_PREV
#define BOUNCE_DOWN BUTTON_NEXT
#define BOUNCE_QUIT (BUTTON_REC | BUTTON_PLAY)
#define BOUNCE_MODE BUTTON_SELECT

#else
#error No keymap defined!
#endif

#ifdef HAVE_TOUCHSCREEN
#ifndef BOUNCE_LEFT
#define BOUNCE_LEFT BUTTON_MIDLEFT
#endif
#ifndef BOUNCE_RIGHT
#define BOUNCE_RIGHT BUTTON_MIDRIGHT
#endif
#ifndef BOUNCE_UP
#define BOUNCE_UP   BUTTON_TOPMIDDLE
#endif
#ifndef BOUNCE_DOWN
#define BOUNCE_DOWN BUTTON_BOTTOMMIDDLE
#endif
#ifndef BOUNCE_QUIT
#define BOUNCE_QUIT BUTTON_TOPLEFT
#endif
#ifndef BOUNCE_MODE
#define BOUNCE_MODE BUTTON_CENTER
#endif
#endif

#define LETTER_WIDTH  11
#define LETTER_HEIGHT 16

const unsigned char char_gen_12x16[][22] =
{
    { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
    { 0x00,0x00,0x00,0x7c,0xff,0xff,0x7c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x33,0x33,0x00,0x00,0x00,0x00,0x00 },
    { 0x00,0x00,0x3c,0x3c,0x00,0x00,0x3c,0x3c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
    { 0x00,0x10,0x90,0xf0,0x7e,0x1e,0x90,0xf0,0x7e,0x1e,0x10,0x02,0x1e,0x1f,0x03,0x02,0x1e,0x1f,0x03,0x02,0x00,0x00 },
    { 0x00,0x78,0xfc,0xcc,0xff,0xff,0xcc,0xcc,0x88,0x00,0x00,0x00,0x04,0x0c,0x0c,0x3f,0x3f,0x0c,0x0f,0x07,0x00,0x00 },
    { 0x00,0x38,0x38,0x38,0x00,0x80,0xc0,0xe0,0x70,0x38,0x1c,0x30,0x38,0x1c,0x0e,0x07,0x03,0x01,0x38,0x38,0x38,0x00 },
    { 0x00,0x00,0xb8,0xfc,0xc6,0xe2,0x3e,0x1c,0x00,0x00,0x00,0x00,0x1f,0x3f,0x31,0x21,0x37,0x1e,0x1c,0x36,0x22,0x00 },
    { 0x00,0x00,0x00,0x27,0x3f,0x1f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
    { 0x00,0x00,0xf0,0xfc,0xfe,0x07,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x03,0x0f,0x1f,0x38,0x20,0x20,0x00,0x00,0x00 },
    { 0x00,0x00,0x01,0x01,0x07,0xfe,0xfc,0xf0,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x38,0x1f,0x0f,0x03,0x00,0x00,0x00 },
    { 0x00,0x98,0xb8,0xe0,0xf8,0xf8,0xe0,0xb8,0x98,0x00,0x00,0x00,0x0c,0x0e,0x03,0x0f,0x0f,0x03,0x0e,0x0c,0x00,0x00 },
    { 0x00,0x80,0x80,0x80,0xf0,0xf0,0x80,0x80,0x80,0x00,0x00,0x00,0x01,0x01,0x01,0x0f,0x0f,0x01,0x01,0x01,0x00,0x00 },
    { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xb8,0xf8,0x78,0x00,0x00,0x00,0x00,0x00 },
    { 0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00 },
    { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x38,0x38,0x38,0x00,0x00,0x00,0x00,0x00 },
    { 0x00,0x00,0x00,0x00,0x80,0xc0,0xe0,0x70,0x38,0x1c,0x0e,0x18,0x1c,0x0e,0x07,0x03,0x01,0x00,0x00,0x00,0x00,0x00 },
    { 0xf8,0xfe,0x06,0x03,0x83,0xc3,0x63,0x33,0x1e,0xfe,0xf8,0x07,0x1f,0x1e,0x33,0x31,0x30,0x30,0x30,0x18,0x1f,0x07 },
    { 0x00,0x00,0x0c,0x0c,0x0e,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x30,0x3f,0x3f,0x30,0x30,0x30,0x00 },
    { 0x1c,0x1e,0x07,0x03,0x03,0x83,0xc3,0xe3,0x77,0x3e,0x1c,0x30,0x38,0x3c,0x3e,0x37,0x33,0x31,0x30,0x30,0x30,0x30 },
    { 0x0c,0x0e,0x07,0xc3,0xc3,0xc3,0xc3,0xc3,0xe7,0x7e,0x3c,0x0c,0x1c,0x38,0x30,0x30,0x30,0x30,0x30,0x39,0x1f,0x0e },
    { 0xc0,0xe0,0x70,0x38,0x1c,0x0e,0x07,0xff,0xff,0x00,0x00,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x3f,0x3f,0x03,0x03 },
    { 0x3f,0x7f,0x63,0x63,0x63,0x63,0x63,0x63,0xe3,0xc3,0x83,0x0c,0x1c,0x38,0x30,0x30,0x30,0x30,0x30,0x38,0x1f,0x0f },
    { 0xc0,0xf0,0xf8,0xdc,0xce,0xc7,0xc3,0xc3,0xc3,0x80,0x00,0x0f,0x1f,0x39,0x30,0x30,0x30,0x30,0x30,0x39,0x1f,0x0f },
    { 0x03,0x03,0x03,0x03,0x03,0x03,0xc3,0xf3,0x3f,0x0f,0x03,0x00,0x00,0x00,0x30,0x3c,0x0f,0x03,0x00,0x00,0x00,0x00 },
    { 0x00,0xbc,0xfe,0xe7,0xc3,0xc3,0xc3,0xe7,0xfe,0xbc,0x00,0x0f,0x1f,0x39,0x30,0x30,0x30,0x30,0x30,0x39,0x1f,0x0f },
    { 0x3c,0x7e,0xe7,0xc3,0xc3,0xc3,0xc3,0xc3,0xe7,0xfe,0xfc,0x00,0x00,0x30,0x30,0x30,0x38,0x1c,0x0e,0x07,0x03,0x00 },
    { 0x00,0x00,0x00,0x70,0x70,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1c,0x1c,0x1c,0x00,0x00,0x00,0x00,0x00 },
    { 0x00,0x00,0x00,0x70,0x70,0x70,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x9c,0xfc,0x7c,0x00,0x00,0x00,0x00,0x00 },
    { 0x00,0xc0,0xe0,0xf0,0x38,0x1c,0x0e,0x07,0x03,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0e,0x1c,0x38,0x30,0x00,0x00 },
    { 0x00,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x60,0x00,0x00,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x00 },
    { 0x00,0x03,0x07,0x0e,0x1c,0x38,0xf0,0xe0,0xc0,0x00,0x00,0x00,0x30,0x38,0x1c,0x0e,0x07,0x03,0x01,0x00,0x00,0x00 },
    { 0x1c,0x1e,0x07,0x03,0x83,0xc3,0xe3,0x77,0x3e,0x1c,0x00,0x00,0x00,0x00,0x00,0x37,0x37,0x00,0x00,0x00,0x00,0x00 },
    { 0xf8,0xfe,0x07,0xf3,0xfb,0x1b,0xfb,0xfb,0x07,0xfe,0xf8,0x0f,0x1f,0x18,0x33,0x37,0x36,0x37,0x37,0x36,0x03,0x01 },
    { 0x00,0x00,0xe0,0xfc,0x1f,0x1f,0xfc,0xe0,0x00,0x00,0x00,0x38,0x3f,0x07,0x06,0x06,0x06,0x06,0x07,0x3f,0x38,0x00 },
    { 0xff,0xff,0xc3,0xc3,0xc3,0xc3,0xe7,0xfe,0xbc,0x00,0x00,0x3f,0x3f,0x30,0x30,0x30,0x30,0x30,0x39,0x1f,0x0f,0x00 },
    { 0xf0,0xfc,0x0e,0x07,0x03,0x03,0x03,0x07,0x0e,0x0c,0x00,0x03,0x0f,0x1c,0x38,0x30,0x30,0x30,0x38,0x1c,0x0c,0x00 },
    { 0xff,0xff,0x03,0x03,0x03,0x03,0x07,0x0e,0xfc,0xf0,0x00,0x3f,0x3f,0x30,0x30,0x30,0x30,0x38,0x1c,0x0f,0x03,0x00 },
    { 0xff,0xff,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0x03,0x03,0x00,0x3f,0x3f,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x00 },
    { 0xff,0xff,0xc3,0xc3,0xc3,0xc3,0xc3,0xc3,0x03,0x03,0x00,0x3f,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
    { 0xf0,0xfc,0x0e,0x07,0x03,0xc3,0xc3,0xc3,0xc7,0xc6,0x00,0x03,0x0f,0x1c,0x38,0x30,0x30,0x30,0x30,0x3f,0x3f,0x00 },
    { 0xff,0xff,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xff,0xff,0x00,0x3f,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0x3f,0x00 },
    { 0x00,0x00,0x03,0x03,0xff,0xff,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x3f,0x3f,0x30,0x30,0x00,0x00,0x00 },
    { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x00,0x0e,0x1e,0x38,0x30,0x30,0x30,0x30,0x38,0x1f,0x07,0x00 },
    { 0xff,0xff,0xc0,0xe0,0xf0,0x38,0x1c,0x0e,0x07,0x03,0x00,0x3f,0x3f,0x00,0x01,0x03,0x07,0x0e,0x1c,0x38,0x30,0x00 },
    { 0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0x3f,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x00 },
    { 0xff,0xff,0x1e,0x78,0xe0,0xe0,0x78,0x1e,0xff,0xff,0x00,0x3f,0x3f,0x00,0x00,0x01,0x01,0x00,0x00,0x3f,0x3f,0x00 },
    { 0xff,0xff,0x0e,0x38,0xf0,0xc0,0x00,0x00,0xff,0xff,0x00,0x3f,0x3f,0x00,0x00,0x00,0x03,0x07,0x1c,0x3f,0x3f,0x00 },
    { 0xf0,0xfc,0x0e,0x07,0x03,0x03,0x07,0x0e,0xfc,0xf0,0x00,0x03,0x0f,0x1c,0x38,0x30,0x30,0x38,0x1c,0x0f,0x03,0x00 },
    { 0xff,0xff,0x83,0x83,0x83,0x83,0x83,0xc7,0xfe,0x7c,0x00,0x3f,0x3f,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00 },
    { 0xf0,0xfc,0x0e,0x07,0x03,0x03,0x07,0x0e,0xfc,0xf0,0x00,0x03,0x0f,0x1c,0x38,0x30,0x36,0x3e,0x1c,0x3f,0x33,0x00 },
    { 0xff,0xff,0x83,0x83,0x83,0x83,0x83,0xc7,0xfe,0x7c,0x00,0x3f,0x3f,0x01,0x01,0x03,0x07,0x0f,0x1d,0x38,0x30,0x00 },
    { 0x3c,0x7e,0xe7,0xc3,0xc3,0xc3,0xc3,0xc7,0x8e,0x0c,0x00,0x0c,0x1c,0x38,0x30,0x30,0x30,0x30,0x39,0x1f,0x0f,0x00 },
    { 0x00,0x03,0x03,0x03,0xff,0xff,0x03,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0x3f,0x00,0x00,0x00,0x00,0x00 },
    { 0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x00,0x07,0x1f,0x38,0x30,0x30,0x30,0x30,0x38,0x1f,0x07,0x00 },
    { 0x07,0x3f,0xf8,0xc0,0x00,0x00,0xc0,0xf8,0x3f,0x07,0x00,0x00,0x00,0x01,0x0f,0x3e,0x3e,0x0f,0x01,0x00,0x00,0x00 },
    { 0xff,0xff,0x00,0x00,0x80,0x80,0x00,0x00,0xff,0xff,0x00,0x3f,0x3f,0x1c,0x06,0x03,0x03,0x06,0x1c,0x3f,0x3f,0x00 },
    { 0x03,0x0f,0x1c,0x30,0xe0,0xe0,0x30,0x1c,0x0f,0x03,0x00,0x30,0x3c,0x0e,0x03,0x01,0x01,0x03,0x0e,0x3c,0x30,0x00 },
    { 0x03,0x0f,0x3c,0xf0,0xc0,0xc0,0xf0,0x3c,0x0f,0x03,0x00,0x00,0x00,0x00,0x00,0x3f,0x3f,0x00,0x00,0x00,0x00,0x00 },
    { 0x03,0x03,0x03,0x03,0xc3,0xe3,0x33,0x1f,0x0f,0x03,0x00,0x30,0x3c,0x3e,0x33,0x31,0x30,0x30,0x30,0x30,0x30,0x00 },
    { 0x00,0x00,0xff,0xff,0x03,0x03,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x3f,0x3f,0x30,0x30,0x30,0x30,0x00,0x00,0x00 },
    { 0x0e,0x1c,0x38,0x70,0xe0,0xc0,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0e,0x1c,0x18 },
    { 0x00,0x00,0x03,0x03,0x03,0x03,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x30,0x30,0x3f,0x3f,0x00,0x00,0x00 },
    { 0x60,0x70,0x38,0x1c,0x0e,0x07,0x0e,0x1c,0x38,0x70,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
    { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0 },
    { 0x00,0x00,0x00,0x00,0x3e,0x7e,0x4e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
    { 0x00,0x40,0x60,0x60,0x60,0x60,0x60,0x60,0xe0,0xc0,0x00,0x1c,0x3e,0x33,0x33,0x33,0x33,0x33,0x33,0x3f,0x3f,0x00 },
    { 0xff,0xff,0xc0,0x60,0x60,0x60,0x60,0xe0,0xc0,0x80,0x00,0x3f,0x3f,0x30,0x30,0x30,0x30,0x30,0x38,0x1f,0x0f,0x00 },
    { 0x80,0xc0,0xe0,0x60,0x60,0x60,0x60,0x60,0xc0,0x80,0x00,0x0f,0x1f,0x38,0x30,0x30,0x30,0x30,0x30,0x18,0x08,0x00 },
    { 0x80,0xc0,0xe0,0x60,0x60,0x60,0xe0,0xc0,0xff,0xff,0x00,0x0f,0x1f,0x38,0x30,0x30,0x30,0x30,0x30,0x3f,0x3f,0x00 },
    { 0x80,0xc0,0xe0,0x60,0x60,0x60,0x60,0x60,0xc0,0x80,0x00,0x0f,0x1f,0x3b,0x33,0x33,0x33,0x33,0x33,0x13,0x01,0x00 },
    { 0xc0,0xc0,0xfc,0xfe,0xc7,0xc3,0xc3,0x03,0x00,0x00,0x00,0x00,0x00,0x3f,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
    { 0x80,0xc0,0xe0,0x60,0x60,0x60,0x60,0x60,0xe0,0xe0,0x00,0x03,0xc7,0xce,0xcc,0xcc,0xcc,0xcc,0xe6,0x7f,0x3f,0x00 },
    { 0xff,0xff,0xc0,0x60,0x60,0x60,0xe0,0xc0,0x80,0x00,0x00,0x3f,0x3f,0x00,0x00,0x00,0x00,0x00,0x3f,0x3f,0x00,0x00 },
    { 0x00,0x00,0x00,0x60,0xec,0xec,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x3f,0x3f,0x30,0x30,0x00,0x00,0x00 },
    { 0x00,0x00,0x00,0x00,0x00,0x60,0xec,0xec,0x00,0x00,0x00,0x00,0x00,0x60,0xe0,0xc0,0xc0,0xff,0x7f,0x00,0x00,0x00 },
    { 0x00,0xff,0xff,0x00,0x80,0xc0,0xe0,0x60,0x00,0x00,0x00,0x00,0x3f,0x3f,0x03,0x07,0x0f,0x1c,0x38,0x30,0x00,0x00 },
    { 0x00,0x00,0x00,0x03,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x3f,0x3f,0x30,0x30,0x00,0x00,0x00 },
    { 0xe0,0xc0,0xe0,0xe0,0xc0,0xc0,0xe0,0xe0,0xc0,0x80,0x00,0x3f,0x3f,0x00,0x00,0x3f,0x3f,0x00,0x00,0x3f,0x3f,0x00 },
    { 0x00,0xe0,0xe0,0x60,0x60,0x60,0x60,0xe0,0xc0,0x80,0x00,0x00,0x3f,0x3f,0x00,0x00,0x00,0x00,0x00,0x3f,0x3f,0x00 },
    { 0x80,0xc0,0xe0,0x60,0x60,0x60,0x60,0xe0,0xc0,0x80,0x00,0x0f,0x1f,0x38,0x30,0x30,0x30,0x30,0x38,0x1f,0x0f,0x00 },
    { 0xe0,0xe0,0x60,0x60,0x60,0x60,0x60,0xe0,0xc0,0x80,0x00,0xff,0xff,0x0c,0x18,0x18,0x18,0x18,0x1c,0x0f,0x07,0x00 },
    { 0x80,0xc0,0xe0,0x60,0x60,0x60,0x60,0x60,0xe0,0xe0,0x00,0x07,0x0f,0x1c,0x18,0x18,0x18,0x18,0x0c,0xff,0xff,0x00 },
    { 0x00,0xe0,0xe0,0xc0,0x60,0x60,0x60,0x60,0xe0,0xc0,0x00,0x00,0x3f,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
    { 0xc0,0xe0,0x60,0x60,0x60,0x60,0x60,0x40,0x00,0x00,0x00,0x11,0x33,0x33,0x33,0x33,0x33,0x3f,0x1e,0x00,0x00,0x00 },
    { 0x60,0x60,0xfe,0xfe,0x60,0x60,0x60,0x00,0x00,0x00,0x00,0x00,0x00,0x1f,0x3f,0x30,0x30,0x30,0x30,0x00,0x00,0x00 },
    { 0xe0,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0xe0,0xe0,0x00,0x0f,0x1f,0x38,0x30,0x30,0x30,0x30,0x18,0x3f,0x3f,0x00 },
    { 0x60,0xe0,0x80,0x00,0x00,0x00,0x00,0x80,0xe0,0x60,0x00,0x00,0x01,0x07,0x1e,0x38,0x38,0x1e,0x07,0x01,0x00,0x00 },
    { 0xe0,0xe0,0x00,0x00,0xe0,0xe0,0x00,0x00,0xe0,0xe0,0x00,0x07,0x1f,0x38,0x1c,0x0f,0x0f,0x1c,0x38,0x1f,0x07,0x00 },
    { 0x60,0xe0,0xc0,0x80,0x00,0x80,0xc0,0xe0,0x60,0x00,0x00,0x30,0x38,0x1d,0x0f,0x07,0x0f,0x1d,0x38,0x30,0x00,0x00 },
    { 0x00,0x60,0xe0,0x80,0x00,0x00,0x80,0xe0,0x60,0x00,0x00,0x00,0x00,0x81,0xe7,0x7e,0x1e,0x07,0x01,0x00,0x00,0x00 },
    { 0x60,0x60,0x60,0x60,0x60,0xe0,0xe0,0x60,0x20,0x00,0x00,0x30,0x38,0x3c,0x36,0x33,0x31,0x30,0x30,0x30,0x00,0x00 },
    { 0x00,0x80,0xc0,0xfc,0x7e,0x07,0x03,0x03,0x03,0x00,0x00,0x00,0x00,0x01,0x1f,0x3f,0x70,0x60,0x60,0x60,0x00,0x00 },
    { 0x00,0x00,0x00,0x00,0xff,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0x3f,0x00,0x00,0x00,0x00,0x00 },
    { 0x00,0x03,0x03,0x03,0x07,0x7e,0xfc,0xc0,0x80,0x00,0x00,0x00,0x60,0x60,0x60,0x70,0x3f,0x1f,0x01,0x00,0x00,0x00 },
    { 0x10,0x18,0x0c,0x04,0x0c,0x18,0x10,0x18,0x0c,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
    { 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x00 }
};

static signed char speed[]={
    1,2,3,3,3,2,1,0,-1,-2,-2,-2,-1,0,0,1,
};

#if LCD_WIDTH > LCD_HEIGHT /* landscape LCD  */

#define TABLE_SIZE    LCD_HEIGHT
#define RADIUS_MINUTE (3*LCD_HEIGHT/8)
#define RADIUS_HOUR   (LCD_HEIGHT/4)

#else /* portrait (or square) LCD */

#define TABLE_SIZE LCD_WIDTH
#define RADIUS_MINUTE (3*LCD_WIDTH/8)
#define RADIUS_HOUR   (LCD_WIDTH/4)

#endif /* LCD orientation */

#define RADIUS_X   ((LCD_WIDTH-LETTER_WIDTH)/2)
#define RADIUS_Y   ((LCD_HEIGHT-LETTER_HEIGHT)/2)

#define PHASE_STEP (0xffffffff/TABLE_SIZE)
#define PHASE_FRAC (0xffffffff%TABLE_SIZE)
#define DIV_X      (0x7ffffffe/RADIUS_X+1)
#define DIV_Y      (0x7ffffffe/RADIUS_Y+1)

static int xtable[TABLE_SIZE];
static int ytable[TABLE_SIZE];

static void init_tables(void)
{
    int i;
    int pfrac;
    unsigned long phase;
    long sin;

    phase = pfrac = 0;

    for (i = 0; i < TABLE_SIZE; i++) {
         sin = fp_sincos(phase, NULL);
         xtable[i] = RADIUS_X + sin / DIV_X;
         ytable[i] = RADIUS_Y + sin / DIV_Y;

         phase += PHASE_STEP;
         pfrac += PHASE_FRAC;
         if (pfrac >= TABLE_SIZE) {
             pfrac -= TABLE_SIZE;
             phase++;
         }
    }
}

enum {
  NUM_XSANKE,
  NUM_YSANKE,
  NUM_XADD,
  NUM_YADD,
  NUM_XDIST,
  NUM_YDIST,

  NUM_LAST
};

struct counter {
  char *what;
  int num;
};

struct counter values[]={
  {"xsanke", 1},
  {"ysanke", 1},
  {"xadd", 1},
  {"yadd", 2},
  {"xdist", -4},
  {"ydist", -6},
};

#if CONFIG_RTC

#define CLOCK_STEP (0xffffffff/60)
#define CLOCK_FRAC (0xffffffff%60)

#define DIV_MY (0x7ffffffe/RADIUS_MINUTE+1)
#define DIV_HY (0x7ffffffe/RADIUS_HOUR+1)

#if LCD_WIDTH == 112 && LCD_HEIGHT == 64 /* Archos LCD: non-square pixels */
#define DIV_MX (0x7ffffffe/(5*RADIUS_MINUTE/4)+1)
#define DIV_HX (0x7ffffffe/(5*RADIUS_HOUR/4)+1)
#else  /* Square pixels */
#define DIV_MX DIV_MY
#define DIV_HX DIV_HY
#endif

static int xminute[60], yminute[60];
static int xhour[60], yhour[60];

static void init_clock(void)
{
    int i;
    int pfrac;
    unsigned long phase;
    long sin, cos;

    phase = pfrac = 0;

    for (i = 0; i < 60; i++) {
         sin = fp_sincos(phase, &cos);
         xminute[i] = LCD_WIDTH/2 + sin / DIV_MX;
         yminute[i] = LCD_HEIGHT/2 - cos / DIV_MY;
         xhour[i] = LCD_WIDTH/2 + sin / DIV_HX;
         yhour[i] = LCD_HEIGHT/2 - cos / DIV_HY;

         phase += CLOCK_STEP;
         pfrac += CLOCK_FRAC;
         if (pfrac >= 60) {
             pfrac -= 60;
             phase++;
         }
    }
}

static void addclock(void)
{
    int i;
    int hour;
    int minute;

    struct tm* current_time = rb->get_time();
    hour = current_time->tm_hour;
    minute = current_time->tm_min;

    rb->lcd_drawline(LCD_WIDTH/2, LCD_HEIGHT/2,
                     xminute[minute], yminute[minute]);

    hour = (hour % 12) * 5 + minute / 12;

    rb->lcd_drawline(LCD_WIDTH/2, LCD_HEIGHT/2, xhour[hour], yhour[hour]);

    /* draw a circle */
    for(i = 1; i < 60; i += 3) 
        rb->lcd_drawline(xminute[i], yminute[i],
                         xminute[(i+1)%60], yminute[(i+1)%60]);
}
#endif /* CONFIG_RTC */

#if LCD_DEPTH > 1
static const unsigned face_colors[] =
{
#ifdef HAVE_LCD_COLOR
    LCD_BLACK, LCD_RGBPACK(0, 0, 255), LCD_RGBPACK(255, 0, 0)
#else
    LCD_BLACK, LCD_LIGHTGRAY, LCD_DARKGRAY
#endif
};
#endif

static int scrollit(void)
{
    int b;
    unsigned int y=100;
    unsigned int yy;
    int x = LCD_WIDTH;
    int xx;
    unsigned int i;
    unsigned int textpos=0;

    char* rock="Rockbox! Pure pleasure. Pure fun. Oooh. What fun! ;-) ";
    unsigned int rocklen = rb->strlen(rock);
    int letter;
#if LCD_DEPTH > 1
    unsigned prev_color;
#endif

    rb->lcd_clear_display();
    while(1)
    {
        b = rb->button_get_w_tmo(HZ/10);
        switch(b)
        {
#ifdef BOUNCE_RC_QUIT
            case BOUNCE_RC_QUIT :
#endif
            case BOUNCE_QUIT :
                return 0;
            case BOUNCE_MODE :
                return 1;
            default:
                if ( rb->default_event_handler(b) == SYS_USB_CONNECTED )
                    return -1;
        }
        rb->lcd_clear_display();
#if CONFIG_RTC
        addclock();
#endif

#if LCD_DEPTH > 1
        prev_color = rb->lcd_get_foreground();
#endif

        for(i=0, yy=y, xx=x; xx < LCD_WIDTH; i++) {
            letter = rock[(i+textpos) % rocklen ];
#if LCD_DEPTH > 1
            rb->lcd_set_foreground(face_colors[letter % 3]);
#endif
            rb->lcd_mono_bitmap(char_gen_12x16[letter-0x20],
                                xx, ytable[yy % TABLE_SIZE],
                                LETTER_WIDTH, LETTER_HEIGHT);
            yy += YADD;
            xx += LETTER_WIDTH;
        }
#if LCD_DEPTH > 1
        rb->lcd_set_foreground(prev_color);
#endif
        rb->lcd_update();

        x-= XSPEED;

        if(x < -LETTER_WIDTH) {
            x += LETTER_WIDTH;
            y += YADD;
            textpos++;
        }

        y+=YSPEED;
    }
}

static int loopit(void)
{
    int b;
    unsigned int y=100;
    unsigned int x=100;
    unsigned int yy,xx;
    unsigned int i;
    unsigned int ysanke=0;
    unsigned int xsanke=0;

    char* rock="ROCKbox";
    unsigned int rocklen = rb->strlen(rock);

    int show=0;
    int timeout=0;

    rb->lcd_clear_display();
    while(1)
    {
        b = rb->button_get_w_tmo(HZ/10);
        if ( b == BOUNCE_QUIT )
            return 0;

        if ( b == BOUNCE_MODE )
            return 1;

        if ( rb->default_event_handler(b) == SYS_USB_CONNECTED )
            return -1;

        if ( b != BUTTON_NONE )
            timeout=20;

        y+= speed[ysanke&15] + values[NUM_YADD].num;
        x+= speed[xsanke&15] + values[NUM_XADD].num;

        rb->lcd_clear_display();
#if CONFIG_RTC
        addclock();
#endif
        if(timeout) {
            switch(b) {
                case BOUNCE_LEFT:
                case BOUNCE_LEFT|BUTTON_REPEAT:
                  values[show].num--;
                  break;
                case BOUNCE_RIGHT:
                case BOUNCE_RIGHT|BUTTON_REPEAT:
                  values[show].num++;
                  break;
                case BOUNCE_UP:
                case BOUNCE_UP|BUTTON_REPEAT:
                  if(++show == NUM_LAST)
                      show=0;
                  break;
                case BOUNCE_DOWN:
                case BOUNCE_DOWN|BUTTON_REPEAT:
                  if(--show < 0)
                      show=NUM_LAST-1;
                  break;
            }
            rb->lcd_putsxyf(0, LCD_HEIGHT -  8, "%s: %d",
                         values[show].what, values[show].num);
            timeout--;
        }
        for(i=0, yy=y, xx=x;
            i<rocklen;
            i++, yy+=values[NUM_YDIST].num, xx+=values[NUM_XDIST].num)
            rb->lcd_mono_bitmap(char_gen_12x16[rock[i]-0x20],
                                xtable[xx % TABLE_SIZE],
                                ytable[yy % TABLE_SIZE],
                                LETTER_WIDTH, LETTER_HEIGHT);
        rb->lcd_update();

        ysanke+= values[NUM_YSANKE].num;
        xsanke+= values[NUM_XSANKE].num;
    }
}


enum plugin_status plugin_start(const void* parameter)
{
    int w, h;
    char *off = "[Off] to stop";

    (void)(parameter);

    rb->lcd_setfont(FONT_SYSFIXED);
    rb->lcd_clear_display();

    /* Get horizontel centering for text */
    rb->lcd_getstringsize((unsigned char *)SS_TITLE, &w, &h);
    rb->lcd_putsxy((LCD_WIDTH/2) - w / 2, (LCD_HEIGHT/2) - h / 2,
                   (unsigned char *)SS_TITLE);

    /* Get horizontel centering for text */
    rb->lcd_getstringsize((unsigned char *)off, &w, &h);
    rb->lcd_putsxy((LCD_WIDTH/2) - w / 2, LCD_HEIGHT - 2 * h,
                    (unsigned char *)off);

    rb->lcd_update();
    rb->sleep(HZ);
    rb->lcd_set_drawmode(DRMODE_FG);
    init_tables();
#if CONFIG_RTC
    init_clock();
#endif

    do {
        h = loopit();
        if (h > 0)
            h = scrollit();
    } while(h > 0);

    rb->lcd_set_drawmode(DRMODE_SOLID);
    rb->lcd_setfont(FONT_UI);

    return (h == 0) ? PLUGIN_OK : PLUGIN_USB_CONNECTED;
}
