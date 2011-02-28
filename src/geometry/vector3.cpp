/**
 * @file geometry/vector3.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/vector3.h>

// TODO: get rid of this #include
#include <algorithm>

#include <geometry/math.h>

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
    std::swap(x, other.x);
    std::swap(y, other.y);
    std::swap(z, other.z);
}

Vector3& operator +=(Vector3& a, const Vector3& b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

Vector3& operator -=(Vector3& a, const Vector3& b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return a;
}

Vector3& operator *=(Vector3& v, const float k)
{
    v.x *= k;
    v.y *= k;
    v.z *= k;
    return v;
}

Vector3& operator *=(Vector3& a, const Vector3& b)
{
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
    return a;
}

Vector3& operator /=(Vector3& v, const float k)
{
    // TODO: use tolerances instead of exact values?
    GEOMETRY_RUNTIME_ASSERT(k != 0.0f);

    v.x /= k;
    v.y /= k;
    v.z /= k;
    return v;
}

Vector3& operator /=(Vector3& a, const Vector3& b)
{
    // TODO: use tolerances instead of exact values?
    GEOMETRY_RUNTIME_ASSERT(b.x != 0.0f);
    GEOMETRY_RUNTIME_ASSERT(b.y != 0.0f);
    GEOMETRY_RUNTIME_ASSERT(b.z != 0.0f);

    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
    return a;
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
    return Vector3(
        v.x * k,
        v.y * k,
        v.z * k
    );
}

const Vector3 operator *(const Vector3& a, const Vector3& b)
{
    return Vector3(
        a.x * b.x,
        a.y * b.y,
        a.z * b.z
    );
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

const Vector3 operator /(const Vector3& a, const Vector3& b)
{
    // TODO: use tolerances instead of exact values?
    GEOMETRY_RUNTIME_ASSERT(b.x != 0.0f);
    GEOMETRY_RUNTIME_ASSERT(b.y != 0.0f);
    GEOMETRY_RUNTIME_ASSERT(b.z != 0.0f);

    return Vector3(
        a.x / b.x,
        a.y / b.y,
        a.z / b.z
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

const Vector3 clamp(const Vector3& v, const float min, const float max)
{
    GEOMETRY_RUNTIME_ASSERT(min <= max);

    return Vector3(
        Math::clamp(v.x, min, max),
        Math::clamp(v.y, min, max),
        Math::clamp(v.z, min, max)
    );
}

const Vector3 clamp(const Vector3& v, const Vector3& min, const Vector3& max)
{
    GEOMETRY_RUNTIME_ASSERT(min.x <= max.x);
    GEOMETRY_RUNTIME_ASSERT(min.y <= max.y);
    GEOMETRY_RUNTIME_ASSERT(min.z <= max.z);

    return Vector3(
        Math::clamp(v.x, min.x, max.x),
        Math::clamp(v.y, min.y, max.y),
        Math::clamp(v.z, min.z, max.z)
    );
}

const Vector3 cross(const Vector3& a, const Vector3& b)
{
    return Vector3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

const Vector3 max(const Vector3& v, const float k)
{
    return Vector3(
        Math::max(v.x, k),
        Math::max(v.y, k),
        Math::max(v.z, k)
    );
}

const Vector3 max(const Vector3& a, const Vector3& b)
{
    return Vector3(
        Math::max(a.x, b.x),
        Math::max(a.y, b.y),
        Math::max(a.z, b.z)
    );
}

const Vector3 min(const Vector3& v, const float k)
{
    return Vector3(
        Math::min(v.x, k),
        Math::min(v.y, k),
        Math::min(v.z, k)
    );
}

const Vector3 min(const Vector3& a, const Vector3& b)
{
    return Vector3(
        Math::min(a.x, b.x),
        Math::min(a.y, b.y),
        Math::min(a.z, b.z)
    );
}

const Vector3 mix(const Vector3& a, const Vector3& b, const float t)
{
    return a + t * (b - a);
}

const Vector3 mix(const Vector3& a, const Vector3& b, const Vector3& t)
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

const Vector3 reflect(const Vector3& v, const Vector3& normal)
{
    return v - 2.0f * dot(v, normal) * normal;
}
