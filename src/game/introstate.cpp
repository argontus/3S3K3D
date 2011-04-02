#include "introstate.h"
#include "gameprogram.h"

#include <iostream>

IntroState::IntroState( GameProgram* backpointer)
 : State( backpointer )
{

}

IntroState::~IntroState()
{
    //dtor
}

void IntroState::update( float deltaTime )
{
    std::cout << "In intro state!" << std::endl;
    owner->changeState( GameProgram::STATE_MAINMENU );
}
