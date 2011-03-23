/**
 * @file geometry/vector2.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/vector2.h>

#include <geometry/math.h>
#include <geometry/matrix2x2.h>

const Vector2 Vector2::zero()
{
    return Vector2(0.0f, 0.0f);
}

const Vector2 Vector2::direction(const float angle)
{
    return Vector2(Math::cos(angle), Math::sin(angle));
}

Vector2::Vector2()
{
    // ...
}

Vector2::Vector2(const float x, const float y)
:   x(x),
    y(y)
{
    // ...
}

Vector2& Vector2::operator +=(const Vector2& v)
{
    *this = *this + v;
    return *this;
}

Vector2& Vector2::operator -=(const Vector2& v)
{
    *this = *this - v;
    return *this;
}

Vector2& Vector2::operator *=(const float k)
{
    *this = *this * k;
    return *this;
}

Vector2& Vector2::operator *=(const Matrix2x2& m)
{
    *this = *this * m;
    return *this;
}

Vector2& Vector2::operator /=(const float k)
{
    // TODO: use tolerances instead of exact values?
    GEOMETRY_RUNTIME_ASSERT(k != 0.0f);

    *this = *this / k;
    return *this;
}

float* Vector2::data()
{
    return &x;
}

const float* Vector2::data() const
{
    return &x;
}

void Vector2::swap(Vector2& other)
{
    Math::swap(x, other.x);
    Math::swap(y, other.y);
}

const Vector2 operator +(const Vector2& a, const Vector2& b)
{
    return Vector2(
        a.x + b.x,
        a.y + b.y
    );
}

const Vector2 operator -(const Vector2& v)
{
    return Vector2(
        -v.x,
        -v.y
    );
}

const Vector2 operator -(const Vector2& a, const Vector2& b)
{
    return Vector2(
        a.x - b.x,
        a.y - b.y
    );
}

const Vector2 operator *(const float k, const Vector2& v)
{
    return Vector2(
        k * v.x,
        k * v.y
    );
}

const Vector2 operator *(const Vector2& v, const float k)
{
    return k * v;
}

const Vector2 operator /(const Vector2& v, const float k)
{
    // TODO: use tolerances instead of exact values?
    GEOMETRY_RUNTIME_ASSERT(k != 0.0f);

    return Vector2(
        v.x / k,
        v.y / k
    );
}

float angle(const Vector2& v)
{
    return Math::atan(v.y, v.x);
}

float angleBetween(const Vector2& a, const Vector2& b)
{
    const Vector2 ua = normalize(a);
    const Vector2 ub = normalize(b);

    // dot(ua, ub) = cos(angle) -> angle = acos(dot(ua, ub))
    return Math::acos(dot(ua, ub));
}

float distance(const Vector2& a, const Vector2& b)
{
    return length(b - a);
}

float dot(const Vector2& a, const Vector2& b)
{
    return a.x * b.x + a.y * b.y;
}

float length(const Vector2& v)
{
    return Math::sqrt(v.x * v.x + v.y * v.y);
}

float sqrDistance(const Vector2& a, const Vector2& b)
{
    return sqrLength(b - a);
}

float sqrLength(const Vector2& v)
{
    return v.x * v.x + v.y * v.y;
}

const Vector2 mix(const Vector2& a, const Vector2& b, const float t)
{
    return a + t * (b - a);
}

const Vector2 normalize(const Vector2& v)
{
    const float k = length(v);

    // TODO: use tolerances instead of exact values?
    if (k > 0.0f)
    {
        return v / k;
    }
    else
    {
        return Vector2(1.0f, 0.0f);
    }
}

const Vector2 perp(const Vector2& v)
{
    return Vector2(
        -v.y,
         v.x
    );
}

const Vector2 polarPoint(const float radius, const float angle)
{
    return radius * Vector2::direction(angle);
}

const Vector2 reflect(const Vector2& v, const Vector2& n)
{
    return v - 2.0f * dot(v, n) * n;
}
