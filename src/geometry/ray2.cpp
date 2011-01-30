/**
 * @file geometry/ray2.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/ray2.h>

Ray2::Ray2()
{
    // ...
}

Ray2::Ray2(const Vector2& origin, const Vector2& direction)
:   origin(origin),
    direction(direction)
{
    // ...
}

const Vector2 Ray2::closestPointTo(const Vector2& q) const
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

float Ray2::distanceTo(const Vector2& q) const
{
    return distance(closestPointTo(q), q);
}

float Ray2::sqrDistanceTo(const Vector2& q) const
{
    return sqrDistance(closestPointTo(q), q);
}

void Ray2::swap(Ray2& other)
{
    origin.swap(other.origin);
    direction.swap(other.direction);
}
