/**
 * @file geometry/plane2.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_PLANE2_H_INCLUDED
#define GEOMETRY_PLANE2_H_INCLUDED

#include <geometry/vector2.h>

/**
 * Describes a 2D plane equation. Member functions of this class assume that
 * the public attributes describe a valid plane equation. The user is
 * responsible for providing valid attributes.
 */
class Plane2
{
public:
    // compiler-generated destructor, copy constructor and copy assignment
    // operator are fine

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
     * Calculates the point on this plane that is closest to <code>q</code>.
     *
     * @param q A point.
     *
     * @return The point on this plane that is closest to <code>q</code>.
     */
    const Vector2 closestPointTo(const Vector2& q) const;

    /**
     * Calculates the signed distance to a given point.
     *
     * @param q Point to which the distance is to be calculated.
     *
     * @return The signed distance to point <code>q</code> from this plane.
     */
    float distanceTo(const Vector2& q) const;

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(Plane2& other);

    Vector2 normal; ///< Plane normal, should be unit length.
    float constant; ///< Plane constant.
};

/**
 * Mirrors a point across a plane.
 *
 * @param q The point to mirror.
 * @param plane The mirror plane.
 *
 * @return Mirrored <code>q</code>.
 */
const Vector2 mirror(const Vector2& q, const Plane2& plane);

#endif // #ifndef GEOMETRY_PLANE2_H_INCLUDED
