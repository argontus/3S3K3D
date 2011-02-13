#include "input/sdlkeyboard.h"

#include <iostream>

SDLKeyboard::SDLKeyboard()
{
    keyboardState = SDL_GetKeyState( &keysOnKeyboard );

    keyboardStateInLastFrame = new Uint8[keysOnKeyboard];
    ::memset( keyboardStateInLastFrame, 0, sizeof(Uint8)*keysOnKeyboard );

    keycodes[KEY_A]     = SDLK_a;
    keycodes[KEY_B]     = SDLK_b;
    keycodes[KEY_C]     = SDLK_c;
    keycodes[KEY_D]     = SDLK_d;
    keycodes[KEY_E]     = SDLK_e;
    keycodes[KEY_F]     = SDLK_f;
    keycodes[KEY_G]     = SDLK_g;
    keycodes[KEY_H]     = SDLK_h;
    keycodes[KEY_I]     = SDLK_i;
    keycodes[KEY_J]     = SDLK_j;
    keycodes[KEY_K]     = SDLK_k;
    keycodes[KEY_L]     = SDLK_l;
    keycodes[KEY_M]     = SDLK_m;
    keycodes[KEY_N]     = SDLK_n;
    keycodes[KEY_O]     = SDLK_o;
    keycodes[KEY_P]     = SDLK_p;
    keycodes[KEY_Q]     = SDLK_q;
    keycodes[KEY_R]     = SDLK_r;
    keycodes[KEY_S]     = SDLK_s;
    keycodes[KEY_T]     = SDLK_t;
    keycodes[KEY_U]     = SDLK_u;
    keycodes[KEY_W]     = SDLK_w;
    keycodes[KEY_V]     = SDLK_v;
    keycodes[KEY_X]     = SDLK_x;
    keycodes[KEY_Y]     = SDLK_y;
    keycodes[KEY_Z]     = SDLK_z;
    keycodes[KEY_0]     = SDLK_0;
    keycodes[KEY_1]     = SDLK_1;
    keycodes[KEY_2]     = SDLK_2;
    keycodes[KEY_3]     = SDLK_3;
    keycodes[KEY_4]     = SDLK_4;
    keycodes[KEY_5]     = SDLK_5;
    keycodes[KEY_6]     = SDLK_6;
    keycodes[KEY_7]     = SDLK_7;
    keycodes[KEY_8]     = SDLK_8;
    keycodes[KEY_9]     = SDLK_9;
    keycodes[KEY_F1]    = SDLK_F1;
    keycodes[KEY_F2]    = SDLK_F2;
    keycodes[KEY_F3]    = SDLK_F3;
    keycodes[KEY_F4]    = SDLK_F4;
    keycodes[KEY_F5]    = SDLK_F5;
    keycodes[KEY_F6]    = SDLK_F6;
    keycodes[KEY_F7]    = SDLK_F7;
    keycodes[KEY_F8]    = SDLK_F8;
    keycodes[KEY_F9]    = SDLK_F9;
    keycodes[KEY_ESCAPE] = SDLK_ESCAPE;
    keycodes[KEY_ENTER]  = SDLK_RETURN;
    keycodes[KEY_SPACE]  = SDLK_SPACE;
}

SDLKeyboard::~SDLKeyboard()
{
    /**
     * NOTE: keyboardState will be freed by SDL, but keyboardStateInLastFrame
     *       has to be freed manually.
     */
    delete keyboardStateInLastFrame;
    keyboardStateInLastFrame = NULL;
}


bool SDLKeyboard::keyIsDown( KEYS key )
{
    if( keyboardState[keycodes[key]] )
        return true;

    return false;
}

bool SDLKeyboard::keyWasDown( KEYS key )
{
    if( keyboardStateInLastFrame[keycodes[key]] )
        return true;

    return false;
}

bool SDLKeyboard::keyWasPressedInThisFrame( KEYS key )
{
    if( keyboardState[keycodes[key]] == true
        && keyboardStateInLastFrame[keycodes[key]] == false )
    {
        return true;
    }

    return false;
}

bool SDLKeyboard::keyWasReleasedInThisFrame( KEYS key )
{
    if( keyboardState[keycodes[key]] == false
        && keyboardStateInLastFrame[keycodes[key]] == true )
    {
        return true;
    }

    return false;
}

void SDLKeyboard::updateKeyboardState() {
    ::memcpy(  keyboardStateInLastFrame,
                keyboardState,
                sizeof(Uint8)*keysOnKeyboard );
}
