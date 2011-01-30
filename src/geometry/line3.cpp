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

const Vector3 Line3::closestPointTo(const Vector3& q) const
{
    // distance to q from a point on this line along line direction
    const float d = dot(q, direction) - dot(point, direction);

    return point + d * direction;
}

float Line3::distanceTo(const Vector3& q) const
{
    return distance(closestPointTo(q), q);
}

float Line3::sqrDistanceTo(const Vector3& q) const
{
    return sqrDistance(closestPointTo(q), q);
}

void Line3::swap(Line3& other)
{
    point.swap(other.point);
    direction.swap(other.direction);
}
