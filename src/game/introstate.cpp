#include "introstate.h"
#include "gameprogram.h"
#include "graphics/meshnode.h"
#include "graphics/texture.h"

#include <iostream>

IntroState::IntroState( GameProgram* backpointer)
 : State( backpointer )
{
    rootNode = new MeshNode();
    mesh = backpointer->createBox( 5.0f, 5.0f, 5.0f );

    //load textures
    Texture* diffuse = new Texture();
    diffuse->loadImage("data/textures/diffuse.tga");
    backpointer->textureManager_.loadResource("diffuseMap", diffuse);

    Texture* specular = new Texture();
    specular->loadImage("data/textures/specular.tga");
    backpointer->textureManager_.loadResource("specularMap", specular);

    Texture* glow = new Texture();
    glow->loadImage("data/textures/glow.tga");
    backpointer->textureManager_.loadResource("glowMap", specular);

    Texture* normal = new Texture();
    normal->loadImage("data/textures/normal.tga");
    backpointer->textureManager_.loadResource("normalMap", specular);

    ((MeshNode*)rootNode)->diffuseMap = backpointer->textureManager_.getResource("diffuseMap");
    ((MeshNode*)rootNode)->specularMap = backpointer->textureManager_.getResource("specularMap");
    ((MeshNode*)rootNode)->glowMap = backpointer->textureManager_.getResource("glowMap");
    ((MeshNode*)rootNode)->normalMap = backpointer->textureManager_.getResource("normalMap");

    ((MeshNode*)rootNode)->setMesh(mesh);
}

IntroState::~IntroState()
{
    delete mesh;
}

void IntroState::update( float deltaTime )
{
    elapsedTime += deltaTime;

    rootNode->rotateBy( Matrix3x3::yRotation(0.5f*deltaTime) );

    if( elapsedTime >= 5.0f )
    {
        owner->changeState( GameProgram::STATE_MAINMENU );
    }

}
