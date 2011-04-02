#include "creditsstate.h"

CreditsState::CreditsState( GameProgram* backpointer )
 : State(backpointer)
{
    //ctor
}

CreditsState::~CreditsState()
{
    //dtor
}

void CreditsState::update( float deltaTime )
{
    std::cout << "Credits state!" << std::endl;
    owner->changeState( GameProgram::STATE_QUIT );
}
