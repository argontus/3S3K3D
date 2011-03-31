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
    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

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
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(Line2& other);

    Vector2 point;      ///< A point on the line.
    Vector2 direction;  ///< Line direction, should be unit length.
};

/**
 * Calculates the distance between line <code>x</code> and point
 * <code>q</code>.
 *
 * @param x A line.
 * @param q A point.
 *
 * @return The distance between line <code>x</code> and point <code>q</code>.
 */
float distance(const Line2& x, const Vector2& q);

/**
 * Calculates the squared distance between line <code>x</code> and point
 * <code>q</code>.
 *
 * @param x A line.
 * @param q A point.
 *
 * @return The squared distance between line <code>x</code> and point
 * <code>q</code>.
 */
float sqrDistance(const Line2& x, const Vector2& q);

/**
 * Calculates the point on line <code>x</code> that is closest to point
 * <code>q</code>.
 *
 * @param x A line.
 * @param q A point.
 *
 * @return The point on line <code>x</code> that is closest to point
 * <code>q</code>.
 */
const Vector2 closestPoint(const Line2& x, const Vector2& q);

#endif // #ifndef GEOMETRY_LINE2_H_INCLUDED
