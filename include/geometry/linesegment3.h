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
    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

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
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(LineSegment3& other);

    Vector3 startPoint; ///< Start point.
    Vector3 endPoint;   ///< End point.
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
float distance(const LineSegment3& x, const Vector3& q);

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
float sqrDistance(const LineSegment3& x, const Vector3& q);

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
const Vector3 closestPoint(const LineSegment3& x, const Vector3& q);

#endif // #ifndef GEOMETRY_LINESEGMENT3_H_INCLUDED
