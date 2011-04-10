#ifndef MENUOBJECT_H
#define MENUOBJECT_H

#include "gameobject.h"


class MenuObject : public GameObject
{
    public:
        MenuObject();
        virtual ~MenuObject();

        inline void setUp(MenuObject* newUp) { up = newUp; }
        inline void setDown(MenuObject* newDown) { down = newDown; }
        inline void setLeft(MenuObject* newLeft) { left = newLeft; }
        inline void setRight(MenuObject* newRight) { right = newRight; }

        inline void setActive(bool newActive) { active = newActive; }
        inline void setAnimationSpeed(MenuObject* newRight) { right = newRight; }
        inline void setNormalSize( float newNormalSize ) { normalSize = newNormalSize; }
        inline void setHighlightSize( float newHliglightSize ) { highlightSize = newHliglightSize; }

        void getFocus();
        void giveFocus(char direction);

        void update( float deltaTime );

    protected:
    private:
        MenuObject* up;
        MenuObject* down;
        MenuObject* left;
        MenuObject* right;

        bool active;

        float animationSpeed;
        float normalSize;
        float highlightSize;
        float currentSize;
};

#endif // MENUOBJECT_H
