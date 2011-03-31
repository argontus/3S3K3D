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

void LineSegment3::swap(LineSegment3& other)
{
    startPoint.swap(other.startPoint);
    endPoint.swap(other.endPoint);
}

float distance(const LineSegment3& x, const Vector3& q)
{
    return distance(closestPoint(x, q), q);
}

float sqrDistance(const LineSegment3& x, const Vector3& q)
{
    return sqrDistance(closestPoint(x, q), q);
}

const Vector3 closestPoint(const LineSegment3& x, const Vector3& q)
{
    // See Real-Time Collision Detection by Christer Ericson, 5.1.2 Closest
    // Point on Line Segment to Point.

    const Vector3 ab = x.endPoint - x.startPoint;
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
