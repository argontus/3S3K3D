/**
 * @file geometry/extents3.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/extents3.h>

// TODO: get rid of this #include
#include <limits>

#include <geometry/interval.h>
#include <geometry/transform3.h>

Extents3::Extents3()
{
    clear();
}

Extents3::Extents3(
    const float xMin, const float yMin, const float zMin,
    const float xMax, const float yMax, const float zMax)
:   min(xMin, yMin, zMin),
    max(xMax, yMax, zMax)
{
    // ...
}

Extents3::Extents3(const Vector3& min, const Vector3& max)
:   min(min),
    max(max)
{
    // ...
}

void Extents3::clear()
{
    min.x = min.y = min.z = std::numeric_limits<float>::max();
    max.x = max.y = max.z = -std::numeric_limits<float>::max();
}

bool Extents3::isEmpty() const
{
    return max.x < min.x || max.y < min.y || max.z < min.z;
}

float Extents3::xLength() const
{
    return max.x - min.x;
}

float Extents3::yLength() const
{
    return max.y - min.y;
}

float Extents3::zLength() const
{
    return max.z - min.z;
}

bool Extents3::contains(const Vector3& point) const
{
    return min.x <= point.x && point.x <= max.x
        && min.y <= point.y && point.y <= max.y
        && min.z <= point.z && point.z <= max.z;
}

bool Extents3::contains(const Extents3& other) const
{
    if (isEmpty() || other.isEmpty())
    {
        return false;
    }

    return min.x <= other.min.x && other.max.x <= max.x
        && min.y <= other.min.y && other.max.y <= max.y
        && min.z <= other.min.z && other.max.z <= max.z;
}

bool Extents3::intersects(const Extents3& other) const
{
    if (isEmpty() || other.isEmpty())
    {
        return false;
    }

    return other.min.x < max.x && min.x < other.max.x
        && other.min.y < max.y && min.y < other.max.y
        && other.min.z < max.y && min.z < other.max.z;
}

void Extents3::growToContain(const Vector3& point)
{
    if (point.x < min.x) min.x = point.x;
    if (max.x < point.x) max.x = point.x;

    if (point.y < min.y) min.y = point.y;
    if (max.y < point.y) max.y = point.y;

    if (point.z < min.z) min.z = point.z;
    if (max.z < point.z) max.z = point.z;
}

void Extents3::growToContain(const Extents3& other)
{
    if (other.min.x < min.x) min.x = other.min.x;
    if (max.x < other.max.x) max.x = other.max.x;

    if (other.min.y < min.y) min.y = other.min.y;
    if (max.y < other.max.y) max.y = other.max.y;

    if (other.min.z < min.z) min.z = other.min.z;
    if (max.z < other.max.z) max.z = other.max.z;
}

const Interval Extents3::intervalAlong(const Vector3& axis) const
{
    if (isEmpty())
    {
        // return an empty interval
        return Interval();
    }

    // This optimization is based on the fact that if this AABB is not empty,
    // then all minimum extents are less than or equal to their corresponding
    // maximum extents.

    Interval interval(0.0f, 0.0f);

    if (axis.x >= 0.0f)
    {
        interval.min += axis.x * min.x;
        interval.max += axis.x * max.x;
    }
    else
    {
        interval.min += axis.x * max.x;
        interval.max += axis.x * min.x;
    }

    if (axis.y >= 0.0f)
    {
        interval.min += axis.y * min.y;
        interval.max += axis.y * max.y;
    }
    else
    {
        interval.min += axis.y * max.y;
        interval.max += axis.y * min.y;
    }

    if (axis.z >= 0.0f)
    {
        interval.min += axis.z * min.z;
        interval.max += axis.z * max.z;
    }
    else
    {
        interval.min += axis.z * max.z;
        interval.max += axis.z * min.z;
    }

    return interval;
}

void Extents3::transformBy(const Transform3& transform)
{
    // TODO: could be optimized, see Real-Time Collision Detection by Christer
    // Ericson, 4.2.6 AABB Recomputed from Rotated AABB

    if (isEmpty())
    {
        return;
    }

    Vector3 vertices[] = {
        Vector3(min.x, min.y, min.z),
        Vector3(min.x, min.y, max.z),
        Vector3(min.x, max.y, min.z),
        Vector3(min.x, max.y, max.z),
        Vector3(max.x, min.y, min.z),
        Vector3(max.x, min.y, max.z),
        Vector3(max.x, max.y, min.z),
        Vector3(max.x, max.y, max.z)
    };

    transform.applyForward(vertices, vertices + 8, vertices);
    min = max = vertices[0];

    for (int i = 1; i < 8; ++i)
    {
        growToContain(vertices[i]);
    }
}

void Extents3::translateBy(const Vector3& translation)
{
    if (isEmpty())
    {
        return;
    }

    min += translation;
    max += translation;
}

void Extents3::rotateBy(const Matrix3x3& rotation)
{
    // TODO: could be optimized, see Real-Time Collision Detection by Christer
    // Ericson, 4.2.6 AABB Recomputed from Rotated AABB

    if (isEmpty())
    {
        return;
    }

    Vector3 vertices[] = {
        Vector3(min.x, min.y, min.z),
        Vector3(min.x, min.y, max.z),
        Vector3(min.x, max.y, min.z),
        Vector3(min.x, max.y, max.z),
        Vector3(max.x, min.y, min.z),
        Vector3(max.x, min.y, max.z),
        Vector3(max.x, max.y, min.z),
        Vector3(max.x, max.y, max.z)
    };

    min = max = product(vertices[0], rotation);

    for (int i = 1; i < 8; ++i)
    {
        growToContain(product(vertices[i], rotation));
    }
}

void Extents3::scaleBy(const float scaling)
{
    GEOMETRY_RUNTIME_ASSERT(scaling > 0.0f);

    if (isEmpty())
    {
        return;
    }

    min *= scaling;
    max *= scaling;
}

void Extents3::swap(Extents3& other)
{
    min.swap(other.min);
    max.swap(other.max);
}
