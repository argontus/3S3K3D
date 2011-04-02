#ifndef INTROSTATE_H
#define INTROSTATE_H

#include "state.h"

class GameProgram;

class IntroState : public State
{
    public:
        IntroState(GameProgram* backpointer );
        virtual ~IntroState();

        virtual void update( float deltaTime );
    protected:
    private:
};

#endif // INTROSTATE_H
