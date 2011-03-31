#ifndef KEYBOARD_H
#define KEYBOARD_H

/**
 * @file input/keyboard.h
 * @author Marko Silokunnas
 *
 */

 #include <vector>

class Keyboard
{
    public:

        /**
         * Enum for keys. Contains all keys supported by this input system.
         * Used as an index in inheriting classes.
         */
        enum KEYS {
            KEY_A,
            KEY_B,
            KEY_C,
            KEY_D,
            KEY_E,
            KEY_F,
            KEY_G,
            KEY_H,
            KEY_I,
            KEY_J,
            KEY_K,
            KEY_L,
            KEY_M,
            KEY_N,
            KEY_O,
            KEY_P,
            KEY_Q,
            KEY_R,
            KEY_S,
            KEY_T,
            KEY_U,
            KEY_V,
            KEY_W,
            KEY_X,
            KEY_Y,
            KEY_Z,
            KEY_0,
            KEY_1,
            KEY_2,
            KEY_3,
            KEY_4,
            KEY_5,
            KEY_6,
            KEY_7,
            KEY_8,
            KEY_9,
            KEY_F1,
            KEY_F2,
            KEY_F3,
            KEY_F4,
            KEY_F5,
            KEY_F6,
            KEY_F7,
            KEY_F8,
            KEY_F9,
            KEY_F10,
            KEY_F11,
            KEY_F12,
            KEY_SPACE,
            KEY_ENTER,
            KEY_ESCAPE,
            KEY_LEFT,
            KEY_RIGHT,
            KEY_UP,
            KEY_DOWN,
            NUMBER_OF_KEYS
        };

        Keyboard();
        virtual ~Keyboard();

        /**
         * Tells whether or not a key is currently down.
         *
         * @param key which key's state we want
         * @return bool returns true if the key is down and false if it isn't.
         */
        virtual bool keyIsDown( KEYS key ) = 0;

        /**
         * Tells whether or not a key was down in the last frame.
         *
         * @param key which key's state we want
         * @return bool returns true if the key is down and false if it isn't.
         */
        virtual bool keyWasDown( KEYS key ) = 0;

        /**
         * Tells whether or not a key was pressed in this frame.
         *
         * @param key which key's state we want
         * @return bool returns true if the key is down and false if it isn't.
         */
        virtual bool keyWasPressedInThisFrame( KEYS key ) = 0;


        /**
         * Tells whether or not a key was released in this frame.
         *
         * @param key which key's state we want
         * @return bool returns true if the key is down and false if it isn't.
         */
        virtual bool keyWasReleasedInThisFrame( KEYS key ) = 0;

        /**
         * Saves the current state of the keyboard as it's last state.
         * Should be called once in a frame.
         */
        virtual void updateKeyboardState() = 0;

    protected:
        int keycodes[NUMBER_OF_KEYS];

        int* keyboardState;
        int* keyboardStateInLastFrame;


    private:

};

#endif // KEYBOARD_H
