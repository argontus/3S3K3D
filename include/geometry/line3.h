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
    // compiler-generated destructor, copy constructor and copy assignment
    // operator are fine

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
     * Calculates the point on this line that is closest to <code>q</code>.
     *
     * @param q A point.
     *
     * @return The point on this line that is closest to <code>q</code>.
     */
    const Vector3 closestPointTo(const Vector3& q) const;

    /**
     * Calculates the distance to a point from this line.
     *
     * @param q A point.
     *
     * @return The distance to point <code>q</code> from this line.
     */
    float distanceTo(const Vector3& q) const;

    /**
     * Calculates the squared distance to a point from this line.
     *
     * @param q A point.
     *
     * @return The squared distance to point <code>q</code> from this line.
     */
    float sqrDistanceTo(const Vector3& q) const;

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(Line3& other);

    Vector3 point;      ///< Point on the line.
    Vector3 direction;  ///< Line direction, should be unit length.
};

#endif // #ifndef GEOMETRY_LINE3_H_INCLUDED
