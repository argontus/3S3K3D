/**
 * @file geometry/plane2.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_PLANE2_H_INCLUDED
#define GEOMETRY_PLANE2_H_INCLUDED

#include <geometry/vector2.h>

/**
 * Describes a 2D plane equation.
 */
class Plane2
{
public:
    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

    /**
     * Default constructor, constructs an uninitialized plane.
     */
    Plane2();

    /**
     * Constructor.
     *
     * @param normal Plane normal, should be unit length.
     * @param constant Plane constant.
     */
    Plane2(const Vector2& normal, float constant);

    /**
     * Constructor.
     *
     * @param normal Plane normal, should be unit length.
     * @param q A point on the plane.
     */
    Plane2(const Vector2& normal, const Vector2& q);

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(Plane2& other);

    /**
     * Plane normal, should be unit length.
     */
    Vector2 normal;

    /**
     * Plane constant, i.e. distance from origin to plane along plane normal.
     */
    float constant;
};

/**
 * Calculates the separation between plane <code>x</code> and point
 * <code>q</code>.
 *
 * @param x A plane.
 * @param q A point.
 *
 * @return The separation between plane <code>x</code> and point
 * <code>q</code>.
 */
float separation(const Plane2& x, const Vector2& q);

/**
 * Calculates the point on plane <code>x</code> that is closest to point
 * <code>q</code>.
 *
 * @param x A plane.
 * @param q A point.
 *
 * @return The point on plane <code>x</code> that is closest to point
 * <code>q</code>.
 */
const Vector2 closestPoint(const Plane2& x, const Vector2& q);

/**
 * Mirrors a point across a plane.
 *
 * @param q The point to mirror.
 * @param x The mirror plane.
 *
 * @return Mirrored <code>q</code>.
 */
const Vector2 mirror(const Vector2& q, const Plane2& x);

#endif // #ifndef GEOMETRY_PLANE2_H_INCLUDED
