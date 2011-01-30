/**
 * @file geometry/ray3.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_RAY3_H_INCLUDED
#define GEOMETRY_RAY3_H_INCLUDED

#include <geometry/vector3.h>

/**
 * Represents a half-bounded 3D line.
 */
class Ray3
{
public:
    // compiler-generated destructor, copy constructor and copy assignment
    // operator are fine

    /**
     * Default constructor, constructs an uninitialized ray.
     */
    Ray3();

    /**
     * Constructor.
     *
     * @param origin Ray origin.
     * @param direction Ray direction, should be unit length.
     */
    Ray3(const Vector3& origin, const Vector3& direction);

    /**
     * Calculates the point on this ray that is closest to <code>q</code>.
     *
     * @param q A point.
     *
     * @return The point on this ray that is closest to <code>q</code>.
     */
    const Vector3 closestPointTo(const Vector3& q) const;

    /**
     * Calculates the distance to a point from this ray.
     *
     * @param q A point.
     *
     * @return The distance to point <code>q</code> from this ray.
     */
    float distanceTo(const Vector3& q) const;

    /**
     * Calculates the squared distance to a point from this ray.
     *
     * @param q A point.
     *
     * @return The squared distance to point <code>q</code> from this ray.
     */
    float sqrDistanceTo(const Vector3& q) const;

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(Ray3& other);

    Vector3 origin;     ///< Ray origin.
    Vector3 direction;  ///< Ray direction, should be unit length.
};

#endif // #ifndef GEOMETRY_RAY3_H_INCLUDED
