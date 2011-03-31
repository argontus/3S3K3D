/**
 * @file geometry/sphere.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/sphere.h>

#include <geometry/math.h>

Sphere::Sphere()
{
    // ...
}

Sphere::Sphere(const Vector3& center, const float radius)
:   center(center),
    radius(radius)
{
    // ...
}

void Sphere::swap(Sphere& other)
{
    center.swap(other.center);
    Math::swap(radius, other.radius);
}
