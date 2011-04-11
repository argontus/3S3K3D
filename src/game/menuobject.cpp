#include "menuobject.h"
#include "graphics/node.h"
#include <iostream>
#include <geometry/vector3.h>

MenuObject::MenuObject()
    : up(NULL),
      down(NULL),
      left(NULL),
      right(NULL),
      animationSpeed(5.0f),
      normalSize(0.1f),
      highlightSize(0.5f),
      currentSize(0.1f),
      timer(0.0f),
      active(false)

{
}

MenuObject::~MenuObject()
{
    if( up )
        delete up;
    if( down )
        delete down;
    if( left )
        delete left;
    if( right )
        delete right;
}

void MenuObject::getFocus()
{
    active = true;
    timer = 0.0f;
}

void MenuObject::giveFocus(char direction)
{
    if(active && timer>0.5f)
    {
        switch (direction)
        {
            case 'u':
            case 'U':
                if(up != NULL)
                {
                    up->getFocus();
                    timer = 0.0f;
                    active = false;
                }
                break;
            case 'd':
            case 'D':
                if(down != NULL)
                {
                    down->getFocus();
                    timer = 0.0f;
                    active = false;
                }
                break;
            case 'l':
            case 'L':
                if(left != NULL)
                {
                    left->getFocus();
                    timer = 0.0f;
                    active = false;
                }
                break;
            case 'r':
            case 'R':
                if(right != NULL)
                {
                    right->getFocus();
                    timer = 0.0f;
                    active = false;
                }
                break;
            default:
                break;
        }
    }
}

void MenuObject::update(float deltaTime)
{
    if(active)
    {
        timer += deltaTime;
    }

    GameObject::update( deltaTime );

    Node* graphicalPresentation = getGraphicalPresentation();

    if(active && currentSize < highlightSize)
    {
        currentSize += animationSpeed*deltaTime;
        if (currentSize>highlightSize)
            currentSize=highlightSize;
        graphicalPresentation->setScaling(currentSize);
    }
    else if (!active && currentSize > normalSize)
    {
        currentSize -= animationSpeed*deltaTime;
        if (currentSize<normalSize)
            currentSize=normalSize;
        graphicalPresentation->setScaling(currentSize);
    }
}

void MenuObject::activate()
{

}







