/**
 * @file geometry/vector2.cpp
 * @author Mika Haarahiltunen
 */

// geometry/vector2.h is included via geometry/plane2.h

#include <algorithm>

#include <geometry/math.h>
#include <geometry/plane2.h>

const Vector2& Vector2::zero()
{
    static const Vector2 v(0.0f, 0.0f);
    return v;
}

const Vector2& Vector2::xAxis()
{
    static const Vector2 v(1.0f, 0.0f);
    return v;
}

const Vector2& Vector2::yAxis()
{
    static const Vector2 v(0.0f, 1.0f);
    return v;
}

const Vector2 Vector2::direction(const float theta)
{
    return Vector2(Math::cos(theta), Math::sin(theta));
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
    x += v.x;
    y += v.y;
    return *this;
}

Vector2& Vector2::operator -=(const Vector2& v)
{
    x -= v.x;
    y -= v.y;
    return *this;
}

Vector2& Vector2::operator *=(const float k)
{
    x *= k;
    y *= k;
    return *this;
}

Vector2& Vector2::operator /=(const float k)
{
    GEOMETRY_RUNTIME_ASSERT(k != 0.0f);

    x /= k;
    y /= k;
    return *this;
}

float& Vector2::operator [](const int i)
{
    GEOMETRY_RUNTIME_ASSERT(i >= 0 && i <= 1);
    return (&x)[i];
}

float Vector2::operator [](const int i) const
{
    GEOMETRY_RUNTIME_ASSERT(i >= 0 && i <= 1);
    return (&x)[i];
}

float* Vector2::data()
{
    return &x;
}

const float* Vector2::data() const
{
    return &x;
}

void Vector2::negate()
{
    x = -x;
    y = -y;
}

void Vector2::normalize()
{
    const float k = length(*this);
    GEOMETRY_RUNTIME_ASSERT(k > 0.0f);

    x /= k;
    y /= k;
}

void Vector2::set(const float x, const float y)
{
    this->x = x;
    this->y = y;
}

void Vector2::swap(Vector2& other)
{
    std::swap(x, other.x);
    std::swap(y, other.y);
}

const Vector2 operator +(const Vector2& a, const Vector2& b)
{
    return Vector2(
        a.x + b.x,
        a.y + b.y
    );
}

const Vector2 operator -(const Vector2& a, const Vector2& b)
{
    return Vector2(
        a.x - b.x,
        a.y - b.y
    );
}

const Vector2 operator -(const Vector2& v)
{
    return Vector2(
        -v.x,
        -v.y
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
        k * v.x,
        k * v.y
    );
}

const Vector2 operator /(const Vector2& v, const float k)
{
    GEOMETRY_RUNTIME_ASSERT(k != 0.0f);

    return Vector2(
        v.x / k,
        v.y / k
    );
}

float angle(const Vector2& v)
{
    const float k = length(v);
    GEOMETRY_RUNTIME_ASSERT(k > 0.0f);

    const float c = v.x / k;

    if (v.y >= 0.0f)
    {
        return Math::acos(c);
    }
    else
    {
        return Math::twoPi() - Math::acos(c);
    }
}

float distance(const Vector2& a, const Vector2& b)
{
    return length(b - a);
}

float sqrDistance(const Vector2& a, const Vector2& b)
{
    return sqrLength(b - a);
}

float dot(const Vector2& a, const Vector2& b)
{
    return a.x * b.x + a.y * b.y;
}

float perpDot(const Vector2& a, const Vector2& b)
{
    return a.x * b.y - a.y * b.x;
}

float length(const Vector2& v)
{
    return Math::sqrt(dot(v, v));
}

float sqrLength(const Vector2& v)
{
    return dot(v, v);
}

const Vector2 mix(const Vector2& a, const Vector2& b, const float t)
{
    return a + t * (b - a);
}

const Vector2 perp(const Vector2& v)
{
    return Vector2(
        -v.y,
         v.x
    );
}

const Vector2 normalize(const Vector2& v)
{
    const float k = length(v);
    GEOMETRY_RUNTIME_ASSERT(k > 0.0f);

    return v / k;
}

const Vector2 reflect(const Vector2& v, const Vector2& normal)
{
    return v - 2.0f * dot(v, normal) * normal;
}

const Vector2 reflect(const Vector2& q, const Plane2& plane)
{
    return q - 2.0f * plane.distanceTo(q) * plane.normal;
}

const Vector2 polarPoint(const float direction, const float distance)
{
    return distance * Vector2::direction(direction);
}

const Vector2 polarPoint(const Vector2& point, const float direction, const float distance)
{
    return point + distance * Vector2::direction(direction);
}
