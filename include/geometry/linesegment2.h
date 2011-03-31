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
    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

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
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(LineSegment2& other);

    Vector2 startPoint; ///< Start point.
    Vector2 endPoint;   ///< End point.
};

/**
 * Calculates the distance between line segment <code>x</code> and point
 * <code>q</code>.
 *
 * @param x A line segment.
 * @param q A point.
 *
 * @return The distance between line segment <code>x</code> and point
 * <code>q</code>.
 */
float distance(const LineSegment2& x, const Vector2& q);

/**
 * Calculates the squared distance between line segment <code>x</code> and
 * point <code>q</code>.
 *
 * @param x A line segment.
 * @param q A point.
 *
 * @return The squared distance between line segment <code>x</code> and point
 * <code>q</code>.
 */
float sqrDistance(const LineSegment2& x, const Vector2& q);

/**
 * Calculates the point on line segment <code>x</code> that is closest to point
 * <code>q</code>.
 *
 * @param x A line segment.
 * @param q A point.
 *
 * @return The point on line segment <code>x</code> that is closest to point
 * <code>q</code>.
 */
const Vector2 closestPoint(const LineSegment2& x, const Vector2& q);

#endif // #ifndef GEOMETRY_LINESEGMENT2_H_INCLUDED
