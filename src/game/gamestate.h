#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "state.h"
#include "gamescene.h"

class GameState : public State
{
    public:
        GameState( GameProgram* backpointer );
        virtual ~GameState();

        virtual void update( float deltaTime );
    protected:
        GameScene* gameScene;

    private:
};

#endif // GAMESTATE_H
