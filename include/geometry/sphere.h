/**
 * @file geometry/sphere.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_SPHERE_H_INCLUDED
#define GEOMETRY_SPHERE_H_INCLUDED

#include <geometry/vector3.h>

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

#endif // #ifndef GEOMETRY_SPHERE_H_INCLUDED
