/**
 * @file geometry/linesegment3.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/linesegment3.h>

LineSegment3::LineSegment3()
{
    // ...
}

LineSegment3::LineSegment3(const Vector3& startPoint, const Vector3& endPoint)
:   startPoint(startPoint),
    endPoint(endPoint)
{
    // ...
}

const Vector3 LineSegment3::closestPointTo(const Vector3& q) const
{
    // See Real-Time Collision Detection by Christer Ericson, 5.1.2 Closest
    // Point on Line Segment to Point.

    const Vector3 ab = endPoint - startPoint;
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

float LineSegment3::distanceTo(const Vector3& q) const
{
    return distance(closestPointTo(q), q);
}

float LineSegment3::sqrDistanceTo(const Vector3& q) const
{
    return sqrDistance(closestPointTo(q), q);
}

void LineSegment3::swap(LineSegment3& other)
{
    startPoint.swap(other.startPoint);
    endPoint.swap(other.endPoint);
}
