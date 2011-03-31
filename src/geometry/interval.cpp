/**
 * @file geometry/interval.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/interval.h>

#include <geometry/math.h>

Interval::Interval()
{
    clear();
}

Interval::Interval(const float min, const float max)
:   min(min),
    max(max)
{
    // ...
}

void Interval::clear()
{
    min = 1.0f;
    max = 0.0f;
}

void Interval::enclose(const float k)
{
    if (isEmpty())
    {
        min = max = k;
        return;
    }

    if (k < min) min = k;
    if (max < k) max = k;
}

void Interval::enclose(const Interval& other)
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

    if (other.min < min) min = other.min;
    if (max < other.max) max = other.max;
}

bool Interval::isEmpty() const
{
    return max < min;
}

void Interval::swap(Interval& other)
{
    Math::swap(min, other.min);
    Math::swap(max, other.max);
}
