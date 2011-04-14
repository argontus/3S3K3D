/**
 * @file graphics/color4.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/color4.h>

#include <geometry/math.h>

#include <graphics/runtimeassert.h>

Color4::Color4()
{
    // ...
}

Color4::Color4(const float r, const float g, const float b, const float a)
:   r(r),
    g(g),
    b(b),
    a(a)
{
    // ...
}

Color4& Color4::operator +=(const Color4& c)
{
    r += c.r;
    g += c.g;
    b += c.b;
    a += c.a;
    return *this;
}

Color4& Color4::operator -=(const Color4& c)
{
    r -= c.r;
    g -= c.g;
    b -= c.b;
    a -= c.a;
    return *this;
}

Color4& Color4::operator *=(const Color4& c)
{
    r *= c.r;
    g *= c.g;
    b *= c.b;
    a *= c.a;
    return *this;
}

Color4& Color4::operator *=(const float k)
{
    r *= k;
    g *= k;
    b *= k;
    a *= k;
    return *this;
}

Color4& Color4::operator /=(const float k)
{
    // TODO: use tolerances instead of absolute values?
    GRAPHICS_RUNTIME_ASSERT(k != 0.0f);

    r /= k;
    g /= k;
    b /= k;
    a /= k;
    return *this;
}

Color4& Color4::operator /=(const Color4& c)
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

float* Color4::data()
{
    return &r;
}

const float* Color4::data() const
{
    return &r;
}

void Color4::swap(Color4& other)
{
    Math::swap(r, other.r);
    Math::swap(g, other.g);
    Math::swap(b, other.b);
    Math::swap(a, other.a);
}

const Color4 operator +(const Color4& a, const Color4& b)
{
    return Color4(
        a.r + b.r,
        a.g + b.g,
        a.b + b.b,
        a.a + b.a
    );
}

const Color4 operator -(const Color4& a, const Color4& b)
{
    return Color4(
        a.r - b.r,
        a.g - b.g,
        a.b - b.b,
        a.a - b.a
    );
}

const Color4 operator -(const Color4& c)
{
    return Color4(
        -c.r,
        -c.g,
        -c.b,
        -c.a
    );
}

const Color4 operator *(const Color4& a, const Color4& b)
{
    return Color4(
        a.r * b.r,
        a.g * b.g,
        a.b * b.b,
        a.a * b.a
    );
}

const Color4 operator *(const float k, const Color4& c)
{
    return Color4(
        k * c.r,
        k * c.g,
        k * c.b,
        k * c.a
    );
}

const Color4 operator *(const Color4& c, const float k)
{
    return Color4(
        k * c.r,
        k * c.g,
        k * c.b,
        k * c.a
    );
}

const Color4 operator /(const Color4& c, const float k)
{
    // TODO: use tolerances instead of absolute values?
    GRAPHICS_RUNTIME_ASSERT(k != 0.0f);

    return Color4(
        c.r / k,
        c.g / k,
        c.b / k,
        c.a / k
    );
}

const Color4 operator /(const Color4& a, const Color4& b)
{
    // TODO: use tolerances instead of absolute values?
    GRAPHICS_RUNTIME_ASSERT(b.r != 0.0f);
    GRAPHICS_RUNTIME_ASSERT(b.g != 0.0f);
    GRAPHICS_RUNTIME_ASSERT(b.b != 0.0f);
    GRAPHICS_RUNTIME_ASSERT(b.a != 0.0f);

    return Color4(
        a.r / b.r,
        a.g / b.g,
        a.b / b.b,
        a.a / b.a
    );
}

const Color4 clamp(const Color4& c, const float min, const float max)
{
    return Color4(
        Math::clamp(c.r, min, max),
        Math::clamp(c.g, min, max),
        Math::clamp(c.b, min, max),
        Math::clamp(c.a, min, max)
    );
}

const Color4 mix(const Color4& a, const Color4& b, const float t)
{
    return a + t * (b - a);
}
