/**
 * @file geometry/matrix2x2.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/matrix2x2.h>

#include <geometry/math.h>
#include <geometry/vector2.h>

const Matrix2x2 Matrix2x2::identity()
{
    return Matrix2x2(
        1.0f, 0.0f,
        0.0f, 1.0f
    );
}

const Matrix2x2 Matrix2x2::rotation(const float rotation)
{
    const float c = Math::cos(rotation);
    const float s = Math::sin(rotation);

    return Matrix2x2(c, s, -s, c);
}

Matrix2x2::Matrix2x2()
{
    // ...
}

Matrix2x2::Matrix2x2(
    const float m00, const float m01,
    const float m10, const float m11)
:   m00(m00), m01(m01),
    m10(m10), m11(m11)
{
    // ...
}

Matrix2x2::Matrix2x2(const Vector2& row0, const Vector2& row1)
:   m00(row0.x), m01(row0.y),
    m10(row1.x), m11(row1.y)
{
    // ...
}

Matrix2x2& Matrix2x2::operator +=(const Matrix2x2& m)
{
    *this = *this + m;
    return *this;
}

Matrix2x2& Matrix2x2::operator -=(const Matrix2x2& m)
{
    *this = *this - m;
    return *this;
}

Matrix2x2& Matrix2x2::operator *=(const float k)
{
    *this = *this * k;
    return *this;
}

Matrix2x2& Matrix2x2::operator *=(const Matrix2x2& m)
{
    *this = *this * m;
    return *this;
}

Matrix2x2& Matrix2x2::operator /=(const float k)
{
    // TODO: use tolerances instead of exact values?
    GEOMETRY_RUNTIME_ASSERT(k != 0.0f);

    *this = *this / k;
    return *this;
}

float* Matrix2x2::data()
{
    return &m00;
}

const float* Matrix2x2::data() const
{
    return &m00;
}

const Vector2 Matrix2x2::row(const int index) const
{
    GEOMETRY_RUNTIME_ASSERT(index >= 0 && index <= 1);

    const float* const v = data() + 2 * index;
    return Vector2(v[0], v[1]);
}

void Matrix2x2::swap(Matrix2x2& other)
{
    Math::swap(m00, other.m00);
    Math::swap(m01, other.m01);

    Math::swap(m10, other.m10);
    Math::swap(m11, other.m11);
}

const Vector2 operator *(const Vector2& v, const Matrix2x2& m)
{
    return Vector2(
        v.x * m.m00 + v.y * m.m10,
        v.x * m.m01 + v.y * m.m11
    );
}

const Matrix2x2 operator +(const Matrix2x2& a, const Matrix2x2& b)
{
    return Matrix2x2(
        a.m00 + b.m00, a.m01 + b.m01,
        a.m10 + b.m10, a.m11 + b.m11
    );
}

const Matrix2x2 operator -(const Matrix2x2& m)
{
    return Matrix2x2(
        -m.m00, -m.m01,
        -m.m10, -m.m11
    );
}

const Matrix2x2 operator -(const Matrix2x2& a, const Matrix2x2& b)
{
    return Matrix2x2(
        a.m00 - b.m00, a.m01 - b.m01,
        a.m10 - b.m10, a.m11 - b.m11
    );
}

const Matrix2x2 operator *(const float k, const Matrix2x2& m)
{
    return Matrix2x2(
        k * m.m00, k * m.m01,
        k * m.m10, k * m.m11
    );
}

const Matrix2x2 operator *(const Matrix2x2& m, const float k)
{
    return k * m;
}

const Matrix2x2 operator *(const Matrix2x2& a, const Matrix2x2& b)
{
    return Matrix2x2(
        a.m00 * b.m00 + a.m01 * b.m10,
        a.m00 * b.m01 + a.m01 * b.m11,

        a.m10 * b.m00 + a.m11 * b.m10,
        a.m10 * b.m01 + a.m11 * b.m11
    );
}

const Matrix2x2 operator /(const Matrix2x2& m, const float k)
{
    // TODO: use tolerances instead of exact values?
    GEOMETRY_RUNTIME_ASSERT(k != 0.0f);

    return Matrix2x2(
        m.m00 / k, m.m01 / k,
        m.m10 / k, m.m11 / k
    );
}

float rotationAngle(const Matrix2x2& m)
{
    return Math::atan(m.m01, m.m00);
}

const Vector2 timesTranspose(const Vector2& v, const Matrix2x2& m)
{
    return Vector2(
        v.x * m.m00 + v.y * m.m01,
        v.x * m.m10 + v.y * m.m11
    );
}

const Matrix2x2 orthogonalize(const Matrix2x2& m)
{
    // TODO: In the worst case scenario, this could construct a matrix where
    // one or both rows are incorrectly set to Vector2(1.0f, 0.0f) because of
    // how normalize(const Vector2&) is implemented. Should this function check
    // for division by zero instead of relying on the default behavior of
    // vector normalization?

    const Vector2 x = normalize(m.row(0));

    Vector2 y = m.row(1);

    // extract the part that is parallel to x and normalize
    y -= x * dot(y, x);
    y = normalize(y);

    return Matrix2x2(x, y);
}

const Matrix2x2 slerp(const Matrix2x2& a, const Matrix2x2& b, const float t)
{
    const Matrix2x2 c = timesTranspose(a, b);
    const float angle = rotationAngle(c);

    return a * Matrix2x2::rotation(t * angle);
}

const Matrix2x2 timesTranspose(const Matrix2x2& a, const Matrix2x2& b)
{
    return Matrix2x2(
        a.m00 * b.m00 + a.m01 * b.m01,
        a.m00 * b.m10 + a.m01 * b.m11,

        a.m10 * b.m00 + a.m11 * b.m01,
        a.m10 * b.m10 + a.m11 * b.m11
    );
}

const Matrix2x2 transpose(const Matrix2x2& m)
{
    return Matrix2x2(
        m.m00, m.m10,
        m.m01, m.m11
    );
}

const Matrix2x2 transposeTimes(const Matrix2x2& a, const Matrix2x2& b)
{
    return Matrix2x2(
        a.m00 * b.m00 + a.m10 * b.m10,
        a.m00 * b.m01 + a.m10 * b.m11,

        a.m01 * b.m00 + a.m11 * b.m10,
        a.m01 * b.m01 + a.m11 * b.m11
    );
}
