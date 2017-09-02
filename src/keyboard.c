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

/* keyboard.c
 * Keyboard functions
 */

#include "SDL/SDL.h"
#include "keyboard.h"
#include "globals.h"
#include "common.h"

//Probably not the best way, but it works...
#define HAVE_CONFIG_H 1

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef AUDIO_ENABLED
#include "audio.h"
#endif

int waitforbutton() {
    SDL_Event event;
    int waiting = 1;
    while (waiting > 0)
    {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                waiting = -1;

            if (event.type == SDL_KEYDOWN || event.type == SDL_JOYBUTTONDOWN) {
                if (event.key.keysym.sym == KEY_RETURN || event.key.keysym.sym == KEY_ENTER || event.key.keysym.sym == KEY_SPACE || event.jbutton.button == 0)
                    waiting = 0;

                if (event.key.keysym.sym == SDLK_ESCAPE)
                    waiting = -1;

#ifdef AUDIO_ENABLED
                if (event.key.keysym.sym == KEY_MUSIC) {
					AUDIOMODE++;
					if (AUDIOMODE > 1) {
						AUDIOMODE = 0;
					}
					if (AUDIOMODE == 1) {
						startmusic();
					}
                }
#endif
            }
        }
		titus_sleep();
#ifdef AUDIO_MIKMOD_SINGLETHREAD
        checkmodule();
#endif

#ifdef AUDIO_SDL_MIXER
        checkaudio();
#endif

    }
    return (waiting);
}

int joy_axis(SDL_Event event)
{
    int axis;

    printf("axis: %d, value: %d\n", event.jaxis.axis, event.jaxis.value);

    axis = -1;

    if (event.jaxis.axis == 0)
    {
        if (event.jaxis.value <= -32768) {
            printf("LEFT\n");
           return JOYLEFT;
        }

        else if (event.jaxis.value >= 32767){
            printf("RIGHT\n");
            return JOYRIGHT;
        }
    }
    else if (event.jaxis.axis == 1)
    {
        if (event.jaxis.value <= -32768) {
            printf("UP\n");
           return JOYUP;
        }

        else if (event.jaxis.value >= 32767){
            printf("DOWN\n");
            return JOYDOWN;
        }
    }

    return -1;
}


int joy_button(SDL_Event event)
{
    int button = -1;

    if (event.jbutton.state == SDL_PRESSED) {
        button = event.jbutton.button;
    }

    printf("=> button = %d, state %d\n", event.jbutton.button, event.jbutton.state);
    return button;
}

#define NUM_OF_JOY_BUTTONS_AXIS 20

static uint8 joy_state[NUM_OF_JOY_BUTTONS_AXIS];

enum {
    SDL_BUTTON_A,
    SDL_BUTTON_B,
    SDL_BUTTON_X,
    SDL_BUTTON_Y,
    SDL_BUTTON_UNKNOWN_1,
    SDL_BUTTON_UNKNOWN_2,
    SDL_BUTTON_UNKNOWN_3,
    SDL_BUTTON_START,
};


static int joyButtonFromSDLButton(int sdl_button)
{
    switch (sdl_button)
    {
        SDL_BUTTON_A:
            return JOY_BUTTON_A;
            break;

        SDL_BUTTON_B:
            return JOY_BUTTON_B;
            break;

        SDL_BUTTON_X:
            return JOY_BUTTON_X;
            break;

        SDL_BUTTON_Y:
            return JOY_BUTTON_Y;
            break;
        SDL_BUTTON_START:
            return JOY_BUTTON_START;
            break;

        default:
            return (NUM_OF_JOY_BUTTONS_AXIS-1);
    }
}


uint8_t * getJoyState(void)
{
    return joy_state;
}

int updateJoyState(SDL_Event event)
{
    int sdl_button;
    int joy_button;
    int i;

    if (event.jaxis.axis == 0)
    {
        if (event.jaxis.value <= -32768) {
            printf("LEFT\n");
            joy_state[JOYLEFT] = 1;
        }

        else if (event.jaxis.value >= 32767){
            printf("RIGHT\n");
            joy_state[JOYRIGHT] = 1;
        }
        else if (event.jaxis.value == 0) {
            printf("AXIS LEFT-RIGHT = 0\n");
            joy_state[JOYLEFT] = 0;
            joy_state[JOYRIGHT] = 0;
        }
    }

    if (event.jaxis.axis == 1)
    {
        if (event.jaxis.value <= -32768) {
            joy_state[JOYUP] = 1;
            printf("UP\n");
        }

        else if (event.jaxis.value >= 32767){
            joy_state[JOYDOWN] = 1;
            printf("DOWN\n");
        }

        else if (event.jaxis.value == 0) {
            printf("AXIS UP/DOWN = 0\n");
            joy_state[JOYUP] = 0;
            joy_state[JOYDOWN] = 0;     
        }
    }

    if (event.jbutton.state == SDL_PRESSED) {
        sdl_button = event.jbutton.button;
        joy_button = joyButtonFromSDLButton(sdl_button);
        printf("Button %d ON\n", joy_button);
        joy_state[joy_button] = 1;
    } else {
        printf("All buttons OFF\n");
        for (i=JOY_BUTTON_A;i<JOY_BUTTON_SELECT;i++)
            joy_state[i] = 0;
    }

}

void initJoyState()
{
    int i;
    for (i=0;i<NUM_OF_JOY_BUTTONS_AXIS;i++)
        joy_state[i] = 0;
}


// BUTTONS
// START = 7
// B = 1
// X = 2
// Y = 3
// A = 0



