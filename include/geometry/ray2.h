/**
 * @file geometry/ray2.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_RAY2_H_INCLUDED
#define GEOMETRY_RAY2_H_INCLUDED

#include <geometry/vector2.h>

/**
 * Represents a half-bounded 2D line.
 */
class Ray2
{
public:
    // compiler-generated destructor, copy constructor and copy assignment
    // operator are fine

    /**
     * Default constructor, constructs an uninitialized ray.
     */
    Ray2();

    /**
     * Constructor.
     *
     * @param origin Ray origin.
     * @param direction Ray direction, should be unit length.
     */
    Ray2(const Vector2& origin, const Vector2& direction);

    /**
     * Calculates the point on this ray that is closest to <code>q</code>.
     *
     * @param q A point.
     *
     * @return The point on this ray that is closest to <code>q</code>.
     */
    const Vector2 closestPointTo(const Vector2& q) const;

    /**
     * Calculates the distance to a point from this ray.
     *
     * @param q A point.
     *
     * @return The distance to point <code>q</code> from this ray.
     */
    float distanceTo(const Vector2& q) const;

    /**
     * Calculates the squared distance to a point from this ray.
     *
     * @param q A point.
     *
     * @return The squared distance to point <code>q</code> from this ray.
     */
    float sqrDistanceTo(const Vector2& q) const;

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(Ray2& other);

    Vector2 origin;     ///< Ray origin.
    Vector2 direction;  ///< Ray direction, should be unit length.
};

#endif // #ifndef GEOMETRY_RAY2_H_INCLUDED
