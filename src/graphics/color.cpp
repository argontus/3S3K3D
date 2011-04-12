/**
 * @file graphics/color.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/color.h>

#include <algorithm>

#include <geometry/math.h>

#include <graphics/runtimeassert.h>

Color::Color()
{
    // ...
}

Color::Color(const float r, const float g, const float b, const float a)
:   r(r),
    g(g),
    b(b),
    a(a)
{
    // ...
}

Color& Color::operator +=(const Color& c)
{
    r += c.r;
    g += c.g;
    b += c.b;
    a += c.a;
    return *this;
}

Color& Color::operator -=(const Color& c)
{
    r -= c.r;
    g -= c.g;
    b -= c.b;
    a -= c.a;
    return *this;
}

Color& Color::operator *=(const Color& c)
{
    r *= c.r;
    g *= c.g;
    b *= c.b;
    a *= c.a;
    return *this;
}

Color& Color::operator *=(const float k)
{
    r *= k;
    g *= k;
    b *= k;
    a *= k;
    return *this;
}

Color& Color::operator /=(const float k)
{
    // TODO: use tolerances instead of absolute values?
    GRAPHICS_RUNTIME_ASSERT(k != 0.0f);

    r /= k;
    g /= k;
    b /= k;
    a /= k;
    return *this;
}

Color& Color::operator /=(const Color& c)
{
    // TODO: use tolerances instead of absolute values?
    GRAPHICS_RUNTIME_ASSERT(c.r != 0.0f);
    GRAPHICS_RUNTIME_ASSERT(c.g != 0.0f);
    GRAPHICS_RUNTIME_ASSERT(c.b != 0.0f);
    GRAPHICS_RUNTIME_ASSERT(c.a != 0.0f);

    r /= c.r;
    g /= c.g;
    b /= c.b;
    a /= c.a;
    return *this;
}

float* Color::data()
{
    return &r;
}

const float* Color::data() const
{
    return &r;
}

void Color::swap(Color& other)
{
    std::swap(r, other.r);
    std::swap(g, other.g);
    std::swap(b, other.b);
    std::swap(a, other.a);
}

const Color operator +(const Color& a, const Color& b)
{
    return Color(
        a.r + b.r,
        a.g + b.g,
        a.b + b.b,
        a.a + b.a
    );
}

const Color operator -(const Color& a, const Color& b)
{
    return Color(
        a.r - b.r,
        a.g - b.g,
        a.b - b.b,
        a.a - b.a
    );
}

const Color operator -(const Color& c)
{
    return Color(
        -c.r,
        -c.g,
        -c.b,
        -c.a
    );
}

const Color operator *(const Color& a, const Color& b)
{
    return Color(
        a.r * b.r,
        a.g * b.g,
        a.b * b.b,
        a.a * b.a
    );
}

const Color operator *(const float k, const Color& c)
{
    return Color(
        k * c.r,
        k * c.g,
        k * c.b,
        k * c.a
    );
}

const Color operator *(const Color& c, const float k)
{
    return Color(
        k * c.r,
        k * c.g,
        k * c.b,
        k * c.a
    );
}

const Color operator /(const Color& c, const float k)
{
    // TODO: use tolerances instead of absolute values?
    GRAPHICS_RUNTIME_ASSERT(k != 0.0f);

    return Color(
        c.r / k,
        c.g / k,
        c.b / k,
        c.a / k
    );
}

const Color operator /(const Color& a, const Color& b)
{
    // TODO: use tolerances instead of absolute values?
    GRAPHICS_RUNTIME_ASSERT(b.r != 0.0f);
    GRAPHICS_RUNTIME_ASSERT(b.g != 0.0f);
    GRAPHICS_RUNTIME_ASSERT(b.b != 0.0f);
    GRAPHICS_RUNTIME_ASSERT(b.a != 0.0f);

    return Color(
        a.r / b.r,
        a.g / b.g,
        a.b / b.b,
        a.a / b.a
    );
}

const Color clamp(const Color& c, const float min, const float max)
{
    return Color(
        Math::clamp(c.r, min, max),
        Math::clamp(c.g, min, max),
        Math::clamp(c.b, min, max),
        Math::clamp(c.a, min, max)
    );
}

const Color mix(const Color& a, const Color& b, const float t)
{
    return a + t * (b - a);
}
