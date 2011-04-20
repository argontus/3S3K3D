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

};

#endif // GAMEMENUSTATE_H
