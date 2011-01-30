/**
 * @file geometry/extents2.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/extents2.h>

#include <limits>

#include <geometry/transform2.h>

Extents2::Extents2()
{
    clear();
}

Extents2::Extents2(
    const float xMin, const float yMin,
    const float xMax, const float yMax)
:   min(xMin, yMin),
    max(xMax, yMax)
{
    // ...
}

Extents2::Extents2(const Vector2& min, const Vector2& max)
:   min(min),
    max(max)
{
    // ...
}

void Extents2::clear()
{
    min.x = min.y = std::numeric_limits<float>::max();
    max.x = max.y = -std::numeric_limits<float>::max();
}

bool Extents2::isEmpty() const
{
    return max.x < min.x || max.y < min.y;
}

float Extents2::xLength() const
{
    return max.x - min.x;
}

float Extents2::yLength() const
{
    return max.y - min.y;
}

bool Extents2::contains(const Vector2& point) const
{
    return min.x <= point.x && point.x <= max.x
        && min.y <= point.y && point.y <= max.y;
}

bool Extents2::contains(const Extents2& other) const
{
    if (isEmpty() || other.isEmpty())
    {
        return false;
    }

    return min.x <= other.min.x && other.max.x <= max.x
        && min.y <= other.min.y && other.max.y <= max.y;
}

bool Extents2::intersects(const Extents2& other) const
{
    if (isEmpty() || other.isEmpty())
    {
        return false;
    }

    return other.min.x < max.x && min.x < other.max.x
        && other.min.y < max.y && min.y < other.max.y;
}

void Extents2::growToContain(const Vector2& point)
{
    if (point.x < min.x) min.x = point.x;
    if (max.x < point.x) max.x = point.x;

    if (point.y < min.y) min.y = point.y;
    if (max.y < point.y) max.y = point.y;
}

void Extents2::growToContain(const Extents2& other)
{
    if (other.min.x < min.x) min.x = other.min.x;
    if (max.x < other.max.x) max.x = other.max.x;

    if (other.min.y < min.y) min.y = other.min.y;
    if (max.y < other.max.y) max.y = other.max.y;
}

void Extents2::transformBy(const Transform2& transform)
{
    // TODO: could be optimized, see Real-Time Collision Detection by Christer
    // Ericson, 4.2.6 AABB Recomputed from Rotated AABB

    if (isEmpty())
    {
        return;
    }

    Vector2 vertices[] = {
        Vector2(min.x, min.y),
        Vector2(min.x, max.y),
        Vector2(max.x, min.y),
        Vector2(max.x, max.y)
    };

    transform.applyForward(vertices, vertices + 4, vertices);
    min = max = vertices[0];

    for (int i = 1; i < 4; ++i)
    {
        growToContain(vertices[i]);
    }
}

void Extents2::translateBy(const Vector2& translation)
{
    if (isEmpty())
    {
        return;
    }

    min += translation;
    max += translation;
}

void Extents2::rotateBy(const Matrix2x2& rotation)
{
    // TODO: could be optimized, see Real-Time Collision Detection by Christer
    // Ericson, 4.2.6 AABB Recomputed from Rotated AABB

    if (isEmpty())
    {
        return;
    }

    Vector2 vertices[] = {
        Vector2(min.x, min.y),
        Vector2(min.x, max.y),
        Vector2(max.x, min.y),
        Vector2(max.x, max.y)
    };

    min = max = product(vertices[0], rotation);

    for (int i = 1; i < 4; ++i)
    {
        growToContain(product(vertices[i], rotation));
    }
}

void Extents2::scaleBy(const float scaling)
{
    if (isEmpty())
    {
        return;
    }

    min *= scaling;
    max *= scaling;
}

void Extents2::swap(Extents2& other)
{
    min.swap(other.min);
    max.swap(other.max);
}
