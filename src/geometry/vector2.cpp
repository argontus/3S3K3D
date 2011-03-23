/**
 * @file geometry/vector2.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/vector2.h>

#include <geometry/math.h>

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

Vector2& operator +=(Vector2& a, const Vector2& b)
{
    a.x += b.x;
    a.y += b.y;
    return a;
}

Vector2& operator -=(Vector2& a, const Vector2& b)
{
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

Vector2& operator *=(Vector2& v, const float k)
{
    v.x *= k;
    v.y *= k;
    return v;
}

Vector2& operator *=(Vector2& a, const Vector2& b)
{
    a.x *= b.x;
    a.y *= b.y;
    return a;
}

Vector2& operator /=(Vector2& v, const float k)
{
    // TODO: use tolerances instead of exact values?
    GEOMETRY_RUNTIME_ASSERT(k != 0.0f);

    v.x /= k;
    v.y /= k;
    return v;
}

Vector2& operator /=(Vector2& a, const Vector2& b)
{
    // TODO: use tolerances instead of exact values?
    GEOMETRY_RUNTIME_ASSERT(b.x != 0.0f);
    GEOMETRY_RUNTIME_ASSERT(b.y != 0.0f);

    a.x /= b.x;
    a.y /= b.y;
    return a;
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
    return Vector2(
        v.x * k,
        v.y * k
    );
}

const Vector2 operator *(const Vector2& a, const Vector2& b)
{
    return Vector2(
        a.x * b.x,
        a.y * b.y
    );
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

const Vector2 operator /(const Vector2& a, const Vector2& b)
{
    // TODO: use tolerances instead of exact values?
    GEOMETRY_RUNTIME_ASSERT(b.x != 0.0f);
    GEOMETRY_RUNTIME_ASSERT(b.y != 0.0f);

    return Vector2(
        a.x / b.x,
        a.y / b.y
    );
}

float angle(const Vector2& v)
{
    const Vector2 direction = normalize(v);

    if (v.y >= 0.0f)
    {
        return Math::acos(v.x);
    }
    else
    {
        return 2.0f * Math::pi() - Math::acos(v.x);
    }
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

float perpDot(const Vector2& a, const Vector2& b)
{
    return a.x * b.y - a.y * b.x;
}

float sqrDistance(const Vector2& a, const Vector2& b)
{
    return sqrLength(b - a);
}

float sqrLength(const Vector2& v)
{
    return v.x * v.x + v.y * v.y;
}

const Vector2 clamp(const Vector2& v, const float min, const float max)
{
    GEOMETRY_RUNTIME_ASSERT(min <= max);

    return Vector2(
        Math::clamp(v.x, min, max),
        Math::clamp(v.y, min, max)
    );
}

const Vector2 clamp(const Vector2& v, const Vector2& min, const Vector2& max)
{
    GEOMETRY_RUNTIME_ASSERT(min.x <= max.x);
    GEOMETRY_RUNTIME_ASSERT(min.y <= max.y);

    return Vector2(
        Math::clamp(v.x, min.x, max.x),
        Math::clamp(v.y, min.y, max.y)
    );
}

const Vector2 max(const Vector2& v, const float k)
{
    return Vector2(
        Math::max(v.x, k),
        Math::max(v.y, k)
    );
}

const Vector2 max(const Vector2& a, const Vector2& b)
{
    return Vector2(
        Math::max(a.x, b.x),
        Math::max(a.y, b.y)
    );
}

const Vector2 min(const Vector2& v, const float k)
{
    return Vector2(
        Math::min(v.x, k),
        Math::min(v.y, k)
    );
}

const Vector2 min(const Vector2& a, const Vector2& b)
{
    return Vector2(
        Math::min(a.x, b.x),
        Math::min(a.y, b.y)
    );
}

const Vector2 mix(const Vector2& a, const Vector2& b, const float t)
{
    return a + t * (b - a);
}

const Vector2 mix(const Vector2& a, const Vector2& b, const Vector2& t)
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

const Vector2 polarPoint(const float angle, const float radius)
{
    return radius * Vector2::direction(angle);
}

const Vector2 polarPoint(
    const Vector2& origin,
    const float angle,
    const float radius)
{
    return origin + radius * Vector2::direction(angle);
}

const Vector2 reflect(const Vector2& v, const Vector2& normal)
{
    return v - 2.0f * dot(v, normal) * normal;
}
