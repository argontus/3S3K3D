/**
 * @file geometry/plane2.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/plane2.h>

// TODO: get rid of this #include
#include <algorithm>

Plane2::Plane2()
{
    // ...
}

Plane2::Plane2(const Vector2& normal, const float constant)
:   normal(normal),
    constant(constant)
{
    // ...
}

Plane2::Plane2(const Vector2& normal, const Vector2& q)
:   normal(normal),
    constant(dot(q, normal))
{
    // ...
}

const Vector2 Plane2::closestPointTo(const Vector2& q) const
{
    return q - distanceTo(q) * normal;
}

float Plane2::distanceTo(const Vector2& q) const
{
    return dot(q, normal) - constant;
}

void Plane2::swap(Plane2& other)
{
    normal.swap(other.normal);
    std::swap(constant, other.constant);
}

const Vector2 mirror(const Vector2& q, const Plane2& plane)
{
    return q - 2.0f * plane.distanceTo(q) * plane.normal;
}
