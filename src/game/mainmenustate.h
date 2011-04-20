#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "state.h"

class MainMenuState : public State
{
    public:
        MainMenuState( GameProgram* backpointer );
        virtual ~MainMenuState();

        virtual void update( float deltaTime );
    protected:
        TextureManager textureManager_;

    private:
};

#endif // MAINMENUSTATE_H
