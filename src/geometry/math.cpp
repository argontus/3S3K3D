/**
 * @file geometry/math.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/math.h>

#include <cmath>

namespace Math {

float pi()
{
    // constant pi
    static const float k = static_cast<float>(std::atan(1.0) * 4.0);

    return k;
}

float halfPi()
{
    // constant pi/2
    static const float k = static_cast<float>(std::atan(1.0) * 2.0);

    return k;
}

float twoPi()
{
    // constant 2*pi
    static const float k = static_cast<float>(std::atan(1.0) * 8.0);

    return k;
}

float degrees(const float radians)
{
    // constant 180/pi
    static const float k = static_cast<float>(45.0 / std::atan(1.0));

    return k * radians;
}

float radians(const float degrees)
{
    // constant pi/180
    static const float k = static_cast<float>(std::atan(1.0) / 45.0);

    return k * degrees;
}

float cos(const float angle)
{
    return std::cos(angle);
}

float sin(const float angle)
{
    return std::sin(angle);
}

float tan(const float angle)
{
    GEOMETRY_RUNTIME_ASSERT(std::cos(angle) != 0.0f);
    return std::tan(angle);
}

float acos(const float value)
{
    if (value > -1.0f)
    {
        if (value < 1.0f)
        {
            return std::acos(value);
        }

        return 0.0f;
    }

    return pi();
}

float asin(const float value)
{
    if (value > -1.0f)
    {
        if (value < 1.0f)
        {
            return std::asin(value);
        }

        return halfPi();
    }

    return -halfPi();
}

float atan(const float value)
{
    return std::atan(value);
}

float atan2(const float y, const float x)
{
    return std::atan2(y, x);
}

float sqr(const float value)
{
    return value * value;
}

float sqrt(const float value)
{
    GEOMETRY_RUNTIME_ASSERT(value >= 0.0f);
    return std::sqrt(value);
}

float inverseSqrt(const float value)
{
    GEOMETRY_RUNTIME_ASSERT(value > 0.0f);
    return 1.0f / std::sqrt(value);
}

float abs(const float value)
{
    return value < 0.0f ? -value : value;
}

float ceil(const float value)
{
    return std::ceil(value);
}

float floor(const float value)
{
    return std::floor(value);
}

float mix(const float a, const float b, const float t)
{
    return a + t * (b - a);
}

float wrapTo2Pi(float value)
{
    value += twoPi();
    return value - floor(value / twoPi()) * twoPi();
}

} // namespace Math
