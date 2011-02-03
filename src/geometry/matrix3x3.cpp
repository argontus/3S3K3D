/**
 * @file geometry/matrix3x3.h
 * @author Mika Haarahiltunen
 */

#include <geometry/matrix3x3.h>

#include <algorithm>

#include <geometry/math.h>
#include <geometry/vector3.h>

const Matrix3x3& Matrix3x3::identity()
{
    static const Matrix3x3 m(
        1.0f,  0.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  0.0f,  1.0f
    );

    return m;
}

const Matrix3x3 Matrix3x3::xRotation(const float rotation)
{
    const float c = Math::cos(rotation);
    const float s = Math::sin(rotation);

    return Matrix3x3(
        1.0f,  0.0f,  0.0f,
        0.0f,     c,     s,
        0.0f,    -s,     c
    );
}

const Matrix3x3 Matrix3x3::yRotation(const float rotation)
{
    const float c = Math::cos(rotation);
    const float s = Math::sin(rotation);

    return Matrix3x3(
           c,  0.0f,    -s,
        0.0f,  1.0f,  0.0f,
           s,  0.0f,     c
    );
}

const Matrix3x3 Matrix3x3::zRotation(const float rotation)
{
    const float c = Math::cos(rotation);
    const float s = Math::sin(rotation);

    return Matrix3x3(
           c,     s,  0.0f,
          -s,     c,  0.0f,
        0.0f,  0.0f,  1.0f
    );
}

const Matrix3x3 Matrix3x3::rotation(const Vector3& axis, const float rotation)
{
    // TODO: not tested, does this work?

    const float c = Math::cos(rotation);
    const float s = Math::sin(rotation);
    const float k = 1.0f - c;

    const float x = axis.x;
    const float y = axis.y;
    const float z = axis.z;

    // let the compiler take care of common sub-expressions

    return Matrix3x3(
            x * x * k + c,  x * y * k + z * s,  x * z * k - y * s,
        x * y * k - z * s,      y * y * k + c,  y * z * k + x * s,
        x * z * k + y * s,  y * z * k - x * s,      z * z * k + c
    );
}

Matrix3x3::Matrix3x3()
{
    // ...
}

Matrix3x3::Matrix3x3(
    const float m00, const float m01, const float m02,
    const float m10, const float m11, const float m12,
    const float m20, const float m21, const float m22)
:   m00(m00), m01(m01), m02(m02),
    m10(m10), m11(m11), m12(m12),
    m20(m20), m21(m21), m22(m22)
{
    // ...
}

Matrix3x3::Matrix3x3(
    const Vector3& row0,
    const Vector3& row1,
    const Vector3& row2)
:   m00(row0.x), m01(row0.y), m02(row0.z),
    m10(row1.x), m11(row1.y), m12(row1.z),
    m20(row2.x), m21(row2.y), m22(row2.z)
{
    // ...
}

float* Matrix3x3::operator [](const int row)
{
    GEOMETRY_RUNTIME_ASSERT(row >= 0 && row <= 2);
    return &m00 + row * 3;
}

const float* Matrix3x3::operator [](const int row) const
{
    GEOMETRY_RUNTIME_ASSERT(row >= 0 && row <= 2);
    return &m00 + row * 3;
}

float* Matrix3x3::data()
{
    return &m00;
}

const float* Matrix3x3::data() const
{
    return &m00;
}

void Matrix3x3::multiplyBy(const Matrix3x3& m)
{
    m00 = m00 * m.m00 + m01 * m.m10 + m02 * m.m20;
    m01 = m00 * m.m01 + m01 * m.m11 + m02 * m.m21;
    m02 = m00 * m.m02 + m01 * m.m12 + m02 * m.m22;

    m10 = m10 * m.m00 + m11 * m.m10 + m12 * m.m20;
    m11 = m10 * m.m01 + m11 * m.m11 + m12 * m.m21;
    m12 = m10 * m.m02 + m11 * m.m12 + m12 * m.m22;

    m20 = m20 * m.m00 + m21 * m.m10 + m22 * m.m20;
    m21 = m20 * m.m01 + m21 * m.m11 + m22 * m.m21;
    m22 = m20 * m.m02 + m21 * m.m12 + m22 * m.m22;
}

void Matrix3x3::multiplyByT(const Matrix3x3& m)
{
    m00 = m00 * m.m00 + m01 * m.m01 + m02 * m.m02;
    m01 = m00 * m.m10 + m01 * m.m11 + m02 * m.m12;
    m02 = m00 * m.m20 + m01 * m.m21 + m02 * m.m22;

    m10 = m10 * m.m00 + m11 * m.m01 + m12 * m.m02;
    m11 = m10 * m.m10 + m11 * m.m11 + m12 * m.m12;
    m12 = m10 * m.m20 + m11 * m.m21 + m12 * m.m22;

    m20 = m20 * m.m00 + m21 * m.m01 + m22 * m.m02;
    m21 = m20 * m.m10 + m21 * m.m11 + m22 * m.m12;
    m22 = m20 * m.m20 + m21 * m.m21 + m22 * m.m22;
}

void Matrix3x3::orthogonalize()
{
    Vector3 x(m00, m01, m02);
    x.normalize();

    Vector3 y(m10, m11, m12);
    y -= x * dot(y, x);
    y.normalize();

    // cross(x, y) should produce a unit vector, normalize just in case
    Vector3 z = cross(x, y);
    z.normalize();

    m00 = x.x;
    m01 = x.y;
    m02 = x.z;

    m10 = y.x;
    m11 = y.y;
    m12 = y.z;

    m20 = z.x;
    m21 = z.y;
    m22 = z.z;
}

void Matrix3x3::swap(Matrix3x3& other)
{
    std::swap(m00, other.m00);
    std::swap(m01, other.m01);
    std::swap(m02, other.m02);

    std::swap(m10, other.m10);
    std::swap(m11, other.m11);
    std::swap(m12, other.m12);

    std::swap(m20, other.m20);
    std::swap(m21, other.m21);
    std::swap(m22, other.m22);
}

const Vector3 product(const Vector3& v, const Matrix3x3& m)
{
    return Vector3(
        v.x * m.m00 + v.y * m.m10 + v.z * m.m20,
        v.x * m.m01 + v.y * m.m11 + v.z * m.m21,
        v.x * m.m02 + v.y * m.m12 + v.z * m.m22
    );
}

const Vector3 productT(const Vector3& v, const Matrix3x3& m)
{
    return Vector3(
        v.x * m.m00 + v.y * m.m01 + v.z * m.m02,
        v.x * m.m10 + v.y * m.m11 + v.z * m.m12,
        v.x * m.m20 + v.y * m.m21 + v.z * m.m22
    );
}

const Matrix3x3 product(const Matrix3x3& a, const Matrix3x3& b)
{
    Matrix3x3 m(a);
    m.multiplyBy(b);
    return m;
}

const Matrix3x3 productT(const Matrix3x3& a, const Matrix3x3& b)
{
    Matrix3x3 m(a);
    m.multiplyByT(b);
    return m;
}

const Matrix3x3 transpose(const Matrix3x3& m)
{
    return Matrix3x3(
        m.m00, m.m10, m.m20,
        m.m01, m.m11, m.m21,
        m.m02, m.m12, m.m22
    );
}
