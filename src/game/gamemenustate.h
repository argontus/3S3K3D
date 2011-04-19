#ifndef GAMEMENUSTATE_H
#define GAMEMENUSTATE_H

#include "state.h"
#include "graphics/mesh.h"


class GameMenuState : public State
{
    public:
        GameMenuState( GameProgram* backpointer );
        virtual ~GameMenuState();

        virtual void update( float deltaTime );
    protected:

    private:
        MenuKeyboardController menuController1;
        MenuKeyboardController menuController2;
        MenuKeyboardController menuController3;
        MenuKeyboardController menuController4;


};

#endif // GAMEMENUSTATE_H
