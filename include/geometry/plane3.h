/**
 * @file geometry/plane3.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_PLANE3_H_INCLUDED
#define GEOMETRY_PLANE3_H_INCLUDED

#include <geometry/vector3.h>

class Line3;

/**
 * Describes a 3D plane equation.
 */
class Plane3
{
public:
    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

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
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(Plane3& other);

    /**
     * Plane normal, should be unit length.
     */
    Vector3 normal;

    /**
     * Plane constant, i.e. distance from origin to plane along plane normal.
     */
    float constant;
};

// TODO: comments
bool intersect(const Plane3& plane, const Line3& line, float* t);

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
float separation(const Plane3& x, const Vector3& q);

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
const Vector3 closestPoint(const Plane3& x, const Vector3& q);

/**
 * Mirrors a point across a plane.
 *
 * @param q The point to mirror.
 * @param x The mirror plane.
 *
 * @return Mirrored <code>q</code>.
 */
const Vector3 mirror(const Vector3& q, const Plane3& x);

#endif // #ifndef GEOMETRY_PLANE3_H_INCLUDED
