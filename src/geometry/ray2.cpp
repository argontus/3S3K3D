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

void Ray2::swap(Ray2& other)
{
    origin.swap(other.origin);
    direction.swap(other.direction);
}

float distance(const Ray2& x, const Vector2& q)
{
    return distance(closestPoint(x, q), q);
}

float sqrDistance(const Ray2& x, const Vector2& q)
{
    return sqrDistance(closestPoint(x, q), q);
}

const Vector2 closestPoint(const Ray2& x, const Vector2& q)
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
