/**
 * @file geometry/plane3.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/plane3.h>

#include <algorithm>

Plane3::Plane3()
{
    // ...
}

Plane3::Plane3(const Vector3& normal, const float constant)
:   normal(normal),
    constant(constant)
{
    // ...
}

Plane3::Plane3(const Vector3& normal, const Vector3& q)
:   normal(normal),
    constant(dot(q, normal))
{
    // ...
}

Plane3::Plane3(const Vector3& a, const Vector3& b, const Vector3& c)
{
    normal = cross(b - a, c - a);
    normal.normalize();
    constant = dot(a, normal);
}

const Vector3 Plane3::closestPointTo(const Vector3& q) const
{
    return q - distanceTo(q) * normal;
}

float Plane3::distanceTo(const Vector3& q) const
{
    return dot(q, normal) - constant;
}

void Plane3::swap(Plane3& other)
{
    normal.swap(other.normal);
    std::swap(constant, other.constant);
}
