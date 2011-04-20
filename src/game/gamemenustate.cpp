#include "gamemenustate.h"
#include "graphics/modelreader.h"
#include "graphics/groupnode.h"
#include "menuobject.h"

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
    scene->update( deltaTime );

    std::cout << "In game menu state, going back to game state" << std::endl;
    owner->previousState();
}
