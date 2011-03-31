/**
 * @file geometry/plane2.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/plane2.h>

#include <geometry/math.h>

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

void Plane2::swap(Plane2& other)
{
    normal.swap(other.normal);
    Math::swap(constant, other.constant);
}

float separation(const Plane2& x, const Vector2& q)
{
    return dot(q, x.normal) - x.constant;
}

const Vector2 closestPoint(const Plane2& x, const Vector2& q)
{
    return q - separation(x, q) * x.normal;
}

const Vector2 mirror(const Vector2& q, const Plane2& x)
{
    return q - 2.0f * separation(x, q) * x.normal;
}
