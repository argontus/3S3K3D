/**
 * @file geometry/sphere.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_SPHERE_H_INCLUDED
#define GEOMETRY_SPHERE_H_INCLUDED

#include <geometry/vector3.h>

class Interval;

/**
 * Describes a circle.
 */
class Sphere
{
public:
    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

    /**
     * Default constructor, constructs an uninitialized sphere.
     */
    Sphere();

    /**
     * Constructor.
     *
     * @param center Center point.
     * @param radius Radius.
     */
    Sphere(const Vector3& center, float radius);

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(Sphere& other);

    Vector3 center; ///< Center point.
    float radius;   ///< Radius.
};

/**
 * Calculates the interval of <code>x</code> along <code>axis</code>. If
 * <code>x.radius < 0.0f</code>, the returned interval will be empty.
 *
 * @param x The sphere whose interval is to be calculated.
 * @param axis The axis along which the interval is to be calculated.
 *
 * @return The calculated interval.
 */
const Interval interval(const Sphere& x, const Vector3& axis);

#endif // #ifndef GEOMETRY_SPHERE_H_INCLUDED
