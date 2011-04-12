/**
 * @file graphics/rectanglef.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_RECTANGLEF_H_INCLUDED
#define GRAPHICS_RECTANGLEF_H_INCLUDED

class RectangleF
{
public:
    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

    RectangleF()
    :   x(0.0f),
        y(0.0f),
        width(0.0f),
        height(0.0f)
    {
        // ...
    }

    RectangleF(float x, float y, float width, float height)
    :   x(x),
        y(y),
        width(width),
        height(height)
    {
        // ...
    }

    float x;        ///< x-coordiate for the left border.
    float y;        ///< y-coordiate for the bottom border.
    float width;    ///< Width.
    float height;   ///< Height.
};

#endif // #ifndef GRAPHICS_RECTANGLEF_H_INCLUDED
