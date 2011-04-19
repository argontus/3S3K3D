#ifndef INTROSTATE_H
#define INTROSTATE_H

#include "state.h"
#include "graphics/mesh.h"

class GameProgram;

class IntroState : public State
{
    public:
        IntroState(GameProgram* backpointer );
        virtual ~IntroState();

        virtual void update( float deltaTime );
    protected:
        float elapsedTime;
        Mesh* mesh;
    private:
};

#endif // INTROSTATE_H
