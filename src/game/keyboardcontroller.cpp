#include "keyboardcontroller.h"
#include "input/keyboard.h"
#include "input/sdlkeyboard.h"
#include "geometry/matrix3x3.h"
#include "graphics/node.h"


KeyboardController::KeyboardController()
    : keyboard( new SDLKeyboard() ),
      speed( 5.0f )
{
}

KeyboardController::~KeyboardController()
{
    if( keyboard )
        delete keyboard;
}

void KeyboardController::update( float deltaTime )
{
    if( objectAttachedTo != NULL )
    {
        Node* graphicalPresentation = objectAttachedTo->getGraphicalPresentation();
        Matrix3x3 rotation = graphicalPresentation->rotation();


        if( keyboard->keyIsDown( Keyboard::KEY_D ) )
		{
            graphicalPresentation->translateBy( deltaTime * rotation.row(0) * speed );
		}
		else if( keyboard->keyIsDown( Keyboard::KEY_A ) )
        {
            graphicalPresentation->translateBy( deltaTime * rotation.row(0) * -speed );
        }

        if( keyboard->keyIsDown( Keyboard::KEY_Q) )
        {
            graphicalPresentation->translateBy( deltaTime * rotation.row(1) * -speed );
        }
        else if( keyboard->keyIsDown( Keyboard::KEY_E ) )
        {
            graphicalPresentation->translateBy( deltaTime * rotation.row(1) * speed );
        }

        if( keyboard->keyIsDown( Keyboard::KEY_W) )
        {
            graphicalPresentation->translateBy( deltaTime * rotation.row(2) * -speed );
        }
        else if( keyboard->keyIsDown( Keyboard::KEY_S ) )
        {
            graphicalPresentation->translateBy( deltaTime * rotation.row(2) * speed );
        }
    }
}

void KeyboardController::setSpeed( float newSpeed )
{
    speed = newSpeed;
}