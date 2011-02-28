/**
 * @file geometry/matrix2x2.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/matrix2x2.h>

// TODO: get rid of this #include
#include <algorithm>

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

const Vector2 Matrix2x2::row0() const
{
    return Vector2(m00, m01);
}

const Vector2 Matrix2x2::row1() const
{
    return Vector2(m10, m11);
}

float* Matrix2x2::data()
{
    return &m00;
}

const float* Matrix2x2::data() const
{
    return &m00;
}

void Matrix2x2::swap(Matrix2x2& other)
{
    std::swap(m00, other.m00);
    std::swap(m01, other.m01);

    std::swap(m10, other.m10);
    std::swap(m11, other.m11);
}

const Vector2 product(const Vector2& v, const Matrix2x2& m)
{
    return Vector2(
        v.x * m.m00 + v.y * m.m10,
        v.x * m.m01 + v.y * m.m11
    );
}

const Vector2 productT(const Vector2& v, const Matrix2x2& m)
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

    const Vector2 x = normalize(m.row0());

    Vector2 y = m.row1();

    // extract the part that is parallel to x and normalize
    y -= x * dot(y, x);
    y = normalize(y);

    return Matrix2x2(x, y);
}

const Matrix2x2 product(const Matrix2x2& a, const Matrix2x2& b)
{
    return Matrix2x2(
        a.m00 * b.m00 + a.m01 * b.m10,
        a.m00 * b.m01 + a.m01 * b.m11,

        a.m10 * b.m00 + a.m11 * b.m10,
        a.m10 * b.m01 + a.m11 * b.m11
    );
}

const Matrix2x2 productT(const Matrix2x2& a, const Matrix2x2& b)
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
