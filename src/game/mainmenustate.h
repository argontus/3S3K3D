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
    private:
};

#endif // MAINMENUSTATE_H
