#include "mainmenustate.h"
#include "gameprogram.h"
#include "graphics/meshnode.h"
#include "graphics/texture.h"
#include "graphics/modelreader.h"
#include "graphics/groupnode.h"
#include "menuobject.h"
#include "geometry/math.h"

#include <iostream>

MainMenuState::MainMenuState( GameProgram* backpointer )
 : State( backpointer )
{
    scene = new GameScene( this );

    Node* menu1;
	Node* menu2;
	Node* menu3;
	Node* menu4;

    MenuKeyboardController* menuController1 = new MenuKeyboardController();
    MenuKeyboardController* menuController2 = new MenuKeyboardController();
    MenuKeyboardController* menuController3 = new MenuKeyboardController();
    MenuKeyboardController* menuController4 = new MenuKeyboardController();

    Texture* texture = new Texture();
    texture->loadImage("data/textures/menu/NewDiff.tga");
    texture->generateMipmap();
    textureManager_.loadResource("newDiffuse", texture);

    texture = new Texture();
    texture->loadImage("data/textures/menu/NewSpec.tga");
    texture->generateMipmap();
    textureManager_.loadResource("newSpecular", texture);

    texture = new Texture();
    texture->loadImage("data/textures/menu/NewGlow.tga");
    texture->generateMipmap();
    textureManager_.loadResource("newGlow", texture);

    texture = new Texture();
    texture->loadImage("data/textures/menu/NewNorm.tga");
    texture->generateMipmap();
    textureManager_.loadResource("newNormal", texture);


    texture = new Texture();
    texture->loadImage("data/textures/menu/OptDiff.tga");
    texture->generateMipmap();
    textureManager_.loadResource("optDiffuse", texture);

    texture = new Texture();
    texture->loadImage("data/textures/menu/OptSpec.tga");
    texture->generateMipmap();
    textureManager_.loadResource("optSpecular", texture);

    texture = new Texture();
    texture->loadImage("data/textures/menu/OptGlow.tga");
    texture->generateMipmap();
    textureManager_.loadResource("optGlow", texture);

    texture = new Texture();
    texture->loadImage("data/textures/menu/OptNorm.tga");
    texture->generateMipmap();
    textureManager_.loadResource("optNormal", texture);


    texture = new Texture();
    texture->loadImage("data/textures/menu/CreDiff.tga");
    texture->generateMipmap();
    textureManager_.loadResource("credDiffuse", texture);

    texture = new Texture();
    texture->loadImage("data/textures/menu/CreSpec.tga");
    texture->generateMipmap();
    textureManager_.loadResource("credSpecular", texture);

    texture = new Texture();
    texture->loadImage("data/textures/menu/CreGlow.tga");
    texture->generateMipmap();
    textureManager_.loadResource("credGlow", texture);

    texture = new Texture();
    texture->loadImage("data/textures/menu/CreNorm.tga");
    texture->generateMipmap();
    textureManager_.loadResource("credNormal", texture);


    texture = new Texture();
    texture->loadImage("data/textures/menu/ExitDiff.tga");
    texture->generateMipmap();
    textureManager_.loadResource("exitDiffuse", texture);

    texture = new Texture();
    texture->loadImage("data/textures/menu/ExitSpec.tga");
    texture->generateMipmap();
    textureManager_.loadResource("exitSpecular", texture);

    texture = new Texture();
    texture->loadImage("data/textures/menu/ExitGlow.tga");
    texture->generateMipmap();
    textureManager_.loadResource("exitGlow", texture);

    texture = new Texture();
    texture->loadImage("data/textures/menu/ExitNorm.tga");
    texture->generateMipmap();
    textureManager_.loadResource("exitNormal", texture);

    ModelReader modelReader;
    modelReader.setMeshManager( &backpointer->meshManager_ );

//    GroupNode* groupNode = new GroupNode();
//    rootNode = groupNode;

    //const float scaling = 1.0f;

    menu1 = modelReader.read("data/models/MenuMesh.3DS");

    MeshNode* hack = (MeshNode*)((GroupNode*)menu1)->child(0);
    //hack->setScaling(scaling);
    hack->diffuseMap = textureManager_.getResource("newDiffuse");
    hack->specularMap = textureManager_.getResource("newSpecular");
    hack->glowMap = textureManager_.getResource("newGlow");
    hack->normalMap = textureManager_.getResource("newNormal");

    menu2 = menu1->clone();
    hack = (MeshNode*)((GroupNode*)menu2)->child(0);
    //hack->setScaling(scaling);
    hack->diffuseMap = textureManager_.getResource("optDiffuse");
    hack->specularMap = textureManager_.getResource("optSpecular");
    hack->glowMap = textureManager_.getResource("optGlow");
    hack->normalMap = textureManager_.getResource("optNormal");

    menu3 = menu1->clone();
    hack = (MeshNode*)((GroupNode*)menu3)->child(0);
    //hack->setScaling(scaling);
    hack->diffuseMap = textureManager_.getResource("credDiffuse");
    hack->specularMap = textureManager_.getResource("credSpecular");
    hack->glowMap = textureManager_.getResource("credGlow");
    hack->normalMap = textureManager_.getResource("credNormal");

    menu4 = menu1->clone();
    hack = (MeshNode*)((GroupNode*)menu4)->child(0);
    //hack->setScaling(scaling);
    hack->diffuseMap = textureManager_.getResource("exitDiffuse");
    hack->specularMap = textureManager_.getResource("exitSpecular");
    hack->glowMap = textureManager_.getResource("exitGlow");
    hack->normalMap = textureManager_.getResource("exitNormal");

    const float base = 20.0f;
    const float offset = 15.0f;

    menu1->setTranslation(Vector3(0.0f, base - 0.0f * offset, -50.0f));
    menu2->setTranslation(Vector3(0.0f, base - 1.0f * offset, -50.0f));
    menu3->setTranslation(Vector3(0.0f, base - 2.0f * offset, -50.0f));
    menu4->setTranslation(Vector3(0.0f, base - 3.0f * offset, -50.0f));

    rootNode->attachChild(menu1);
    rootNode->attachChild(menu2);
    rootNode->attachChild(menu3);
    rootNode->attachChild(menu4);

    rootNode->translateBy( Vector3(2,0,0) );
    rootNode->rotateBy( Matrix3x3::yRotation( -Math::pi() / 8 ) );

    MenuObject* testMenuObject1 = new MenuObject( backpointer );
    testMenuObject1->setGraphicalPresentation( menu1 );
    testMenuObject1->attachController( menuController1 );

    MenuObject* testMenuObject2 = new MenuObject( backpointer );
    testMenuObject2->setGraphicalPresentation( menu2 );
    testMenuObject2->attachController( menuController2 );

    MenuObject* testMenuObject3 = new MenuObject( backpointer );
    testMenuObject3->setGraphicalPresentation( menu3 );
    testMenuObject3->attachController( menuController3 );

    MenuObject* testMenuObject4 = new MenuObject( backpointer );
    testMenuObject4->setGraphicalPresentation( menu4 );
    testMenuObject4->attachController( menuController4 );

    testMenuObject1->setType(MenuObject::TYPE_NEWGAME);
    testMenuObject2->setType(MenuObject::TYPE_OPTIONS);
    testMenuObject3->setType(MenuObject::TYPE_CREDITS);
    testMenuObject4->setType(MenuObject::TYPE_EXIT);

    testMenuObject1->setUp(testMenuObject4);
    testMenuObject1->setDown(testMenuObject2);

    testMenuObject2->setUp(testMenuObject1);
    testMenuObject2->setDown(testMenuObject3);

    testMenuObject3->setUp(testMenuObject2);
    testMenuObject3->setDown(testMenuObject4);

    testMenuObject4->setUp(testMenuObject3);
    testMenuObject4->setDown(testMenuObject1);

    testMenuObject1->setActive(true);

    scene->addObject( testMenuObject1 );
    scene->addObject( testMenuObject2 );
    scene->addObject( testMenuObject3 );
    scene->addObject( testMenuObject4 );

}

MainMenuState::~MainMenuState()
{
    //dtor
}

void MainMenuState::update( float deltaTime )
{
    scene->update(deltaTime);
    //std::cout << "In main menu state!" << std::endl;
    //owner->changeState(GameProgram::STATE_GAME);
}
