/**
 * @file geometry/line3.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_LINE3_H_INCLUDED
#define GEOMETRY_LINE3_H_INCLUDED

#include <geometry/vector3.h>

/**
 * Represents an unbounded 3D line.
 */
class Line3
{
public:
    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

    /**
     * Default constructor, constructs an uninitialized line.
     */
    Line3();

    /**
     * Constructor.
     *
     * @param point Point on the line.
     * @param direction Line direction, should be unit length.
     */
    Line3(const Vector3& point, const Vector3& direction);

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(Line3& other);

    Vector3 point;      ///< Point on the line.
    Vector3 direction;  ///< Line direction, should be unit length.
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
float distance(const Line3& x, const Vector3& q);

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
float sqrDistance(const Line3& x, const Vector3& q);

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
const Vector3 closestPoint(const Line3& x, const Vector3& q);

#endif // #ifndef GEOMETRY_LINE3_H_INCLUDED
