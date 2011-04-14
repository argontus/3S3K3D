/**
 * @file graphics/color3.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/color3.h>

#include <geometry/math.h>

#include <graphics/runtimeassert.h>

Color3::Color3()
{
    // ...
}

Color3::Color3(const float r, const float g, const float b)
:   r(r),
    g(g),
    b(b)
{
    // ...
}

Color3& Color3::operator +=(const Color3& c)
{
    r += c.r;
    g += c.g;
    b += c.b;
    return *this;
}

Color3& Color3::operator -=(const Color3& c)
{
    r -= c.r;
    g -= c.g;
    b -= c.b;
    return *this;
}

Color3& Color3::operator *=(const Color3& c)
{
    r *= c.r;
    g *= c.g;
    b *= c.b;
    return *this;
}

Color3& Color3::operator *=(const float k)
{
    r *= k;
    g *= k;
    b *= k;
    return *this;
}

Color3& Color3::operator /=(const float k)
{
    // TODO: use tolerances instead of absolute values?
    GRAPHICS_RUNTIME_ASSERT(k != 0.0f);

    r /= k;
    g /= k;
    b /= k;
    return *this;
}

Color3& Color3::operator /=(const Color3& c)
{
    // TODO: use tolerances instead of absolute values?
    GRAPHICS_RUNTIME_ASSERT(c.r != 0.0f);
    GRAPHICS_RUNTIME_ASSERT(c.g != 0.0f);
    GRAPHICS_RUNTIME_ASSERT(c.b != 0.0f);

    r /= c.r;
    g /= c.g;
    b /= c.b;
    return *this;
}

float* Color3::data()
{
    return &r;
}

const float* Color3::data() const
{
    return &r;
}

void Color3::swap(Color3& other)
{
    Math::swap(r, other.r);
    Math::swap(g, other.g);
    Math::swap(b, other.b);
}

const Color3 operator +(const Color3& a, const Color3& b)
{
    return Color3(
        a.r + b.r,
        a.g + b.g,
        a.b + b.b
    );
}

const Color3 operator -(const Color3& a, const Color3& b)
{
    return Color3(
        a.r - b.r,
        a.g - b.g,
        a.b - b.b
    );
}

const Color3 operator -(const Color3& c)
{
    return Color3(
        -c.r,
        -c.g,
        -c.b
    );
}

const Color3 operator *(const Color3& a, const Color3& b)
{
    return Color3(
        a.r * b.r,
        a.g * b.g,
        a.b * b.b
    );
}

const Color3 operator *(const float k, const Color3& c)
{
    return Color3(
        k * c.r,
        k * c.g,
        k * c.b
    );
}

const Color3 operator *(const Color3& c, const float k)
{
    return Color3(
        k * c.r,
        k * c.g,
        k * c.b
    );
}

const Color3 operator /(const Color3& c, const float k)
{
    // TODO: use tolerances instead of absolute values?
    GRAPHICS_RUNTIME_ASSERT(k != 0.0f);

    return Color3(
        c.r / k,
        c.g / k,
        c.b / k
    );
}

const Color3 operator /(const Color3& a, const Color3& b)
{
    // TODO: use tolerances instead of absolute values?
    GRAPHICS_RUNTIME_ASSERT(b.r != 0.0f);
    GRAPHICS_RUNTIME_ASSERT(b.g != 0.0f);
    GRAPHICS_RUNTIME_ASSERT(b.b != 0.0f);

    return Color3(
        a.r / b.r,
        a.g / b.g,
        a.b / b.b
    );
}

const Color3 clamp(const Color3& c, const float min, const float max)
{
    return Color3(
        Math::clamp(c.r, min, max),
        Math::clamp(c.g, min, max),
        Math::clamp(c.b, min, max)
    );
}

const Color3 mix(const Color3& a, const Color3& b, const float t)
{
    return a + t * (b - a);
}
