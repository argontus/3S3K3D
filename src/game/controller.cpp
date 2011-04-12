#include "controller.h"
#include "gameobject.h"

Controller::Controller()
 : objectAttachedTo(NULL)
{
    //ctor
}

Controller::~Controller()
{
    //dtor
}

void Controller::setObjectAttachedTo( GameObject* object )
{
    objectAttachedTo = object;
}
