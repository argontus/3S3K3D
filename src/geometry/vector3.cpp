/**
 * @file geometry/vector3.cpp
 * @author Mika Haarahiltunen
 */

// geometry/vector3.h is included via geometry/plane3.h

#include <algorithm>

#include <geometry/math.h>
#include <geometry/plane3.h>

const Vector3& Vector3::zero()
{
    static const Vector3 v(0.0f, 0.0f, 0.0f);
    return v;
}

const Vector3& Vector3::xAxis()
{
    static const Vector3 v(1.0f, 0.0f, 0.0f);
    return v;
}

const Vector3& Vector3::yAxis()
{
    static const Vector3 v(0.0f, 1.0f, 0.0f);
    return v;
}

const Vector3& Vector3::zAxis()
{
    static const Vector3 v(0.0f, 0.0f, 1.0f);
    return v;
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
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

Vector3& Vector3::operator -=(const Vector3& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

Vector3& Vector3::operator *=(const float k)
{
    x *= k;
    y *= k;
    z *= k;
    return *this;
}

Vector3& Vector3::operator /=(const float k)
{
    GEOMETRY_RUNTIME_ASSERT(k != 0.0f);

    x /= k;
    y /= k;
    z /= k;
    return *this;
}

float& Vector3::operator [](const int i)
{
    GEOMETRY_RUNTIME_ASSERT(i >= 0 && i <= 2);
    return (&x)[i];
}

float Vector3::operator [](const int i) const
{
    GEOMETRY_RUNTIME_ASSERT(i >= 0 && i <= 2);
    return (&x)[i];
}

float* Vector3::data()
{
    return &x;
}

const float* Vector3::data() const
{
    return &x;
}

void Vector3::negate()
{
    x = -x;
    y = -y;
    z = -z;
}

void Vector3::normalize()
{
    const float k = length(*this);
    GEOMETRY_RUNTIME_ASSERT(k > 0.0f);

    x /= k;
    y /= k;
    z /= k;
}

void Vector3::set(const float x, const float y, const float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector3::swap(Vector3& other)
{
    std::swap(x, other.x);
    std::swap(y, other.y);
    std::swap(z, other.z);
}

const Vector3 operator +(const Vector3& a, const Vector3& b)
{
    return Vector3(
        a.x + b.x,
        a.y + b.y,
        a.z + b.z
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

const Vector3 operator -(const Vector3& v)
{
    return Vector3(
        -v.x,
        -v.y,
        -v.z
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
    return Vector3(
        k * v.x,
        k * v.y,
        k * v.z
    );
}

const Vector3 operator /(const Vector3& v, const float k)
{
    GEOMETRY_RUNTIME_ASSERT(k != 0.0f);

    return Vector3(
        v.x / k,
        v.y / k,
        v.z / k
    );
}

float distance(const Vector3& a, const Vector3& b)
{
    return length(b - a);
}

float sqrDistance(const Vector3& a, const Vector3& b)
{
    return sqrLength(b - a);
}

float dot(const Vector3& a, const Vector3& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

const Vector3 cross(const Vector3& a, const Vector3& b)
{
    return Vector3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

float length(const Vector3& v)
{
    return Math::sqrt(dot(v, v));
}

float sqrLength(const Vector3& v)
{
    return dot(v, v);
}

const Vector3 mix(const Vector3& a, const Vector3& b, const float t)
{
    return a + t * (b - a);
}

const Vector3 normalize(const Vector3& v)
{
    const float k = length(v);
    GEOMETRY_RUNTIME_ASSERT(k > 0.0f);

    return v / k;
}

const Vector3 reflect(const Vector3& v, const Vector3& normal)
{
    return v - 2.0f * dot(v, normal) * normal;
}

const Vector3 reflect(const Vector3& q, const Plane3& plane)
{
    return q - 2.0f * plane.distanceTo(q) * plane.normal;
}
