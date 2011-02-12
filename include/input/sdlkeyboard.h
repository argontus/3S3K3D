#ifndef SDLKEYBOARD_H
#define SDLKEYBOARD_H


#include <input/keyboard.h>
#include <SDL/SDL.h>

#include <vector>

class SDLKeyboard : public Keyboard
{
    public:

        SDLKeyboard();
        virtual ~SDLKeyboard();

        virtual bool keyIsDown( KEYS key );
        virtual bool keyWasDown( KEYS key );

        virtual bool keyWasPressedInThisFrame( KEYS key );
        virtual bool keyWasReleasedInThisFrame( KEYS key );

        virtual bool updateKeyboardState();

    private:
        /**
         * Number of keys on the keyboard. Set by SDL.
         */
        int keysOnKeyboard;

        Uint8* keyboardState;
        Uint8* keyboardStateInLastFrame;

        /**
         * Keycode table.
         */
        int keycodes[numberOfKeys];

};

#endif // SDLKEYBOARD_H
