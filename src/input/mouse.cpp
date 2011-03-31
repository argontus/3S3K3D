#include "input/mouse.h"

Mouse::Mouse()
 : mouseBindPointX(0),
   mouseBindPointY(0),
   mouseX(0),
   mouseY(0),
   mouseLastX(0),
   mouseLastY(0)
{
}

Mouse::~Mouse()
{
}

int Mouse::getNumberOfMouseButtons()
{
    return numberOfMouseButtons;
}

void Mouse::setMouseMode( MOUSEMODE mode )
{
    mouseMode = mode;
}

void Mouse::setMouseBindPoint( int x, int y )
{
    mouseBindPointX = x;
    mouseBindPointY = y;
}

int Mouse::getMouseDeltaX()
{
    return mouseX-mouseLastX;
}

int Mouse::getMouseDeltaY()
{
    return mouseY-mouseLastY;
}
