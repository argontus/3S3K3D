/**
 * @file geometry/plane3.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/plane3.h>

// TODO: get rid of this #include
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
    // initializer list is not used to avoid a hard-to-find bug in case the
    // declaration order of Plane3::normal and Plane3::constant changes
    normal = normalize(cross(b - a, c - a));
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

const Vector3 mirror(const Vector3& q, const Plane3& plane)
{
    return q - 2.0f * plane.distanceTo(q) * plane.normal;
}
