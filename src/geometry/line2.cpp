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

void Line2::swap(Line2& other)
{
    point.swap(other.point);
    direction.swap(other.direction);
}

float distance(const Line2& x, const Vector2& q)
{
    return distance(closestPoint(x, q), q);
}

float sqrDistance(const Line2& x, const Vector2& q)
{
    return sqrDistance(closestPoint(x, q), q);
}

const Vector2 closestPoint(const Line2& x, const Vector2& q)
{
    // distance to q from a point on the line along line direction
    const float d = dot(q, x.direction) - dot(x.point, x.direction);

    return x.point + d * x.direction;
}
