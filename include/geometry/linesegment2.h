/**
 * @file geometry/linesegment2.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_LINESEGMENT2_H_INCLUDED
#define GEOMETRY_LINESEGMENT2_H_INCLUDED

#include <geometry/vector2.h>

/**
 * Represents a bounded 2D line.
 */
class LineSegment2
{
public:
    // compiler-generated destructor, copy constructor and copy assignment
    // operator are fine

    /**
     * Default constructor, constructs an uninitialized line segment.
     */
    LineSegment2();

    /**
     * Constructor.
     *
     * @param startPoint Start point.
     * @param endPoint End point.
     */
    LineSegment2(const Vector2& startPoint, const Vector2& endPoint);

    /**
     * Calculates the point on this line segment that is closest to
     * <code>q</code>.
     *
     * @param q A point.
     *
     * @return The point on this line segment that is closest to
     * <code>q</code>.
     */
    const Vector2 closestPointTo(const Vector2& q) const;

    /**
     * Calculates the distance to a point from this line segment.
     *
     * @param q A point.
     *
     * @return The distance to point <code>q</code> from this line segment.
     */
    float distanceTo(const Vector2& q) const;

    /**
     * Calculates the squared distance to a point from this line segment.
     *
     * @param q A point.
     *
     * @return The squared distance to point <code>q</code> from this line
     * segment.
     */
    float sqrDistanceTo(const Vector2& q) const;

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(LineSegment2& other);

    Vector2 startPoint; ///< Start point.
    Vector2 endPoint;   ///< End point.
};

#endif // #ifndef GEOMETRY_LINESEGMENT2_H_INCLUDED
