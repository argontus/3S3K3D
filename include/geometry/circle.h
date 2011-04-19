/**
 * @file geometry/circle.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_CIRCLE_H_INCLUDED
#define GEOMETRY_CIRCLE_H_INCLUDED

#include <geometry/vector2.h>

// TODO: rename this to Circle2 and implement a Circle3 class
/**
 * Describes a circle.
 */
class Circle
{
public:
    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

    /**
     * Default constructor, constructs an uninitialized circle.
     */
    Circle();

    /**
     * Constructor.
     *
     * @param center Center point.
     * @param radius Radius.
     */
    Circle(const Vector2& center, float radius);

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(Circle& other);

    Vector2 center; ///< Center point.
    float radius;   ///< Radius.
};

#endif // #ifndef GEOMETRY_CIRCLE_H_INCLUDED
