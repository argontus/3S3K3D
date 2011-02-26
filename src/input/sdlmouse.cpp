#include "input/sdlmouse.h"
#include <iostream>

SDLMouse::SDLMouse()
{
    // map mouse buttons
    mouseButtonCodes[ Mouse::MOUSEBUTTON_LEFT ] = SDL_BUTTON(1);
    mouseButtonCodes[ Mouse::MOUSEBUTTON_MIDDLE ] = SDL_BUTTON(2);
    mouseButtonCodes[ Mouse::MOUSEBUTTON_RIGHT ] = SDL_BUTTON(3);

    // initialize the states
    mouseState = SDL_GetMouseState( &currentMouseX, &currentMouseY );
    mouseStateInLastFrame = 0;
}

SDLMouse::~SDLMouse()
{
}

int SDLMouse::getMouseDeltaX() const
{
    return currentMouseX-previousMouseX;
}

int SDLMouse::getMouseDeltaY() const
{
    return currentMouseY-previousMouseY;
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

    if( isMouseBoundToPoint() )
    {
        previousMouseX = mouseBindPointX;
        previousMouseY = mouseBindPointY;
        SDL_WarpMouse( mouseBindPointX, mouseBindPointY );

    }
    else {
        previousMouseX = currentMouseX;
        previousMouseY = currentMouseY;
    }

    mouseState = SDL_GetMouseState( &currentMouseX, &currentMouseY );
}

void SDLMouse::showMousePointer()
{
    int x, y;

    SDL_GetMouseState( &x, &y );
    SDL_ShowCursor( SDL_ENABLE );
    SDL_WarpMouse( x, y );
}

void SDLMouse::hideMousePointer()
{
    int x, y;

    SDL_GetMouseState( &x, &y );
    SDL_ShowCursor( SDL_DISABLE );
    SDL_WarpMouse( x, y );
}

