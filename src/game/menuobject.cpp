#include "menuobject.h"

MenuObject::MenuObject()
    : up(NULL),
      down(NULL),
      left(NULL),
      right(NULL)
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
}

void MenuObject::giveFocus(char direction)
{
    if(active)
    {
        switch (direction)
        {
            case 'u':
            case 'U':
                if(up != NULL)
                {
                    up->getFocus();
                    active = false;
                }
                break;
            case 'd':
            case 'D':
                if(down != NULL)
                {
                    down->getFocus();
                    active = false;
                }
                break;
            case 'l':
            case 'L':
                if(left != NULL)
                {
                    left->getFocus();
                    active = false;
                }
                break;
            case 'r':
            case 'R':
                if(right != NULL)
                {
                    right->getFocus();
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
    if(active && currentSize < highlightSize)
    {
        //TODO increase size
    }
    else if (!active && currentSize > normalSize)
    {
        //TODO decrease size
    }
}








