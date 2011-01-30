/**
 * @file geometry/plane3.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_PLANE3_H_INCLUDED
#define GEOMETRY_PLANE3_H_INCLUDED

#include <geometry/vector3.h>

/**
 * Describes a 3D plane equation. Member functions of this class assume that
 * the public attributes describe a valid plane equation. The user is
 * responsible for providing valid attributes.
 */
class Plane3
{
public:
    // compiler-generated destructor, copy constructor and copy assignment
    // operator are fine

    /**
     * Default constructor, constructs an uninitialized plane.
     */
    Plane3();

    /**
     * Constructor.
     *
     * @param normal Plane normal, should be unit length.
     * @param constant Plane constant.
     */
    Plane3(const Vector3& normal, float constant);

    /**
     * Constructor.
     *
     * @param normal Plane normal, should be unit length.
     * @param q A point on the plane.
     */
    Plane3(const Vector3& normal, const Vector3& q);

    /**
     * Constructor. Points <code>a</code>, <code>b</code> and <code>c</code>
     * are assumed to be in CCW order.
     *
     * @param First point on the plane.
     * @param Second point on the plane.
     * @param Third point on the plane.
     */
    Plane3(const Vector3& a, const Vector3& b, const Vector3& c);

    /**
     * Calculates the point on this plane that is closest to <code>q</code>.
     *
     * @param q A point.
     *
     * @return The point on this plane that is closest to <code>q</code>.
     */
    const Vector3 closestPointTo(const Vector3& q) const;

    /**
     * Calculates the signed distance to a given point.
     *
     * @param q Point to which the distance is to be calculated.
     *
     * @return The signed distance to point <code>q</code> from this plane.
     */
    float distanceTo(const Vector3& q) const;

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(Plane3& other);

    Vector3 normal; ///< Plane normal, should be unit length.
    float constant; ///< Plane constant.
};

#endif // #ifndef GEOMETRY_PLANE3_H_INCLUDED
