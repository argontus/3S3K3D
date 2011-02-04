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
    GRAPHICS_RUNTIME_ASSERT(k != 0.0f);

    r /= k;
    g /= k;
    b /= k;
    a /= k;
    return *this;
}

float& Color::operator [](const int i)
{
    GRAPHICS_RUNTIME_ASSERT(i >= 0 && i <= 3);
    return (&r)[i];
}

float Color::operator [](const int i) const
{
    GRAPHICS_RUNTIME_ASSERT(i >= 0 && i <= 3);
    return (&r)[i];
}

float* Color::data()
{
    return &r;
}

const float* Color::data() const
{
    return &r;
}

void Color::clamp()
{
    r = Math::clamp(r, 0.0f, 1.0f);
    g = Math::clamp(g, 0.0f, 1.0f);
    b = Math::clamp(b, 0.0f, 1.0f);
    a = Math::clamp(a, 0.0f, 1.0f);
}

void Color::negate()
{
    r = -r;
    g = -g;
    b = -b;
    a = -a;
}

void Color::set(const float r, const float g, const float b, const float a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
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
    GRAPHICS_RUNTIME_ASSERT(k != 0.0f);

    return Color(
        c.r / k,
        c.g / k,
        c.b / k,
        c.a / k
    );
}

const Color clamp(const Color& c)
{
    return Color(
        Math::clamp(c.r, 0.0f, 1.0f),
        Math::clamp(c.g, 0.0f, 1.0f),
        Math::clamp(c.b, 0.0f, 1.0f),
        Math::clamp(c.a, 0.0f, 1.0f)
    );
}

const Color mix(const Color& a, const Color& b, const float t)
{
    return a + t * (b - a);
}
