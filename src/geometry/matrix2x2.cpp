/**
 * @file geometry/matrix2x2.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/matrix2x2.h>

#include <algorithm>

#include <geometry/math.h>
#include <geometry/vector2.h>

const Matrix2x2& Matrix2x2::identity()
{
    static const Matrix2x2 m(
        1.0f, 0.0f,
        0.0f, 1.0f
    );

    return m;
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

float* Matrix2x2::operator [](const int row)
{
    GEOMETRY_RUNTIME_ASSERT(row >= 0 && row <= 1);
    return &m00 + row * 2;
}

const float* Matrix2x2::operator [](const int row) const
{
    GEOMETRY_RUNTIME_ASSERT(row >= 0 && row <= 1);
    return &m00 + row * 2;
}

float* Matrix2x2::data()
{
    return &m00;
}

const float* Matrix2x2::data() const
{
    return &m00;
}

void Matrix2x2::setRow(const int row, const Vector2& v)
{
    GEOMETRY_RUNTIME_ASSERT(row >= 0 && row <= 1);
    float* data = &m00 + row * 2;

    data[0] = v.x;
    data[1] = v.y;
}

const Vector2 Matrix2x2::row(const int row) const
{
    GEOMETRY_RUNTIME_ASSERT(row >= 0 && row <= 1);
    const float* data = &m00 + row * 2;
    return Vector2(data[0], data[1]);
}

void Matrix2x2::setColumn(const int column, const Vector2& v)
{
    GEOMETRY_RUNTIME_ASSERT(column >= 0 && column <= 1);
    float* data = &m00 + column;

    data[0] = v.x;
    data[2] = v.y;
}

const Vector2 Matrix2x2::column(const int column) const
{
    GEOMETRY_RUNTIME_ASSERT(column >= 0 && column <= 1);
    const float* data = &m00 + column;
    return Vector2(data[0], data[2]);
}

void Matrix2x2::multiplyBy(const Matrix2x2& m)
{
    *this = product(*this, m);
}

void Matrix2x2::multiplyByT(const Matrix2x2& m)
{
    *this = productT(*this, m);
}

void Matrix2x2::orthogonalize()
{
    Vector2 x(m00, m01);
    x.normalize();

    Vector2 y(m10, m11);
    y -= x * dot(y, x);
    y.normalize();

    m00 = x.x;
    m01 = x.y;

    m10 = y.x;
    m11 = y.y;
}

void Matrix2x2::swap(Matrix2x2& other)
{
    std::swap(m00, other.m00);
    std::swap(m01, other.m01);

    std::swap(m10, other.m10);
    std::swap(m11, other.m11);
}

float angle(const Matrix2x2& m)
{
    const Vector2 xAxis = m.row(0);

    if (xAxis.y >= 0.0f)
    {
        return Math::acos(xAxis.x);
    }
    else
    {
        return Math::twoPi() - Math::acos(xAxis.x);
    }
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
