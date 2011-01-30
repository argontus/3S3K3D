/**
 * @file geometry/line2.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_LINE2_H_INCLUDED
#define GEOMETRY_LINE2_H_INCLUDED

#include <geometry/vector2.h>

/**
 * Represents an unbounded 2D line.
 */
class Line2
{
public:
    // compiler-generated destructor, copy constructor and copy assignment
    // operator are fine

    /**
     * Default constructor, constructs an uninitialized line.
     */
    Line2();

    /**
     * Constructor.
     *
     * @param point A point on the line.
     * @param direction Line direction, should be unit length.
     */
    Line2(const Vector2& point, const Vector2& direction);

    /**
     * Calculates the point on this line that is closest to <code>q</code>.
     *
     * @param q A point.
     *
     * @return The point on this line that is closest to <code>q</code>.
     */
    const Vector2 closestPointTo(const Vector2& q) const;

    /**
     * Calculates the distance to a point from this line.
     *
     * @param q A point.
     *
     * @return The distance to point <code>q</code> from this line.
     */
    float distanceTo(const Vector2& q) const;

    /**
     * Calculates the squared distance to a point from this line.
     *
     * @param q A point.
     *
     * @return The squared distance to point <code>q</code> from this line.
     */
    float sqrDistanceTo(const Vector2& q) const;

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(Line2& other);

    Vector2 point;      ///< A point on the line.
    Vector2 direction;  ///< Line direction, should be unit length.
};

#endif // #ifndef GEOMETRY_LINE2_H_INCLUDED
