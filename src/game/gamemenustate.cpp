#include "gamemenustate.h"

#include <iostream>

GameMenuState::GameMenuState( GameProgram* backpointer )
 : State( backpointer )
{
}

GameMenuState::~GameMenuState()
{
    //dtor
}

void GameMenuState::update( float deltaTime )
{
    std::cout << "In game menu state, going back to game state" << std::endl;
    owner->previousState();
}
