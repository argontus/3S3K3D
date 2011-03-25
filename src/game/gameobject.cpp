#include "gameobject.h"
#include "controller.h"
#include "gameprogram.h"
#include "graphics/node.h"


GameObject::GameObject()
 : graphicalPresentation(NULL),
   gameProgram(NULL),
   parent(NULL)
{
    //ctor
}

GameObject::~GameObject()
{

    std::list<GameObject*>::iterator childIterator = children.begin();
    std::list<Controller*>::iterator controllerIterator = controllers.begin();

    // iterate over children and delete all of them
    while( childIterator != children.end() )
    {
        destroyChild( *childIterator );
        childIterator++;
    }

    // iterate over controllers and delete all of them.
    while( controllerIterator != controllers.end() )
    {
        destroyController( *controllerIterator );
        controllerIterator++;
    }

    delete graphicalPresentation;
}

void GameObject::setGameProgram( GameProgram* newGameProgram )
{
    if( newGameProgram == NULL )
        return;

    gameProgram = newGameProgram;
}

void GameObject::setGraphicalPresentation( Node* newGraphicalPresentation )
{
    if( newGraphicalPresentation == NULL )
        return;

    graphicalPresentation = newGraphicalPresentation;
}

void GameObject::setLocalTransformation( Transform2 newTransformation )
{
    localTransformation = newTransformation;
}

void GameObject::setWorldTransformation( Transform2 newTransformation )
{
    worldTransformation = newTransformation;
}

void GameObject::setParent( GameObject* newParent )
{
    if( newParent == NULL )
        return;

    /*
     * if the is a child of an another object already, we have to detach the
     * child first.
     */
    if( parent != NULL )
    {
        parent->detachChild( this );
    }

    parent = newParent;
}

void GameObject::update( float deltaTime )
{
    std::list<Controller*>::iterator controllerIterator = controllers.begin();
    std::list<GameObject*>::iterator childIterator = children.begin();

    while( controllerIterator != controllers.end() )
    {
        (*controllerIterator)->update( deltaTime );
        controllerIterator++;
    }

    while(  childIterator != children.iterator() )
    {
        (*childIterator)->update( deltaTime );
        childIterator++;
    }
}

void GameObject::onEnter( GameObject* otherObject )
{
    //does nothing
}

void GameObject::onLeave( GameObject* otherObject )
{
    //does nothing
}

void GameObject::attachChild( GameObject* child )
{
    if( child == NULL )
        return;

    child->setParent(this);
    children.push_back( child );
}

void GameObject::detachChild( GameObject* child )
{
    if( child == NULL )
        return;

    child->setParent(NULL);
    children.remove( child );
}

void GameObject::destroyChild( GameObject* child )
{
    if( child == NULL )
        return;

    detachChild( child );
    delete child;
}

void GameObject::attachController( Controller* controller )
{
    if( controller == NULL)
        return;

    controller->setObjectAttachedTo(this);
    controllers.push_back( controller );
}

void GameObject::detachController( Controller* controller )
{
    if( controller == NULL )
        return;

    controller->setObjectAttachedTo(NULL);
    controllers.remove( controller );
}

void GameObject::destroyController( Controller* controller )
{
    if( controller == NULL )
        return;

    detachController( controller );
    delete controller;
}
