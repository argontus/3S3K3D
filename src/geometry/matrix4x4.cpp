/**
 * @file geometry/matrix4x4.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/matrix4x4.h>

// TODO: get rid of this #include
#include <algorithm>

#include <geometry/math.h>
#include <geometry/vector3.h>
#include <geometry/vector4.h>

const Matrix4x4 Matrix4x4::identity()
{
    return Matrix4x4(
        1.0f,  0.0f,  0.0f,  0.0f,
        0.0f,  1.0f,  0.0f,  0.0f,
        0.0f,  0.0f,  1.0f,  0.0f,
        0.0f,  0.0f,  0.0f,  1.0f
    );
}

const Matrix4x4 Matrix4x4::translation(const Vector3& t)
{
    return Matrix4x4(
        1.0f,  0.0f,  0.0f,  0.0f,
        0.0f,  1.0f,  0.0f,  0.0f,
        0.0f,  0.0f,  1.0f,  0.0f,
         t.x,   t.y,   t.z,  1.0f
    );
}

const Matrix4x4 Matrix4x4::xRotation(const float rotation)
{
    const float c = Math::cos(rotation);
    const float s = Math::sin(rotation);

    return Matrix4x4(
        1.0f,  0.0f,  0.0f,  0.0f,
        0.0f,     c,     s,  0.0f,
        0.0f,    -s,     c,  0.0f,
        0.0f,  0.0f,  0.0f,  1.0f
    );
}

const Matrix4x4 Matrix4x4::yRotation(const float rotation)
{
    const float c = Math::cos(rotation);
    const float s = Math::sin(rotation);

    return Matrix4x4(
           c,  0.0f,    -s,  0.0f,
        0.0f,  1.0f,  0.0f,  0.0f,
           s,  0.0f,     c,  0.0f,
        0.0f,  0.0f,  0.0f,  1.0f
    );
}

const Matrix4x4 Matrix4x4::zRotation(const float rotation)
{
    const float c = Math::cos(rotation);
    const float s = Math::sin(rotation);

    return Matrix4x4(
           c,     s,  0.0f,  0.0f,
          -s,     c,  0.0f,  0.0f,
        0.0f,  0.0f,  1.0f,  0.0f,
        0.0f,  0.0f,  0.0f,  1.0f
    );
}

const Matrix4x4 Matrix4x4::rotation(const Vector3& axis, const float rotation)
{
    // TODO: not tested, does this work?

    const float c = Math::cos(rotation);
    const float s = Math::sin(rotation);
    const float k = 1.0f - c;

    const float x = axis.x;
    const float y = axis.y;
    const float z = axis.z;

    // let the compiler take care of common sub-expressions

    return Matrix4x4(
            x * x * k + c,  x * y * k + z * s,  x * z * k - y * s,  0.0f,
        x * y * k - z * s,      y * y * k + c,  y * z * k + x * s,  0.0f,
        x * z * k + y * s,  y * z * k - x * s,      z * z * k + c,  0.0f,
                     0.0f,               0.0f,               0.0f,  1.0f
    );
}

const Matrix4x4 Matrix4x4::scaling(const float s)
{
    return Matrix4x4(
           s, 0.0f, 0.0f, 0.0f,
        0.0f,    s, 0.0f, 0.0f,
        0.0f, 0.0f,    s, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

const Matrix4x4 Matrix4x4::scaling(
    const float sx,
    const float sy,
    const float sz)
{
    return Matrix4x4(
          sx, 0.0f, 0.0f, 0.0f,
        0.0f,   sy, 0.0f, 0.0f,
        0.0f, 0.0f,   sz, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

Matrix4x4::Matrix4x4()
{
    // ...
}

Matrix4x4::Matrix4x4(
    const float m00, const float m01, const float m02, const float m03,
    const float m10, const float m11, const float m12, const float m13,
    const float m20, const float m21, const float m22, const float m23,
    const float m30, const float m31, const float m32, const float m33)
:   m00(m00), m01(m01), m02(m02), m03(m03),
    m10(m10), m11(m11), m12(m12), m13(m13),
    m20(m20), m21(m21), m22(m22), m23(m23),
    m30(m30), m31(m31), m32(m32), m33(m33)
{
    // ...
}

Matrix4x4::Matrix4x4(
    const Vector4& row0,
    const Vector4& row1,
    const Vector4& row2,
    const Vector4& row3)
:   m00(row0.x), m01(row0.y), m02(row0.z), m03(row0.w),
    m10(row1.x), m11(row1.y), m12(row1.z), m13(row1.w),
    m20(row2.x), m21(row2.y), m22(row2.z), m23(row2.w),
    m30(row3.x), m31(row3.y), m32(row3.z), m33(row3.w)
{
    // ...
}

const Vector4 Matrix4x4::row0() const
{
    return Vector4(m00, m01, m02, m03);
}

const Vector4 Matrix4x4::row1() const
{
    return Vector4(m10, m11, m12, m13);
}

const Vector4 Matrix4x4::row2() const
{
    return Vector4(m20, m21, m22, m23);
}

const Vector4 Matrix4x4::row3() const
{
    return Vector4(m30, m31, m32, m33);
}

float* Matrix4x4::data()
{
    return &m00;
}

const float* Matrix4x4::data() const
{
    return &m00;
}

void Matrix4x4::swap(Matrix4x4& other)
{
    std::swap(m00, other.m00);
    std::swap(m01, other.m01);
    std::swap(m02, other.m02);
    std::swap(m03, other.m03);

    std::swap(m10, other.m10);
    std::swap(m11, other.m11);
    std::swap(m12, other.m12);
    std::swap(m13, other.m13);

    std::swap(m20, other.m20);
    std::swap(m21, other.m21);
    std::swap(m22, other.m22);
    std::swap(m23, other.m23);

    std::swap(m30, other.m30);
    std::swap(m31, other.m31);
    std::swap(m32, other.m32);
    std::swap(m33, other.m33);
}

const Vector4 product(const Vector4& v, const Matrix4x4& m)
{
    return Vector4(
        v.x * m.m00 + v.y * m.m10 + v.z * m.m20 + v.w * m.m30,
        v.x * m.m01 + v.y * m.m11 + v.z * m.m21 + v.w * m.m31,
        v.x * m.m02 + v.y * m.m12 + v.z * m.m22 + v.w * m.m32,
        v.x * m.m03 + v.y * m.m13 + v.z * m.m23 + v.w * m.m33
    );
}

const Vector4 productT(const Vector4& v, const Matrix4x4& m)
{
    return Vector4(
        v.x * m.m00 + v.y * m.m01 + v.z * m.m02 + v.w * m.m03,
        v.x * m.m10 + v.y * m.m11 + v.z * m.m12 + v.w * m.m13,
        v.x * m.m20 + v.y * m.m21 + v.z * m.m22 + v.w * m.m23,
        v.x * m.m30 + v.y * m.m31 + v.z * m.m32 + v.w * m.m33
    );
}

const Matrix4x4 orthogonalize(const Matrix4x4& m)
{
    // TODO: In the worst case scenario, this could construct a matrix where
    // one or more rows are incorrectly set to Vector4(1.0f, 0.0f, 0.0f, 0.0f)
    // because of how normalize(const Vector4&) is implemented. Should this
    // function check for division by zero instead of relying on the default
    // behavior of vector normalization?

    const Vector4 x = normalize(m.row0());

    Vector4 y = m.row1();

    // extract the part that is parallel to x and normalize
    y -= x * dot(y, x);
    y = normalize(y);

    Vector4 z = m.row2();

    // extract the parts that are parallel to x and y and normalize
    z -= x * dot(z, x);
    z -= y * dot(z, y);
    z = normalize(z);

    Vector4 w = m.row3();

    // extract the parts that are parallel to x, y and z and normalize
    w -= x * dot(w, x);
    w -= y * dot(w, y);
    w -= z * dot(w, z);
    w = normalize(w);

    return Matrix4x4(x, y, z, w);
}

const Matrix4x4 product(const Matrix4x4& a, const Matrix4x4& b)
{
    return Matrix4x4(
        a.m00 * b.m00 + a.m01 * b.m10 + a.m02 * b.m20 + a.m03 * b.m30,
        a.m00 * b.m01 + a.m01 * b.m11 + a.m02 * b.m21 + a.m03 * b.m31,
        a.m00 * b.m02 + a.m01 * b.m12 + a.m02 * b.m22 + a.m03 * b.m32,
        a.m00 * b.m03 + a.m01 * b.m13 + a.m02 * b.m23 + a.m03 * b.m33,

        a.m10 * b.m00 + a.m11 * b.m10 + a.m12 * b.m20 + a.m13 * b.m30,
        a.m10 * b.m01 + a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31,
        a.m10 * b.m02 + a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32,
        a.m10 * b.m03 + a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33,

        a.m20 * b.m00 + a.m21 * b.m10 + a.m22 * b.m20 + a.m23 * b.m30,
        a.m20 * b.m01 + a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31,
        a.m20 * b.m02 + a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32,
        a.m20 * b.m03 + a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33,

        a.m30 * b.m00 + a.m31 * b.m10 + a.m32 * b.m20 + a.m33 * b.m30,
        a.m30 * b.m01 + a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31,
        a.m30 * b.m02 + a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32,
        a.m30 * b.m03 + a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33
    );
}

const Matrix4x4 productT(const Matrix4x4& a, const Matrix4x4& b)
{
    return Matrix4x4(
        a.m00 * b.m00 + a.m01 * b.m01 + a.m02 * b.m02 + a.m03 * b.m03,
        a.m00 * b.m10 + a.m01 * b.m11 + a.m02 * b.m12 + a.m03 * b.m13,
        a.m00 * b.m20 + a.m01 * b.m21 + a.m02 * b.m22 + a.m03 * b.m23,
        a.m00 * b.m30 + a.m01 * b.m31 + a.m02 * b.m32 + a.m03 * b.m33,

        a.m10 * b.m00 + a.m11 * b.m01 + a.m12 * b.m02 + a.m13 * b.m03,
        a.m10 * b.m10 + a.m11 * b.m11 + a.m12 * b.m12 + a.m13 * b.m13,
        a.m10 * b.m20 + a.m11 * b.m21 + a.m12 * b.m22 + a.m13 * b.m23,
        a.m10 * b.m30 + a.m11 * b.m31 + a.m12 * b.m32 + a.m13 * b.m33,

        a.m20 * b.m00 + a.m21 * b.m01 + a.m22 * b.m02 + a.m23 * b.m03,
        a.m20 * b.m10 + a.m21 * b.m11 + a.m22 * b.m12 + a.m23 * b.m13,
        a.m20 * b.m20 + a.m21 * b.m21 + a.m22 * b.m22 + a.m23 * b.m23,
        a.m20 * b.m30 + a.m21 * b.m31 + a.m22 * b.m32 + a.m23 * b.m33,

        a.m30 * b.m00 + a.m31 * b.m01 + a.m32 * b.m02 + a.m33 * b.m03,
        a.m30 * b.m10 + a.m31 * b.m11 + a.m32 * b.m12 + a.m33 * b.m13,
        a.m30 * b.m20 + a.m31 * b.m21 + a.m32 * b.m22 + a.m33 * b.m23,
        a.m30 * b.m30 + a.m31 * b.m31 + a.m32 * b.m32 + a.m33 * b.m33
    );
}

const Matrix4x4 transpose(const Matrix4x4& m)
{
    return Matrix4x4(
        m.m00, m.m10, m.m20, m.m30,
        m.m01, m.m11, m.m21, m.m31,
        m.m02, m.m12, m.m22, m.m32,
        m.m03, m.m13, m.m23, m.m33
    );
}
