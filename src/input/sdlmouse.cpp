#include "input/sdlmouse.h"
#include <iostream>

SDLMouse::SDLMouse()
{
    // map mouse buttons
    mouseButtonCodes[ Mouse::MOUSEBUTTON_LEFT ] = SDL_BUTTON(1);
    mouseButtonCodes[ Mouse::MOUSEBUTTON_MIDDLE ] = SDL_BUTTON(2);
    mouseButtonCodes[ Mouse::MOUSEBUTTON_RIGHT ] = SDL_BUTTON(3);

    // initialize the states
    mouseState = SDL_GetMouseState( &mouseX, &mouseY );
    mouseLastX = mouseX;
    mouseLastY = mouseY;

    mouseStateInLastFrame = 0;
}

SDLMouse::~SDLMouse()
{
}

int SDLMouse::getMouseX()
{
    if( mouseMode == Mouse::MOUSE_NORMAL || mouseMode == Mouse::MOUSE_RELATIVE )
    {
        return mouseX;
    }
    else if( mouseMode == Mouse::MOUSE_BOUND )
    {
        return mouseX-mouseLastX;
    }

    return 0;
}

int SDLMouse::getMouseY()
{
    if( mouseMode == Mouse::MOUSE_NORMAL || mouseMode == Mouse::MOUSE_RELATIVE )
    {
        return mouseY;
    }
    else if( mouseMode == Mouse::MOUSE_BOUND )
    {
         return mouseY-mouseLastY;
    }

    return 0;
}

bool SDLMouse::mouseButtonIsDown( MOUSEBUTTONS mouseButton ) const
{
    if( mouseState & mouseButtonCodes[mouseButton] )
        return true;

    return false;
}

bool SDLMouse::mouseButtonWasDown( MOUSEBUTTONS mouseButton ) const
{
    if( mouseStateInLastFrame & mouseButtonCodes[mouseButton] )
        return true;

    return false;
}

bool SDLMouse::mouseButtonPressedInThisFrame( MOUSEBUTTONS mouseButton ) const
{
    if( (mouseStateInLastFrame & mouseButtonCodes[mouseButton]) == false
         && (mouseState & mouseButtonCodes[mouseButton]) == true )
    {
        return true;
    }

    return false;
}

bool SDLMouse::mouseButtonReleasedInThisFrame( MOUSEBUTTONS mouseButton ) const
{
    if( (mouseStateInLastFrame & mouseButtonCodes[mouseButton]) == true
         && (mouseState & mouseButtonCodes[mouseButton]) == false )
    {
        return true;
    }

    return false;
}

void SDLMouse::updateMouse()
{
    mouseStateInLastFrame = mouseState;

    if( mouseMode == Mouse::MOUSE_RELATIVE || mouseState == Mouse::MOUSE_NORMAL)
    {
        mouseState = SDL_GetRelativeMouseState( &mouseX, &mouseY );
        mouseLastX = mouseX;
        mouseLastY = mouseY;
    }
    else if( mouseMode == Mouse::MOUSE_BOUND )
    {
        mouseState = SDL_GetMouseState( &mouseX, &mouseY );

        SDL_WarpMouse( mouseBindPointX, mouseBindPointY );
        mouseLastX = mouseBindPointX;
        mouseLastY = mouseBindPointY;
    }
}

void SDLMouse::showMousePointer()
{
    SDL_ShowCursor( SDL_ENABLE );
}

void SDLMouse::hideMousePointer()
{
    SDL_ShowCursor( SDL_DISABLE );
}

void SDLMouse::moveMouse( int x, int y )
{
    SDL_WarpMouse( x, y );
}
