/**
 * @file graphics/rectanglei.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_RECTANGLEI_H_INCLUDED
#define GRAPHICS_RECTANGLEI_H_INCLUDED

/**
 * Describes a rectange with <code>int</code> values.
 */
class RectangleI
{
public:
    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

    RectangleI()
    :   x(0),
        y(0),
        width(0),
        height(0)
    {
        // ...
    }

    RectangleI(int x, int y, int width, int height)
    :   x(x),
        y(y),
        width(width),
        height(height)
    {
        // ...
    }

    int x;        ///< Minimum x coordinate within the rectangle.
    int y;        ///< Minimum y coordinate within the rectangle.
    int width;    ///< Width.
    int height;   ///< Height.
};

#endif // #ifndef GRAPHICS_RECTANGLEI_H_INCLUDED
