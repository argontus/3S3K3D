#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

#include "controller.h"
#include "input/keyboard.h"

class KeyboardController : public Controller
{
    public:
        KeyboardController();
        virtual ~KeyboardController();

        virtual void update( float deltaTime );

        virtual inline float getSpeed() const { return speed; }

        virtual void setSpeed( float newSpeed );
    protected:
    private:
        Keyboard* keyboard;
        float speed;
};

#endif // KEYBOARDCONTROLLER_H
