/**
 * @file geometry/line3.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/line3.h>

Line3::Line3()
{
    // ...
}

Line3::Line3(const Vector3& point, const Vector3& direction)
:   point(point),
    direction(direction)
{
    // ...
}

void Line3::swap(Line3& other)
{
    point.swap(other.point);
    direction.swap(other.direction);
}

float distance(const Line3& x, const Vector3& q)
{
    return distance(closestPoint(x, q), q);
}

float sqrDistance(const Line3& x, const Vector3& q)
{
    return sqrDistance(closestPoint(x, q), q);
}

const Vector3 closestPoint(const Line3& x, const Vector3& q)
{
    // distance to q from a point on the line along line direction
    const float d = dot(q, x.direction) - dot(x.point, x.direction);

    return x.point + d * x.direction;
}
