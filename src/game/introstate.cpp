#include "introstate.h"
#include "graphics/meshnode.h"


#include <iostream>

IntroState::IntroState( GameProgram* backpointer)
 : State( backpointer )
{
    MeshNode* asd = new MeshNode();
    rootNode->attachChild( asd );

    mesh = backpointer->createBox( 5.0f, 5.0f, 5.0f );

    //load textures
    Texture* diffuse = new Texture();
    diffuse->loadImage("data/textures/diffuse.tga");
    diffuse->generateMipmap();
    backpointer->textureManager_.loadResource("diffuseMap", diffuse);

    Texture* specular = new Texture();
    specular->loadImage("data/textures/specular.tga");
    specular->generateMipmap();
    backpointer->textureManager_.loadResource("specularMap", specular);

    Texture* glow = new Texture();
    glow->loadImage("data/textures/glow.tga");
    glow->generateMipmap();
    backpointer->textureManager_.loadResource("glowMap", glow);

    Texture* normal = new Texture();
    normal->loadImage("data/textures/normal.tga");
    normal->generateMipmap();
    backpointer->textureManager_.loadResource("normalMap", normal);

    asd->setMesh(mesh);
    asd->updateModelExtents();

    asd->diffuseMap = diffuse;
    asd->specularMap = specular;
    asd->glowMap = glow;
    asd->normalMap = normal;

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

    if( keyboard.keyWasPressedInThisFrame(Keyboard::KEY_F12) )
    {
        owner->addState( GameProgram::STATE_MAINMENU );
    }
}
