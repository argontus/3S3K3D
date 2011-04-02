#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "state.h"

class GameState : public State
{
    public:
        GameState( GameProgram* backpointer );
        virtual ~GameState();

        virtual void update( float deltaTime );
    protected:
    private:
};

#endif // GAMESTATE_H
