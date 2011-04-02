#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

#include "controller.h"
#include "input/keyboard.h"

/**
 * @file game/keyboardcontroller.h
 * @author Marko Silokunnas
 *
 * An implementation of pure virtual class Controller that implements keyboard
 * movement for a GameObject that the controller is attached to.
 */

class KeyboardController : public Controller
{
    public:
        KeyboardController();
        virtual ~KeyboardController();

        virtual void update( float deltaTime );

        /**
         * TODO: implement a ShipObject class or something that contains the
         *       speed of the ship so that we don't have to set it here.
         */
        virtual inline float getSpeed() const { return speed; }
        virtual void setSpeed( float newSpeed );

        virtual inline float getRotationSpeed() const { return rotationSpeed; }
        virtual void setRotationSpeed( float newRotationSpeed );
    protected:
    private:
        Keyboard* keyboard;
        float speed;
        float rotationSpeed;
};

#endif // KEYBOARDCONTROLLER_H
