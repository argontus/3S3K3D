/**
 * @file graphics/rectanglef.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_RECTANGLEF_H_INCLUDED
#define GRAPHICS_RECTANGLEF_H_INCLUDED

/**
 * Describes a rectange with <code>float</code> values.
 */
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

    float x;        ///< Minimum x coordinate within the rectangle.
    float y;        ///< Minimum y coordinate within the rectangle.
    float width;    ///< Width.
    float height;   ///< Height.
};

#endif // #ifndef GRAPHICS_RECTANGLEF_H_INCLUDED
