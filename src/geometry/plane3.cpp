/**
 * @file geometry/plane3.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/plane3.h>

#include <geometry/line3.h>
#include <geometry/math.h>

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

void Plane3::swap(Plane3& other)
{
    normal.swap(other.normal);
    Math::swap(constant, other.constant);
}

bool intersect(const Plane3& plane, const Line3& line, float* const t)
{
    const float divisor = dot(line.direction, plane.normal);

    // TODO: use tolerances instead of absolute values?
    if (divisor == 0.0f)
    {
        return false;
    }

    if (t != 0)
    {
        *t = -separation(plane, line.point) / divisor;
    }

    return true;
}

float separation(const Plane3& x, const Vector3& q)
{
    return dot(q, x.normal) - x.constant;
}

const Vector3 closestPoint(const Plane3& x, const Vector3& q)
{
    return q - separation(x, q) * x.normal;
}

const Vector3 mirror(const Vector3& q, const Plane3& x)
{
    return q - 2.0f * separation(x, q) * x.normal;
}
