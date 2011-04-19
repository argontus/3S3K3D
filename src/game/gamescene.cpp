/**
 * @file game/gamescene.cpp
 * @author Juhani Alanko
 */

#include "gamescene.h"
#include "state.h"
#include "gameobject.h"

GameScene::GameScene( State* parentState )
:   state_( parentState )
{
    //ctor
}

GameScene::~GameScene()
{
    std::vector<GameObject*>::iterator iter = gameObjects_.begin();

    while( iter != gameObjects_.end() )
    {
        removeObject( *iter );
        iter++;
    }
}


void GameScene::update( float deltaTime )
{
    int i;
    for( i = 0; i < gameObjects_.size(); i++ )
    {
        GameObject* current = gameObjects_.at( i );

        if( current != NULL )
        {
            current->update( deltaTime );
        }
    }
}


void GameScene::removeObject( GameObject* object )
{
    if( object != NULL )
    {
        std::vector<GameObject*>::iterator iter = gameObjects_.begin();

        while( iter != gameObjects_.end() )
        {
            if( *iter == object )
            {
                gameObjects_.erase( iter );
                delete *iter;
                *iter = NULL;

                break;
            }

            iter++;
        }
    }

}


void GameScene::addObject( GameObject* object )
{
    if( object != NULL )
    {
        gameObjects_.push_back( object );
    }
}

