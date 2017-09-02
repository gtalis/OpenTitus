/*   
 * Copyright (C) 2008 - 2012 The OpenTitus team
 *
 * Authors:
 * Eirik Stople
 *
 * "Titus the Fox: To Marrakech and Back" (1992) and
 * "Lagaf': Les Aventures de Moktar - Vol 1: La Zoubida" (1991)
 * was developed by, and is probably copyrighted by Titus Software,
 * which, according to Wikipedia, stopped buisness in 2005.
 *
 * OpenTitus is not affiliated with Titus Software.
 *
 * OpenTitus is  free software; you can redistribute  it and/or modify
 * it under the  terms of the GNU General  Public License as published
 * by the Free  Software Foundation; either version 3  of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT  ANY  WARRANTY;  without   even  the  implied  warranty  of
 * MERCHANTABILITY or  FITNESS FOR A PARTICULAR PURPOSE.   See the GNU
 * General Public License for more details.
 */

/* keyboard.h
 * Keyboard functions
 */

#ifndef KEYBOARD_H
#define KEYBOARD_H

int waitforbutton();

enum {
    JOYUP,
    JOYDOWN,
    JOYLEFT,
    JOYRIGHT,
    JOY_BUTTON_A,
    JOY_BUTTON_B,
    JOY_BUTTON_X,
    JOY_BUTTON_Y,
    JOY_BUTTON_START,
    JOY_BUTTON_SELECT,
};

int joy_axis(SDL_Event event);
int joy_button(SDL_Event event);


uint8_t *getJoyState(void);
int updateJoyState(SDL_Event event);
void initJoyState(void);

#endif

