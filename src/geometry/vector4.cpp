/**
 * @file geometry/vector4.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/vector4.h>

#include <geometry/math.h>

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

Vector4& operator +=(Vector4& a, const Vector4& b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;
    return a;
}

Vector4& operator -=(Vector4& a, const Vector4& b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.w -= b.w;
    return a;
}

Vector4& operator *=(Vector4& v, const float k)
{
    v.x *= k;
    v.y *= k;
    v.z *= k;
    v.w *= k;
    return v;
}

Vector4& operator *=(Vector4& a, const Vector4& b)
{
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
    a.w *= b.w;
    return a;
}

Vector4& operator /=(Vector4& v, const float k)
{
    // TODO: use tolerances instead of exact values?
    GEOMETRY_RUNTIME_ASSERT(k != 0.0f);

    v.x /= k;
    v.y /= k;
    v.z /= k;
    v.w /= k;
    return v;
}

Vector4& operator /=(Vector4& a, const Vector4& b)
{
    // TODO: use tolerances instead of exact values?
    GEOMETRY_RUNTIME_ASSERT(b.x != 0.0f);
    GEOMETRY_RUNTIME_ASSERT(b.y != 0.0f);
    GEOMETRY_RUNTIME_ASSERT(b.z != 0.0f);
    GEOMETRY_RUNTIME_ASSERT(b.w != 0.0f);

    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
    a.w /= b.w;
    return a;
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
    return Vector4(
        v.x * k,
        v.y * k,
        v.z * k,
        v.w * k
    );
}

const Vector4 operator *(const Vector4& a, const Vector4& b)
{
    return Vector4(
        a.x * b.x,
        a.y * b.y,
        a.z * b.z,
        a.w * b.w
    );
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

const Vector4 operator /(const Vector4& a, const Vector4& b)
{
    // TODO: use tolerances instead of exact values?
    GEOMETRY_RUNTIME_ASSERT(b.x != 0.0f);
    GEOMETRY_RUNTIME_ASSERT(b.y != 0.0f);
    GEOMETRY_RUNTIME_ASSERT(b.z != 0.0f);
    GEOMETRY_RUNTIME_ASSERT(b.w != 0.0f);

    return Vector4(
        a.x / b.x,
        a.y / b.y,
        a.z / b.z,
        a.w / b.w
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

const Vector4 clamp(const Vector4& v, const float min, const float max)
{
    GEOMETRY_RUNTIME_ASSERT(min <= max);

    return Vector4(
        Math::clamp(v.x, min, max),
        Math::clamp(v.y, min, max),
        Math::clamp(v.z, min, max),
        Math::clamp(v.w, min, max)
    );
}

const Vector4 clamp(const Vector4& v, const Vector4& min, const Vector4& max)
{
    GEOMETRY_RUNTIME_ASSERT(min.x <= max.x);
    GEOMETRY_RUNTIME_ASSERT(min.y <= max.y);
    GEOMETRY_RUNTIME_ASSERT(min.z <= max.z);
    GEOMETRY_RUNTIME_ASSERT(min.w <= max.w);

    return Vector4(
        Math::clamp(v.x, min.x, max.x),
        Math::clamp(v.y, min.y, max.y),
        Math::clamp(v.z, min.z, max.z),
        Math::clamp(v.w, min.w, max.w)
    );
}

const Vector4 max(const Vector4& v, const float k)
{
    return Vector4(
        Math::max(v.x, k),
        Math::max(v.y, k),
        Math::max(v.z, k),
        Math::max(v.w, k)
    );
}

const Vector4 max(const Vector4& a, const Vector4& b)
{
    return Vector4(
        Math::max(a.x, b.x),
        Math::max(a.y, b.y),
        Math::max(a.z, b.z),
        Math::max(a.w, b.w)
    );
}

const Vector4 min(const Vector4& v, const float k)
{
    return Vector4(
        Math::min(v.x, k),
        Math::min(v.y, k),
        Math::min(v.z, k),
        Math::min(v.w, k)
    );
}

const Vector4 min(const Vector4& a, const Vector4& b)
{
    return Vector4(
        Math::min(a.x, b.x),
        Math::min(a.y, b.y),
        Math::min(a.z, b.z),
        Math::min(a.w, b.w)
    );
}

const Vector4 mix(const Vector4& a, const Vector4& b, const float t)
{
    return a + t * (b - a);
}

const Vector4 mix(const Vector4& a, const Vector4& b, const Vector4& t)
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

const Vector4 reflect(const Vector4& v, const Vector4& normal)
{
    return v - 2.0f * dot(v, normal) * normal;
}
