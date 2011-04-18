#include "menukeyboardcontroller.h"
#include "input/keyboard.h"
#include "input/sdlkeyboard.h"
#include "geometry/matrix3x3.h"
#include "graphics/node.h"
#include "geometry/vector3.h"

MenuKeyboardController::MenuKeyboardController()
    : keyboard( new SDLKeyboard() )
{
}

MenuKeyboardController::~MenuKeyboardController()
{
        if( keyboard )
            delete keyboard;
}

void MenuKeyboardController::update(float deltaTime)
{
    if( objectAttachedTo != NULL )
    {
        {
            attachedMenuObject = (MenuObject*)objectAttachedTo;

            if( keyboard->keyWasPressedInThisFrame( Keyboard::KEY_W) )
            {
                attachedMenuObject->giveFocus('u');
            }
            else if( keyboard->keyWasPressedInThisFrame( Keyboard::KEY_S ) )
            {
                attachedMenuObject->giveFocus('d');
            }
            else if( keyboard->keyWasPressedInThisFrame( Keyboard::KEY_A ) )
            {
                attachedMenuObject->giveFocus('l');
            }
            else if( keyboard->keyWasPressedInThisFrame( Keyboard::KEY_D ) )
            {
                attachedMenuObject->giveFocus('r');
            }
            else if( keyboard->keyWasPressedInThisFrame( Keyboard::KEY_ENTER ) )
            {
                attachedMenuObject->activate();
            }
        }
    }
}
