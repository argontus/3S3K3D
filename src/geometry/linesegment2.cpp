/**
 * @file geometry/linesegment2.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/linesegment2.h>

LineSegment2::LineSegment2()
{
    // ...
}

LineSegment2::LineSegment2(const Vector2& startPoint, const Vector2& endPoint)
:   startPoint(startPoint),
    endPoint(endPoint)
{
    // ...
}

void LineSegment2::swap(LineSegment2& other)
{
    startPoint.swap(other.startPoint);
    endPoint.swap(other.endPoint);
}

float distance(const LineSegment2& x, const Vector2& q)
{
    return distance(closestPoint(x, q), q);
}

float sqrDistance(const LineSegment2& x, const Vector2& q)
{
    return sqrDistance(closestPoint(x, q), q);
}

const Vector2 closestPoint(const LineSegment2& x, const Vector2& q)
{
    // See Real-Time Collision Detection by Christer Ericson, 5.1.2 Closest
    // Point on Line Segment to Point.

    const Vector2 ab = x.endPoint - x.startPoint;
    const float t = dot(q - x.startPoint, ab);

    if (t <= 0.0f)
    {
        return x.startPoint;
    }

    const float divisor = dot(ab, ab);

    if (t >= divisor)
    {
        return x.endPoint;
    }

    return x.startPoint + (t / divisor) * ab;
}
