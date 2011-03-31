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
    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

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
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(Ray3& other);

    Vector3 origin;     ///< Ray origin.
    Vector3 direction;  ///< Ray direction, should be unit length.
};

/**
 * Calculates the distance between ray <code>x</code> and point
 * <code>q</code>.
 *
 * @param x A ray.
 * @param q A point.
 *
 * @return The distance between ray <code>x</code> and point <code>q</code>.
 */
float distance(const Ray3& x, const Vector3& q);

/**
 * Calculates the squared distance between ray <code>x</code> and point
 * <code>q</code>.
 *
 * @param x A ray.
 * @param q A point.
 *
 * @return The squared distance between ray <code>x</code> and point
 * <code>q</code>.
 */
float sqrDistance(const Ray3& x, const Vector3& q);

/**
 * Calculates the point on ray <code>x</code> that is closest to point
 * <code>q</code>.
 *
 * @param x A ray.
 * @param q A point.
 *
 * @return The point on ray <code>x</code> that is closest to point
 * <code>q</code>.
 */
const Vector3 closestPoint(const Ray3& x, const Vector3& q);

#endif // #ifndef GEOMETRY_RAY3_H_INCLUDED
