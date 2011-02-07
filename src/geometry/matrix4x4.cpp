/**
 * @file geometry/matrix4x4.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/matrix4x4.h>

#include <algorithm>

#include <geometry/math.h>
#include <geometry/transform2.h>
#include <geometry/transform3.h>

const Matrix4x4& Matrix4x4::identity()
{
    static const Matrix4x4 m(
        1.0f,  0.0f,  0.0f,  0.0f,
        0.0f,  1.0f,  0.0f,  0.0f,
        0.0f,  0.0f,  1.0f,  0.0f,
        0.0f,  0.0f,  0.0f,  1.0f
    );

    return m;
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

Matrix4x4::Matrix4x4(const Matrix2x2& m)
:   m00(m.m00), m01(m.m01), m02(0.0f), m03(0.0f),
    m10(m.m10), m11(m.m11), m12(0.0f), m13(0.0f),
    m20(0.0f), m21(0.0f), m22(1.0f), m23(0.0f),
    m30(0.0f), m31(0.0f), m32(0.0f), m33(1.0f)
{
    // ...
}

Matrix4x4::Matrix4x4(const Matrix3x3& m)
:   m00(m.m00), m01(m.m01), m02(m.m02), m03(0.0f),
    m10(m.m10), m11(m.m11), m12(m.m12), m13(0.0f),
    m20(m.m20), m21(m.m21), m22(m.m22), m23(0.0f),
    m30(0.0f), m31(0.0f), m32(0.0f), m33(1.0f)
{
    // ...
}

Matrix4x4::Matrix4x4(const Transform2& transform)
{
    const Vector2 t = transform.translation();
    const Matrix2x2 r = Matrix2x2::rotation(transform.rotation());
    const float s = transform.scaling();

    *this = Matrix4x4(
        r.m00 * s,  r.m01 * s,  0.0f,  0.0f,
        r.m10 * s,  r.m11 * s,  0.0f,  0.0f,
             0.0f,       0.0f,  1.0f,  0.0f,
              t.x,        t.y,  0.0f,  1.0f
    );
}

Matrix4x4::Matrix4x4(const Transform3& transform)
{
    const Vector3 t = transform.translation();
    const Matrix3x3 r = transform.rotation();
    const float s = transform.scaling();

    *this = Matrix4x4(
        r.m00 * s,  r.m01 * s,  r.m02 * s,  0.0f,
        r.m10 * s,  r.m11 * s,  r.m12 * s,  0.0f,
        r.m20 * s,  r.m21 * s,  r.m22 * s,  0.0f,
              t.x,        t.y,        t.z,  1.0f
    );
}

float* Matrix4x4::operator [](const int row)
{
    GEOMETRY_RUNTIME_ASSERT(row >= 0 && row <= 3);
    return &m00 + row * 4;
}

const float* Matrix4x4::operator [](const int row) const
{
    GEOMETRY_RUNTIME_ASSERT(row >= 0 && row <= 3);
    return &m00 + row * 4;
}

float* Matrix4x4::data()
{
    return &m00;
}

const float* Matrix4x4::data() const
{
    return &m00;
}

void Matrix4x4::multiplyBy(const Matrix4x4& m)
{
    *this = product(*this, m);
}

void Matrix4x4::multiplyByT(const Matrix4x4& m)
{
    *this = productT(*this, m);
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
