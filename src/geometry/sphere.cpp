/**
 * @file geometry/sphere.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/sphere.h>

#include <geometry/interval.h>
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

const Interval interval(const Sphere& x, const Vector3& axis)
{
    const float d = dot(x.center, axis);
    return Interval(d - x.radius, d + x.radius);
}
