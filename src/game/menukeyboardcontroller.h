#ifndef MENUKEYBOARDCONTROLLER_H
#define MENUKEYBOARDCONTROLLER_H

#include "controller.h"
#include "menuobject.h"
#include "input/keyboard.h"


class MenuKeyboardController : public Controller
{
    public:
        MenuKeyboardController();
        virtual ~MenuKeyboardController();

        virtual void update( float deltaTime );

        inline void setAttachedMenuObject(MenuObject* newAttachedMenuObject) { attachedMenuObject = newAttachedMenuObject; }

    protected:
    private:
        Keyboard* keyboard;
        MenuObject* attachedMenuObject;
};

#endif // MENUKEYBOARDCONTROLLER_H
