#include "mainmenustate.h"
#include "gameprogram.h"

#include <iostream>

MainMenuState::MainMenuState( GameProgram* backpointer )
 : State( backpointer )
{
    //ctor
}

MainMenuState::~MainMenuState()
{
    //dtor
}

void MainMenuState::update( float deltaTime )
{
    std::cout << "In main menu state!" << std::endl;
    owner->changeState(GameProgram::STATE_GAME);
}
