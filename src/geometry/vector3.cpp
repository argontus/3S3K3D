/**
 * @file geometry/vector3.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/vector3.h>

#include <geometry/math.h>
#include <geometry/matrix3x3.h>

const Vector3 Vector3::zero()
{
    return Vector3(0.0f, 0.0f, 0.0f);
}

Vector3::Vector3()
{
    // ...
}

Vector3::Vector3(const float x, const float y, const float z)
:   x(x),
    y(y),
    z(z)
{
    // ...
}

Vector3& Vector3::operator +=(const Vector3& v)
{
    *this = *this + v;
    return *this;
}

Vector3& Vector3::operator -=(const Vector3& v)
{
    *this = *this - v;
    return *this;
}

Vector3& Vector3::operator *=(const float k)
{
    *this = *this * k;
    return *this;
}

Vector3& Vector3::operator *=(const Matrix3x3& m)
{
    *this = *this * m;
    return *this;
}

Vector3& Vector3::operator /=(const float k)
{
    // TODO: use tolerances instead of exact values?
    GEOMETRY_RUNTIME_ASSERT(k != 0.0f);

    *this = *this / k;
    return *this;
}

float* Vector3::data()
{
    return &x;
}

const float* Vector3::data() const
{
    return &x;
}

void Vector3::swap(Vector3& other)
{
    Math::swap(x, other.x);
    Math::swap(y, other.y);
    Math::swap(z, other.z);
}

const Vector3 operator +(const Vector3& a, const Vector3& b)
{
    return Vector3(
        a.x + b.x,
        a.y + b.y,
        a.z + b.z
    );
}

const Vector3 operator -(const Vector3& v)
{
    return Vector3(
        -v.x,
        -v.y,
        -v.z
    );
}

const Vector3 operator -(const Vector3& a, const Vector3& b)
{
    return Vector3(
        a.x - b.x,
        a.y - b.y,
        a.z - b.z
    );
}

const Vector3 operator *(const float k, const Vector3& v)
{
    return Vector3(
        k * v.x,
        k * v.y,
        k * v.z
    );
}

const Vector3 operator *(const Vector3& v, const float k)
{
    return k * v;
}

const Vector3 operator /(const Vector3& v, const float k)
{
    // TODO: use tolerances instead of exact values?
    GEOMETRY_RUNTIME_ASSERT(k != 0.0f);

    return Vector3(
        v.x / k,
        v.y / k,
        v.z / k
    );
}

float angleBetween(const Vector3& a, const Vector3& b)
{
    const Vector3 ua = normalize(a);
    const Vector3 ub = normalize(b);

    // dot(ua, ub) = cos(angle) -> angle = acos(dot(ua, ub))
    return Math::acos(dot(ua, ub));
}

float distance(const Vector3& a, const Vector3& b)
{
    return length(b - a);
}

float dot(const Vector3& a, const Vector3& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float length(const Vector3& v)
{
    return Math::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

float sqrDistance(const Vector3& a, const Vector3& b)
{
    return sqrLength(b - a);
}

float sqrLength(const Vector3& v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

const Vector3 cross(const Vector3& a, const Vector3& b)
{
    return Vector3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

const Vector3 mix(const Vector3& a, const Vector3& b, const float t)
{
    return a + t * (b - a);
}

const Vector3 normalize(const Vector3& v)
{
    const float k = length(v);

    // TODO: use tolerances instead of exact values?
    if (k > 0.0f)
    {
        return v / k;
    }
    else
    {
        return Vector3(1.0f, 0.0f, 0.0f);
    }
}

const Vector3 reflect(const Vector3& v, const Vector3& n)
{
    return v - 2.0f * dot(v, n) * n;
}
