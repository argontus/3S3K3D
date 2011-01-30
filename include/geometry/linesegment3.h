/**
 * @file geometry/linesegment3.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_LINESEGMENT3_H_INCLUDED
#define GEOMETRY_LINESEGMENT3_H_INCLUDED

#include <geometry/vector3.h>

/**
 * Represents a bounded 3D line.
 */
class LineSegment3
{
public:
    // compiler-generated destructor, copy constructor and copy assignment
    // operator are fine

    /**
     * Default constructor, constructs an uninitialized line segment.
     */
    LineSegment3();

    /**
     * Constructor.
     *
     * @param startPoint Start point.
     * @param endPoint End point.
     */
    LineSegment3(const Vector3& startPoint, const Vector3& endPoint);

    /**
     * Calculates the point on this line segment that is closest to
     * <code>q</code>.
     *
     * @param q A point.
     *
     * @return The point on this line segment that is closest to
     * <code>q</code>.
     */
    const Vector3 closestPointTo(const Vector3& q) const;

    /**
     * Calculates the distance to a point from this line segment.
     *
     * @param q A point.
     *
     * @return The distance to point <code>q</code> from this line segment.
     */
    float distanceTo(const Vector3& q) const;

    /**
     * Calculates the squared distance to a point from this line segment.
     *
     * @param q A point.
     *
     * @return The squared distance to point <code>q</code> from this line
     * segment.
     */
    float sqrDistanceTo(const Vector3& q) const;

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(LineSegment3& other);

    Vector3 startPoint; ///< Start point.
    Vector3 endPoint;   ///< End point.
};

#endif // #ifndef GEOMETRY_LINESEGMENT3_H_INCLUDED
