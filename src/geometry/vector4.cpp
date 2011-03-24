/**
 * @file geometry/vector4.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/vector4.h>

#include <geometry/math.h>
#include <geometry/matrix4x4.h>

const Vector4 Vector4::zero()
{
    return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
}

Vector4::Vector4()
{
    // ...
}

Vector4::Vector4(const float x, const float y, const float z, const float w)
:   x(x),
    y(y),
    z(z),
    w(w)
{
    // ...
}

Vector4& Vector4::operator +=(const Vector4& v)
{
    *this = *this + v;
    return *this;
}

Vector4& Vector4::operator -=(const Vector4& v)
{
    *this = *this - v;
    return *this;
}

Vector4& Vector4::operator *=(const float k)
{
    *this = *this * k;
    return *this;
}

Vector4& Vector4::operator *=(const Matrix4x4& m)
{
    *this = *this * m;
    return *this;
}

Vector4& Vector4::operator /=(const float k)
{
    // TODO: use tolerances instead of exact values?
    GEOMETRY_RUNTIME_ASSERT(k != 0.0f);

    *this = *this / k;
    return *this;
}

float* Vector4::data()
{
    return &x;
}

const float* Vector4::data() const
{
    return &x;
}

void Vector4::swap(Vector4& other)
{
    Math::swap(x, other.x);
    Math::swap(y, other.y);
    Math::swap(z, other.z);
    Math::swap(w, other.w);
}

const Vector4 operator +(const Vector4& a, const Vector4& b)
{
    return Vector4(
        a.x + b.x,
        a.y + b.y,
        a.z + b.z,
        a.w + b.w
    );
}

const Vector4 operator -(const Vector4& v)
{
    return Vector4(
        -v.x,
        -v.y,
        -v.z,
        -v.w
    );
}

const Vector4 operator -(const Vector4& a, const Vector4& b)
{
    return Vector4(
        a.x - b.x,
        a.y - b.y,
        a.z - b.z,
        a.w - b.w
    );
}

const Vector4 operator *(const float k, const Vector4& v)
{
    return Vector4(
        k * v.x,
        k * v.y,
        k * v.z,
        k * v.w
    );
}

const Vector4 operator *(const Vector4& v, const float k)
{
    return k * v;
}

const Vector4 operator /(const Vector4& v, const float k)
{
    // TODO: use tolerances instead of exact values?
    GEOMETRY_RUNTIME_ASSERT(k != 0.0f);

    return Vector4(
        v.x / k,
        v.y / k,
        v.z / k,
        v.w / k
    );
}

float angleBetween(const Vector4& a, const Vector4& b)
{
    const Vector4 ua = normalize(a);
    const Vector4 ub = normalize(b);

    // dot(ua, ub) = cos(angle) -> angle = acos(dot(ua, ub))
    return Math::acos(dot(ua, ub));
}

float distance(const Vector4& a, const Vector4& b)
{
    return length(b - a);
}

float dot(const Vector4& a, const Vector4& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

float length(const Vector4& v)
{
    return Math::sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

float sqrDistance(const Vector4& a, const Vector4& b)
{
    return sqrLength(b - a);
}

float sqrLength(const Vector4& v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
}

const Vector4 mix(const Vector4& a, const Vector4& b, const float t)
{
    return a + t * (b - a);
}

const Vector4 normalize(const Vector4& v)
{
    const float k = length(v);

    // TODO: use tolerances instead of exact values?
    if (k > 0.0f)
    {
        return v / k;
    }
    else
    {
        return Vector4(1.0f, 0.0f, 0.0f, 0.0f);
    }
}

const Vector4 reflect(const Vector4& v, const Vector4& n)
{
    return v - 2.0f * dot(v, n) * n;
}
