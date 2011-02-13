#include "input/mouse.h"

Mouse::Mouse()
 : currentMouseX(0),
   currentMouseY(0),
   previousMouseX(0),
   previousMouseY(0)
{
}

Mouse::~Mouse()
{
}

int Mouse::getNumberOfMouseButtons()
{
    return numberOfMouseButtons;
}

void Mouse::setMouseBindPointX( const int x )
{
    mouseBindPointX = x;
}

void Mouse::setMouseBindPointY( const int y )
{
    mouseBindPointY = y;
}

void Mouse::bindMouse()
{
    mouseBoundToPoint = true;
}

void Mouse::releaseMouse()
{
    mouseBoundToPoint = false;
}
