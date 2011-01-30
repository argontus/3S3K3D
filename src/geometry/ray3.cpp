/**
 * @file geometry/ray3.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/ray3.h>

Ray3::Ray3()
{
    // ...
}

Ray3::Ray3(const Vector3& origin, const Vector3& direction)
:   origin(origin),
    direction(direction)
{
    // ...
}

const Vector3 Ray3::closestPointTo(const Vector3& q) const
{
    // distance to q from ray origin along ray direction
    const float d = dot(q, direction) - dot(origin, direction);

    // test if point q is closest to the ray origin
    if (d <= 0.0f)
    {
        return origin;
    }

    return origin + d * direction;
}

float Ray3::distanceTo(const Vector3& q) const
{
    return distance(closestPointTo(q), q);
}

float Ray3::sqrDistanceTo(const Vector3& q) const
{
    return sqrDistance(closestPointTo(q), q);
}

void Ray3::swap(Ray3& other)
{
    origin.swap(other.origin);
    direction.swap(other.direction);
}
