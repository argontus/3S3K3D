/**
 * @file geometry/line2.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/line2.h>

Line2::Line2()
{
    // ...
}

Line2::Line2(const Vector2& point, const Vector2& direction)
:   point(point),
    direction(direction)
{
    // ...
}

const Vector2 Line2::closestPointTo(const Vector2& q) const
{
    // distance to q from a point on this line along line direction
    const float d = dot(q, direction) - dot(point, direction);

    return point + d * direction;
}

float Line2::distanceTo(const Vector2& q) const
{
    return distance(closestPointTo(q), q);
}

float Line2::sqrDistanceTo(const Vector2& q) const
{
    return sqrDistance(closestPointTo(q), q);
}

void Line2::swap(Line2& other)
{
    point.swap(other.point);
    direction.swap(other.direction);
}
