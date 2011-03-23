/**
 * @file geometry/math.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/math.h>

#include <cfloat>
#include <cmath>

namespace Math {

// mathematical constants

float e()
{
    return M_E;
}

float infinity()
{
    // TODO: return infinity, not the maximum positive value
    return FLT_MAX;
}

float pi()
{
    return M_PI;
}

// angle conversion functions

float degrees(const float radians)
{
    return 180.0 / M_PI * radians;
}

float radians(const float degrees)
{
    return M_PI / 180.0 * degrees;
}

// trigonometry functions

float acos(const float x)
{
    if (x > -1.0f)
    {
        if (x < 1.0f)
        {
            return std::acos(x);
        }

        return 0.0f;
    }

    return pi();
}

float asin(const float x)
{
    if (x > -1.0f)
    {
        if (x < 1.0f)
        {
            return std::asin(x);
        }

        return 0.5f * pi();
    }

    return -0.5f * pi();
}

float atan(const float x)
{
    return std::atan(x);
}

float atan(const float y, const float x)
{
    // TODO: use tolerances instead of absolute values?
    if (x == 0.0f && y == 0.0f)
    {
        return 0.0f;
    }

    return std::atan2(y, x);
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
    // TODO: use tolerances instead of absolute values?
    GEOMETRY_RUNTIME_ASSERT(std::cos(angle) != 0.0f);
    return std::tan(angle);
}

// exponential functions

float exp(const float x)
{
    return std::exp(x);
}

float log(const float x)
{
    // TODO: use tolerances instead of absolute values?
    GEOMETRY_RUNTIME_ASSERT(x > 0.0f);
    return std::log(x);
}

float pow(const float base, const float exponent)
{
    // TODO: use tolerances instead of absolute values?
    GEOMETRY_RUNTIME_ASSERT(base >= 0.0f);
    // TODO: more sanity checks
    return std::pow(base, exponent);
}

float sqr(const float x)
{
    return x * x;
}

float sqrt(const float x)
{
    // TODO: use tolerances instead of absolute values?
    GEOMETRY_RUNTIME_ASSERT(x >= 0.0f);
    return std::sqrt(x);
}

// common functions

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

float mod(const float dividend, const float divisor)
{
    // TODO: use tolerances instead of absolute values?
    GEOMETRY_RUNTIME_ASSERT(divisor != 0.0f);
    return dividend - divisor * floor(dividend / divisor);
}

} // namespace Math
