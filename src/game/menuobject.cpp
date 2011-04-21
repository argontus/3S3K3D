#include "menuobject.h"
#include "graphics/node.h"
#include "gameprogram.h"
#include <iostream>
#include <geometry/vector3.h>

MenuObject::MenuObject( GameProgram* backpointer )
    : up(NULL),
      down(NULL),
      left(NULL),
      right(NULL),
      animationSpeed(5.0f),
      normalSize(0.3f),
      highlightSize(0.5f),
      currentSize(0.3f),
      timer(0.0f),
      active(false),
      owner( backpointer )
{
}

MenuObject::~MenuObject()
{
}

void MenuObject::getFocus()
{
    active = true;
    timer = 0.0f;
}

void MenuObject::giveFocus(char direction)
{
    if(active && timer>0.2f)
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
    }
    else if (!active && currentSize > normalSize)
    {
        currentSize -= animationSpeed*deltaTime;
        if (currentSize<normalSize)
            currentSize=normalSize;
    }

    graphicalPresentation->setScaling(currentSize);
}

void MenuObject::activate()
{
    if(active && timer>0.2f)
    {
        switch( type )
        {
            case TYPE_NEWGAME:
                timer = 0.0f;
                owner->addState(GameProgram::STATE_GAME);
                break;

            case TYPE_OPTIONS:
                timer = 0.0f;
                owner->addState(GameProgram::STATE_GAMEMENU);
                break;

            case TYPE_CREDITS:
                timer = 0.0f;
                owner->addState(GameProgram::STATE_CREDITS);
                break;

            case TYPE_EXIT:
                timer = 0.0f;
                owner->changeState(GameProgram::STATE_QUIT);
                break;

            default:
                break;
        }
    }
}







