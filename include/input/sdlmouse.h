#ifndef SDLMOUSE_H
#define SDLMOUSE_H

#include "input/mouse.h"

#include <SDL/SDL.h>
/**
 * @file input/sdlmouse.h
 * @author Marko Silokunnas
 */
class SDLMouse : public Mouse
{
    public:
        SDLMouse();
        virtual ~SDLMouse();

        virtual inline int getMouseY() const { return currentMouseX; }
        virtual inline int getMouseX() const { return currentMouseY; }

        virtual int getMouseDeltaX() const;
        virtual int getMouseDeltaY() const;

        virtual bool mouseButtonIsDown( MOUSEBUTTONS mouseButton ) const;

        virtual bool mouseButtonWasDown( MOUSEBUTTONS mouseButton ) const;

        virtual bool mouseButtonPressedInThisFrame(
                                            MOUSEBUTTONS mousebutton ) const;

        virtual bool mouseButtonReleasedInThisFrame(
                                            MOUSEBUTTONS mouseButton ) const;

        virtual void updateMouse();

        virtual void showMousePointer();

        virtual void hideMousePointer();
    protected:

    private:
        int mouseButtonCodes[numberOfMouseButtons];

        /**
         * Current state of the mouse buttons. Contains info on what mouse
         * buttons are currently down. Values stored in the mouseButtonCodes
         * array will be used to mask this value to determine what buttons are
         * down.
         */
        Uint8 mouseState;

        /**
         * Mouse state in the last frame.
         */
        Uint8 mouseStateInLastFrame;

};

#endif // SDLMOUSE_H
