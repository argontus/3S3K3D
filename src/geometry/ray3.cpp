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

void Ray3::swap(Ray3& other)
{
    origin.swap(other.origin);
    direction.swap(other.direction);
}

float distance(const Ray3& x, const Vector3& q)
{
    return distance(closestPoint(x, q), q);
}

float sqrDistance(const Ray3& x, const Vector3& q)
{
    return sqrDistance(closestPoint(x, q), q);
}

const Vector3 closestPoint(const Ray3& x, const Vector3& q)
{
    // distance to q from ray origin along ray direction
    const float d = dot(q, x.direction) - dot(x.origin, x.direction);

    // test if point q is closest to the ray origin
    if (d <= 0.0f)
    {
        return x.origin;
    }

    return x.origin + d * x.direction;
}
