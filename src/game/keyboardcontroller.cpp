#include "keyboardcontroller.h"
#include "input/keyboard.h"
#include "input/sdlkeyboard.h"
#include "geometry/matrix3x3.h"
#include "graphics/node.h"
#include "geometry/vector3.h"

KeyboardController::KeyboardController()
    : keyboard( new SDLKeyboard() ),
      speed( 5.0f ),
      rotationSpeed( 5.0f )
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
            graphicalPresentation->rotateBy( Matrix3x3::zRotation( -rotationSpeed * deltaTime ));
		}
		else if( keyboard->keyIsDown( Keyboard::KEY_A ) )
        {
            graphicalPresentation->rotateBy( Matrix3x3::zRotation( rotationSpeed * deltaTime ));
        }

        if( keyboard->keyIsDown( Keyboard::KEY_Q) )
        {
            Vector3 direction = -graphicalPresentation->worldTransform().rotation.row(1);
            graphicalPresentation->rotateBy( Matrix3x3::rotation( direction, rotationSpeed * deltaTime ));
        }
        else if( keyboard->keyIsDown( Keyboard::KEY_E ) )
        {
            Vector3 direction = -graphicalPresentation->worldTransform().rotation.row(1);
            graphicalPresentation->rotateBy( Matrix3x3::rotation( direction, -rotationSpeed * deltaTime ));
        }

        if( keyboard->keyIsDown( Keyboard::KEY_W) )
        {
            Vector3 direction = -graphicalPresentation->worldTransform().rotation.row(1);
            graphicalPresentation->translateBy( direction * speed * deltaTime );
        }
        else if( keyboard->keyIsDown( Keyboard::KEY_S ) )
        {
            Vector3 direction = -graphicalPresentation->worldTransform().rotation.row(1);
            graphicalPresentation->translateBy( -direction * speed * deltaTime );
        }
    }
}

void KeyboardController::setSpeed( float newSpeed )
{
    speed = newSpeed;
}

void KeyboardController::setRotationSpeed( float newRotationSpeed )
{
    rotationSpeed = newRotationSpeed;
}
