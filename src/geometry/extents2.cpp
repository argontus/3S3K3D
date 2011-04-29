/**
 * @file geometry/extents2.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/extents2.h>

#include <geometry/circle.h>
#include <geometry/interval.h>
#include <geometry/math.h>
#include <geometry/transform2.h>

Extents2::Extents2()
{
    clear();
}

Extents2::Extents2(const Vector2& min, const Vector2& max)
:   min(min),
    max(max)
{
    // ...
}

void Extents2::clear()
{
    min.x = min.y = 1.0f;
    max.x = max.y = 0.0f;
}

void Extents2::enclose(const Vector2& q)
{
    if (isEmpty())
    {
        min = max = q;
        return;
    }

    if (q.x < min.x) min.x = q.x;
    if (max.x < q.x) max.x = q.x;

    if (q.y < min.y) min.y = q.y;
    if (max.y < q.y) max.y = q.y;
}

void Extents2::enclose(const Extents2& other)
{
    if (other.isEmpty())
    {
        return;
    }

    if (isEmpty())
    {
        *this = other;
        return;
    }

    if (other.min.x < min.x) min.x = other.min.x;
    if (max.x < other.max.x) max.x = other.max.x;

    if (other.min.y < min.y) min.y = other.min.y;
    if (max.y < other.max.y) max.y = other.max.y;
}

bool Extents2::isEmpty() const
{
    return max.x < min.x || max.y < min.y;
}

bool Extents2::contains(const Extents2& other) const
{
    return min.x <= other.min.x
    &&     min.y <= other.min.y
    &&     max.x >= other.max.x
    &&     max.y >= other.max.y;
}

void Extents2::swap(Extents2& other)
{
    min.swap(other.min);
    max.swap(other.max);
}

bool intersect(const Extents2& a, const Circle& b)
{
    if (a.isEmpty())
    {
        return false;
    }

    const float sqrRadius = b.radius * b.radius;

    return sqrDistance(closestPoint(a, b.center), b.center) <= sqrRadius;
}

bool intersect(const Extents2& a, const Extents2& b)
{
    if (a.isEmpty() || b.isEmpty())
    {
        return false;
    }

    return b.min.x <= a.max.x && a.min.x <= b.max.x
        && b.min.y <= a.max.y && a.min.y <= b.max.y;
}

const Vector2 closestPoint(const Extents2& x, const Vector2& q)
{
    GEOMETRY_RUNTIME_ASSERT(x.isEmpty() == false);

    return Vector2(
        Math::clamp(q.x, x.min.x, x.max.x),
        Math::clamp(q.y, x.min.y, x.max.y)
    );
}

const Interval interval(const Extents2& x, const Vector2& axis)
{
    if (x.isEmpty())
    {
        // return an empty interval
        return Interval();
    }

    // This optimization is based on the fact that if x is not empty, then all
    // minimum extents are less than or equal to their corresponding maximum
    // extents.

    Interval interval(0.0f, 0.0f);

    if (axis.x >= 0.0f)
    {
        interval.min += axis.x * x.min.x;
        interval.max += axis.x * x.max.x;
    }
    else
    {
        interval.min += axis.x * x.max.x;
        interval.max += axis.x * x.min.x;
    }

    if (axis.y >= 0.0f)
    {
        interval.min += axis.y * x.min.y;
        interval.max += axis.y * x.max.y;
    }
    else
    {
        interval.min += axis.y * x.max.y;
        interval.max += axis.y * x.min.y;
    }

    return interval;
}

const Extents2 transform(const Extents2& x, const Transform2& t)
{
    // TODO: could be optimized, see Real-Time Collision Detection by Christer
    // Ericson, 4.2.6 AABB Recomputed from Rotated AABB

    if (x.isEmpty())
    {
        return x;
    }

    Vector2 vertices[] = {
        Vector2(x.min.x, x.min.y),
        Vector2(x.min.x, x.max.y),
        Vector2(x.max.x, x.min.y),
        Vector2(x.max.x, x.max.y)
    };

    transform(vertices, vertices + 4, vertices, t);

    return Extents2(vertices, vertices + 4);
}
