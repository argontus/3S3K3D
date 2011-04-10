#include "menukeyboardcontroller.h"
#include "input/keyboard.h"
#include "input/sdlkeyboard.h"

MenuKeyboardController::MenuKeyboardController()
    : keyboard( new SDLKeyboard() ),
      attachedMenuObject(NULL)
{
}

MenuKeyboardController::~MenuKeyboardController()
{
        if( keyboard )
            delete keyboard;
        if ( attachedMenuObject )
            delete attachedMenuObject;
}

void MenuKeyboardController::update(float deltaTime)
{
    if( attachedMenuObject != NULL )
    {
        if( keyboard->keyIsDown( Keyboard::KEY_W) )
        {
            attachedMenuObject->giveFocus('u');
        }
        else if( keyboard->keyIsDown( Keyboard::KEY_S ) )
        {
            attachedMenuObject->giveFocus('d');
        }
        else if( keyboard->keyIsDown( Keyboard::KEY_A ) )
        {
            attachedMenuObject->giveFocus('l');
        }
        else if( keyboard->keyIsDown( Keyboard::KEY_D ) )
        {
            attachedMenuObject->giveFocus('r');
        }
    }
}
