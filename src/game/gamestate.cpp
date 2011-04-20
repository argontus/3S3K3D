#include "gamestate.h"
#include "gameobject.h"
#include "keyboardcontroller.h"
#include "graphics/texture.h"
#include "graphics/meshnode.h"

#include  <iostream>
#include <graphics/modelreader.h>

GameState::GameState( GameProgram* backpointer )
 : State(backpointer)
{
    gameScene = new GameScene(this);

    ModelReader modelReader;
    modelReader.setMeshManager( &backpointer->meshManager_ );

// PLAYER
    GameObject* playerShip = new GameObject();
    KeyboardController* keyboardController = new KeyboardController();
    keyboardController->setSpeed( 15.0f );

    playerShip->attachController(keyboardController);
    GroupNode* node = (GroupNode*)modelReader.read("data/models/ship2.3DS");
    node->setScaling( 0.09 );
    playerShip->setGraphicalPresentation( node );

    Texture* diffuse = new Texture();
    diffuse->loadImage("data/textures/ship2.tga");
    diffuse->generateMipmap();
    backpointer->textureManager_.loadResource("ship_diffuse", diffuse);

    Texture* specular = new Texture();
    specular->loadImage("data/textures/ship2Spe.tga");
    specular->generateMipmap();
    backpointer->textureManager_.loadResource("ship_specular", specular);

    Texture* normal = new Texture();
    normal->loadImage("data/textures/ship2Nor.tga");
    normal->generateMipmap();
    backpointer->textureManager_.loadResource("ship_normal", normal);

    Texture* glow = new Texture();
    glow->loadImage("data/textures/ship2SL.tga");
    glow->generateMipmap();
    backpointer->textureManager_.loadResource("ship_glow", glow);

    MeshNode* playerMesh = (MeshNode*)node->child(0);
    playerMesh->diffuseMap = diffuse;
    playerMesh->specularMap = specular;
    playerMesh->normalMap = normal;
    playerMesh->glowMap = glow;
// PLAYER END


// ENEMY
    GameObject* enemyShip = new GameObject();

    //enemyShip->attachController();
    node = (GroupNode*)modelReader.read("data/models/ship1.3DS");
    node->setScaling( 0.2 );
    enemyShip->setGraphicalPresentation( node );

    MeshNode* enemyMesh = (MeshNode*)node->child(0);
    enemyMesh->diffuseMap = diffuse;
    enemyMesh->specularMap = specular;
    enemyMesh->normalMap = normal;
    enemyMesh->glowMap = glow;
// ENEMY END

    gameScene->addObject( playerShip );
    gameScene->addObject( enemyShip );

    rootNode->attachChild( playerShip->getGraphicalPresentation() );
    rootNode->attachChild( enemyShip->getGraphicalPresentation() );
}

GameState::~GameState()
{
    delete gameScene;
}

void GameState::update( float deltaTime )
{
    gameScene->update(deltaTime);
}
