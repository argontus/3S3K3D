/**
 * @file geometry/interval.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/interval.h>

// TODO: get rid of these #includes
#include <algorithm>
#include <limits>

Interval::Interval()
:   min(std::numeric_limits<float>::max()),
    max(-std::numeric_limits<float>::max())
{
    // ...
}

Interval::Interval(const float min, const float max)
:   min(min),
    max(max)
{
    // ...
}

void Interval::clear()
{
    min = std::numeric_limits<float>::max();
    max = -std::numeric_limits<float>::max();
}

bool Interval::isEmpty() const
{
    return max < min;
}

float Interval::length() const
{
    return max - min;
}

bool Interval::contains(const float value) const
{
    return min <= value && value <= max;
}

bool Interval::contains(const Interval& other) const
{
    if (isEmpty() || other.isEmpty())
    {
        return false;
    }

    return min <= other.min && other.max <= max;
}

bool Interval::intersects(const Interval& other) const
{
    if (isEmpty() || other.isEmpty())
    {
        return false;
    }

    return other.min < max && min < other.max;
}

void Interval::growToContain(const float value)
{
    if (value < min)
    {
        min = value;
    }

    if (max < value)
    {
        max = value;
    }
}

void Interval::growToContain(const Interval& other)
{
    if (other.min < min)
    {
        min = other.min;
    }

    if (max < other.max)
    {
        max = other.max;
    }
}

void Interval::swap(Interval& other)
{
    std::swap(min, other.min);
    std::swap(max, other.max);
}
