/**
 * @file geometry/extents3.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/extents3.h>

#include <geometry/interval.h>
#include <geometry/line3.h>
#include <geometry/math.h>
#include <geometry/plane3.h>
#include <geometry/sphere.h>
#include <geometry/transform3.h>

Extents3::Extents3()
{
    clear();
}

Extents3::Extents3(const Vector3& min, const Vector3& max)
:   min(min),
    max(max)
{
    // ...
}

void Extents3::clear()
{
    min.x = min.y = min.z = 1.0f;
    max.x = max.y = max.z = 0.0f;
}

void Extents3::enclose(const Vector3& q)
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

    if (q.z < min.z) min.z = q.z;
    if (max.z < q.z) max.z = q.z;
}

void Extents3::enclose(const Extents3& other)
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

    if (other.min.z < min.z) min.z = other.min.z;
    if (max.z < other.max.z) max.z = other.max.z;
}

bool Extents3::isEmpty() const
{
    return max.x < min.x || max.y < min.y || max.z < min.z;
}

bool Extents3::contains(const Extents3& other) const
{
    return min.x <= other.min.x
    &&     min.y <= other.min.y
    &&     min.z <= other.min.z
    &&     max.x >= other.max.x
    &&     max.y >= other.max.y
    &&     max.z >= other.max.z;
}

void Extents3::swap(Extents3& other)
{
    min.swap(other.min);
    max.swap(other.max);
}

bool intersect(const Extents3& a, const Extents3& b)
{
    if (a.isEmpty() || b.isEmpty())
    {
        return false;
    }

    return b.min.x <= a.max.x && a.min.x <= b.max.x
        && b.min.y <= a.max.y && a.min.y <= b.max.y
        && b.min.z <= a.max.z && a.min.z <= b.max.z;
}

bool intersect(const Extents3& a, const Sphere& b)
{
    if (a.isEmpty())
    {
        return false;
    }

    const float sqrRadius = b.radius * b.radius;

    return sqrDistance(closestPoint(a, b.center), b.center) <= sqrRadius;
}

bool intersect(
    const Extents3& extents,
    const Line3& line,
    float* const tEnterOut,
    float* const tLeaveOut)
{
    float tEnter = -Math::infinity();
    float tLeave = Math::infinity();

    const Plane3 planes[] = {
        Plane3(Vector3(-1.0f,  0.0f,  0.0f), extents.min),
        Plane3(Vector3( 1.0f,  0.0f,  0.0f), extents.max),
        Plane3(Vector3( 0.0f, -1.0f,  0.0f), extents.min),
        Plane3(Vector3( 0.0f,  1.0f,  0.0f), extents.max),
        Plane3(Vector3( 0.0f,  0.0f, -1.0f), extents.min),
        Plane3(Vector3( 0.0f,  0.0f,  1.0f), extents.max)
    };

    float t;

    for (int i = 0; i < 6; ++i)
    {
        if (intersect(planes[i], line, &t))
        {
            if (dot(line.direction, planes[i].normal) < 0.0f)
            {
                // entering
                if (t > tEnter)
                {
                    tEnter = t;
                }
            }
            else
            {
                // leaving
                if (t < tLeave)
                {
                    tLeave = t;
                }
            }
        }
        else
        {
            if (separation(planes[i], line.point) > 0.0f)
            {
                return false;
            }
        }
    }

    if (tLeave < tEnter)
    {
        return false;
    }

    if (tEnterOut != 0)
    {
        *tEnterOut = tEnter;
    }

    if (tLeaveOut != 0)
    {
        *tLeaveOut = tLeave;
    }

    return true;
}

const Vector3 closestPoint(const Extents3& x, const Vector3& q)
{
    GEOMETRY_RUNTIME_ASSERT(x.isEmpty() == false);

    return Vector3(
        Math::clamp(q.x, x.min.x, x.max.x),
        Math::clamp(q.y, x.min.y, x.max.y),
        Math::clamp(q.z, x.min.z, x.max.z)
    );
}

const Interval interval(const Extents3& x, const Vector3& axis)
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

    if (axis.z >= 0.0f)
    {
        interval.min += axis.z * x.min.z;
        interval.max += axis.z * x.max.z;
    }
    else
    {
        interval.min += axis.z * x.max.z;
        interval.max += axis.z * x.min.z;
    }

    return interval;
}

const Extents3 transform(const Extents3& x, const Transform3& t)
{
    // TODO: could be optimized, see Real-Time Collision Detection by Christer
    // Ericson, 4.2.6 AABB Recomputed from Rotated AABB

    if (x.isEmpty())
    {
        return x;
    }

    Vector3 vertices[] = {
        Vector3(x.min.x, x.min.y, x.min.z),
        Vector3(x.min.x, x.min.y, x.max.z),
        Vector3(x.min.x, x.max.y, x.min.z),
        Vector3(x.min.x, x.max.y, x.max.z),
        Vector3(x.max.x, x.min.y, x.min.z),
        Vector3(x.max.x, x.min.y, x.max.z),
        Vector3(x.max.x, x.max.y, x.min.z),
        Vector3(x.max.x, x.max.y, x.max.z)
    };

    transform(vertices, vertices + 8, vertices, t);

    return Extents3(vertices, vertices + 8);
}
