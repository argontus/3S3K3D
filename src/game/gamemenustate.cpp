#include "gamemenustate.h"
#include "graphics/modelreader.h"
#include "graphics/groupnode.h"
#include "menuobject.h"

#include <iostream>

GameMenuState::GameMenuState( GameProgram* backpointer )
 : State( backpointer )
{
    scene = new GameScene( this );


    Node* menu1;
	Node* menu2;
	Node* menu3;
	Node* menu4;

    ModelReader modelReader;
    modelReader.setMeshManager( &backpointer->meshManager_ );



    GroupNode* groupNode = new GroupNode();
    rootNode = groupNode;

    const float scaling = 0.1f;

    menu1 = modelReader.read("data/models/menuitem.3DS");
    menu1->setScaling(scaling);

    menu2 = modelReader.read("data/models/menuitem.3DS");
    menu2->setScaling(scaling);

    menu3 = modelReader.read("data/models/menuitem.3DS");
    menu3->setScaling(scaling);

    menu4 = modelReader.read("data/models/menuitem.3DS");
    menu4->setScaling(scaling);

    menu1->setTranslation(Vector3(0.0f, 20.0f, -50.0f));
    menu2->setTranslation(Vector3(0.0f, 0.0f, -50.0f));
    menu3->setTranslation(Vector3(0.0f, -20.0f, -50.0f));
    menu4->setTranslation(Vector3(0.0f, -40.0f, -50.0f));

    groupNode->attachChild(menu1);
    groupNode->attachChild(menu2);
    groupNode->attachChild(menu3);
    groupNode->attachChild(menu4);

    MenuObject* testMenuObject1 = new MenuObject( backpointer );
    testMenuObject1->setGraphicalPresentation( menu1 );
    testMenuObject1->attachController( &menuController1 );

    MenuObject* testMenuObject2 = new MenuObject( backpointer );
    testMenuObject2->setGraphicalPresentation( menu2 );
    testMenuObject2->attachController( &menuController2 );

    MenuObject* testMenuObject3 = new MenuObject( backpointer );
    testMenuObject3->setGraphicalPresentation( menu3 );
    testMenuObject3->attachController( &menuController3 );

    MenuObject* testMenuObject4 = new MenuObject( backpointer );
    testMenuObject4->setGraphicalPresentation( menu4 );
    testMenuObject4->attachController( &menuController4 );

    testMenuObject1->setType(MenuObject::TYPE_NEWGAME);
    testMenuObject2->setType(MenuObject::TYPE_OPTIONS);
    testMenuObject3->setType(MenuObject::TYPE_CREDITS);
    testMenuObject4->setType(MenuObject::TYPE_EXIT);

    testMenuObject1->setDown(testMenuObject2);

    testMenuObject2->setUp(testMenuObject1);
    testMenuObject2->setDown(testMenuObject3);

    testMenuObject3->setUp(testMenuObject2);
    testMenuObject3->setDown(testMenuObject4);

    testMenuObject4->setUp(testMenuObject3);

    testMenuObject1->setActive(true);

    scene->addObject( testMenuObject1 );
    scene->addObject( testMenuObject2 );
    scene->addObject( testMenuObject3 );
    scene->addObject( testMenuObject4 );

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
