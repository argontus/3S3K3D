/**
 * @file geometry/matrix3x3.h
 * @author Mika Haarahiltunen
 */

#include <geometry/matrix3x3.h>

// TODO: get rid of this #include
#include <algorithm>

#include <geometry/math.h>
#include <geometry/vector3.h>

const Matrix3x3 Matrix3x3::identity()
{
    return Matrix3x3(
        1.0f,  0.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
        0.0f,  0.0f,  1.0f
    );
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

const Vector3 Matrix3x3::row0() const
{
    return Vector3(m00, m01, m02);
}

const Vector3 Matrix3x3::row1() const
{
    return Vector3(m10, m11, m12);
}

const Vector3 Matrix3x3::row2() const
{
    return Vector3(m20, m21, m22);
}

float* Matrix3x3::data()
{
    return &m00;
}

const float* Matrix3x3::data() const
{
    return &m00;
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

const Matrix3x3 orthogonalize(const Matrix3x3& m)
{
    // TODO: In the worst case scenario, this could construct a matrix where
    // one or more rows are incorrectly set to Vector3(1.0f, 0.0f, 0.0f)
    // because of how normalize(const Vector3&) is implemented. Should this
    // function check for division by zero instead of relying on the default
    // behavior of vector normalization?

    const Vector3 x = normalize(m.row0());

    Vector3 y = m.row1();

    // extract the part that is parallel to x and normalize
    y -= x * dot(y, x);
    y = normalize(y);

    Vector3 z = m.row2();

    // extract the parts that are parallel to x and y and normalize
    z -= x * dot(z, x);
    z -= y * dot(z, y);
    z = normalize(z);

    return Matrix3x3(x, y, z);
}

const Matrix3x3 product(const Matrix3x3& a, const Matrix3x3& b)
{
    return Matrix3x3(
        a.m00 * b.m00 + a.m01 * b.m10 + a.m02 * b.m20,
        a.m00 * b.m01 + a.m01 * b.m11 + a.m02 * b.m21,
        a.m00 * b.m02 + a.m01 * b.m12 + a.m02 * b.m22,

        a.m10 * b.m00 + a.m11 * b.m10 + a.m12 * b.m20,
        a.m10 * b.m01 + a.m11 * b.m11 + a.m12 * b.m21,
        a.m10 * b.m02 + a.m11 * b.m12 + a.m12 * b.m22,

        a.m20 * b.m00 + a.m21 * b.m10 + a.m22 * b.m20,
        a.m20 * b.m01 + a.m21 * b.m11 + a.m22 * b.m21,
        a.m20 * b.m02 + a.m21 * b.m12 + a.m22 * b.m22
    );
}

const Matrix3x3 productT(const Matrix3x3& a, const Matrix3x3& b)
{
    return Matrix3x3(
        a.m00 * b.m00 + a.m01 * b.m01 + a.m02 * b.m02,
        a.m00 * b.m10 + a.m01 * b.m11 + a.m02 * b.m12,
        a.m00 * b.m20 + a.m01 * b.m21 + a.m02 * b.m22,

        a.m10 * b.m00 + a.m11 * b.m01 + a.m12 * b.m02,
        a.m10 * b.m10 + a.m11 * b.m11 + a.m12 * b.m12,
        a.m10 * b.m20 + a.m11 * b.m21 + a.m12 * b.m22,

        a.m20 * b.m00 + a.m21 * b.m01 + a.m22 * b.m02,
        a.m20 * b.m10 + a.m21 * b.m11 + a.m22 * b.m12,
        a.m20 * b.m20 + a.m21 * b.m21 + a.m22 * b.m22
    );
}

const Matrix3x3 transpose(const Matrix3x3& m)
{
    return Matrix3x3(
        m.m00, m.m10, m.m20,
        m.m01, m.m11, m.m21,
        m.m02, m.m12, m.m22
    );
}
