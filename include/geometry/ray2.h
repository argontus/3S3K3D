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
    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

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
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(Ray2& other);

    Vector2 origin;     ///< Ray origin.
    Vector2 direction;  ///< Ray direction, should be unit length.
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
float distance(const Ray2& x, const Vector2& q);

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
float sqrDistance(const Ray2& x, const Vector2& q);

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
const Vector2 closestPoint(const Ray2& x, const Vector2& q);

#endif // #ifndef GEOMETRY_RAY2_H_INCLUDED
