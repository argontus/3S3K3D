#ifndef SDLKEYBOARD_H
#define SDLKEYBOARD_H


#include <input/keyboard.h>
#include <SDL/SDL.h>

#include <vector>

/**
 * @file input/sdlkeyboard.h
 * @author Marko Silokunnas
 *
 * This class is an implementation of the 'Keyboard' pure virtual class for SDL.
 */
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

        /**
         * Current keyboard state. In other words, what buttons are down.
         */
        Uint8* keyboardState;

        /**
         * State of the keyboard in previous frame.
         */
        Uint8* keyboardStateInLastFrame;

        /**
         * Keycode table.
         */
        int keycodes[numberOfKeys];

};

#endif // SDLKEYBOARD_H
