#ifndef MENUOBJECT_H
#define MENUOBJECT_H

#include "gameobject.h"

class MenuObject : public GameObject
{
    public:
        enum TYPES {
            TYPE_NEWGAME,
            TYPE_OPTIONS,
            TYPE_CREDITS,
            TYPE_EXIT
        };

        MenuObject( GameProgram* backpointer );
        virtual ~MenuObject();

        inline void setUp(MenuObject* newUp) { up = newUp; }
        inline void setDown(MenuObject* newDown) { down = newDown; }
        inline void setLeft(MenuObject* newLeft) { left = newLeft; }
        inline void setRight(MenuObject* newRight) { right = newRight; }

        inline void setActive(bool newActive) { active = newActive; }
        inline void setAnimationSpeed( float newAnimationSpeed) { animationSpeed = newAnimationSpeed; }
        inline void setNormalSize( float newNormalSize ) { normalSize = newNormalSize; }
        inline void setHighlightSize( float newHliglightSize ) { highlightSize = newHliglightSize; }

        inline void setType (TYPES newType) { type = newType; }

        void getFocus();
        void giveFocus(char direction);

        void activate();

        void update( float deltaTime );

    protected:
    private:
        MenuObject* up;
        MenuObject* down;
        MenuObject* left;
        MenuObject* right;

        float animationSpeed;
        float normalSize;
        float highlightSize;
        float currentSize;
        float timer;

        int type;

        bool active;

        GameProgram* owner;
};

#endif // MENUOBJECT_H
