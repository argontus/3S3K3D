#include "input/mouse.h"

Mouse::Mouse()
 : mouseX(0),
   mouseY(0),
   mouseBindPointX(0),
   mouseBindPointY(0)
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
