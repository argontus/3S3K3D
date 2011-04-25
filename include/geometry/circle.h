/**
 * @file geometry/circle.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_CIRCLE_H_INCLUDED
#define GEOMETRY_CIRCLE_H_INCLUDED

#include <geometry/vector2.h>

class Interval;

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

/**
 * Calculates the interval of <code>x</code> along <code>axis</code>. If
 * <code>x.radius < 0.0f</code>, the returned interval will be empty.
 *
 * @param x The circle whose interval is to be calculated.
 * @param axis The axis along which the interval is to be calculated.
 *
 * @return The calculated interval.
 */
const Interval interval(const Circle& x, const Vector2& axis);

#endif // #ifndef GEOMETRY_CIRCLE_H_INCLUDED
