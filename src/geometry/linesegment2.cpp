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

const Vector2 LineSegment2::closestPointTo(const Vector2& q) const
{
    // See Real-Time Collision Detection by Christer Ericson, 5.1.2 Closest
    // Point on Line Segment to Point.

    const Vector2 ab = endPoint - startPoint;
    const float t = dot(q - startPoint, ab);

    if (t <= 0.0f)
    {
        return startPoint;
    }

    const float denom = dot(ab, ab);

    if (t >= denom)
    {
        return endPoint;
    }

    return startPoint + (t / denom) * ab;
}

float LineSegment2::distanceTo(const Vector2& q) const
{
    return distance(closestPointTo(q), q);
}

float LineSegment2::sqrDistanceTo(const Vector2& q) const
{
    return sqrDistance(closestPointTo(q), q);
}

void LineSegment2::swap(LineSegment2& other)
{
    startPoint.swap(other.startPoint);
    endPoint.swap(other.endPoint);
}
