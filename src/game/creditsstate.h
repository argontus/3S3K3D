#ifndef CREDITSSTATE_H
#define CREDITSSTATE_H

#include "state.h"


class CreditsState : public State
{
    public:
        CreditsState( GameProgram* backpointer );
        virtual ~CreditsState();

        virtual void update( float deltaTime );
    protected:
    private:
};

#endif // CREDITSSTATE_H
