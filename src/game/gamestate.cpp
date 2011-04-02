#include "gamestate.h"
#include  <iostream>

GameState::GameState( GameProgram* backpointer )
 : State(backpointer)
{
}

GameState::~GameState()
{
    //dtor
}

void GameState::update( float deltaTime )
{

}
