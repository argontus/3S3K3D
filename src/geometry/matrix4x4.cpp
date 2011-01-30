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

const Matrix4x4 Matrix4x4::transform(const Transform2& transform)
{
    const Vector2 t = transform.translation();
    const Matrix2x2 r = Matrix2x2::rotation(transform.rotation());
    const float s = transform.scaling();

    return Matrix4x4(
        r.m00 * s,  r.m01 * s,  0.0f,  0.0f,
        r.m10 * s,  r.m11 * s,  0.0f,  0.0f,
             0.0f,       0.0f,  1.0f,  0.0f,
              t.x,        t.y,  0.0f,  1.0f
    );
}

const Matrix4x4 Matrix4x4::transform(const Transform3& transform)
{
    const Vector3 t = transform.translation();
    const Matrix3x3 r = transform.rotation();
    const float s = transform.scaling();

    return Matrix4x4(
        r.m00 * s,  r.m01 * s,  r.m02 * s,  0.0f,
        r.m10 * s,  r.m11 * s,  r.m12 * s,  0.0f,
        r.m20 * s,  r.m21 * s,  r.m22 * s,  0.0f,
              t.x,        t.y,        t.z,  1.0f
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
    m00 = m00 * m.m00 + m01 * m.m10 + m02 * m.m20 + m03 * m.m30;
    m01 = m00 * m.m01 + m01 * m.m11 + m02 * m.m21 + m03 * m.m31;
    m02 = m00 * m.m02 + m01 * m.m12 + m02 * m.m22 + m03 * m.m32;
    m03 = m00 * m.m03 + m01 * m.m13 + m02 * m.m23 + m03 * m.m33;

    m10 = m10 * m.m00 + m11 * m.m10 + m12 * m.m20 + m13 * m.m30;
    m11 = m10 * m.m01 + m11 * m.m11 + m12 * m.m21 + m13 * m.m31;
    m12 = m10 * m.m02 + m11 * m.m12 + m12 * m.m22 + m13 * m.m32;
    m13 = m10 * m.m03 + m11 * m.m13 + m12 * m.m23 + m13 * m.m33;

    m20 = m20 * m.m00 + m21 * m.m10 + m22 * m.m20 + m23 * m.m30;
    m21 = m20 * m.m01 + m21 * m.m11 + m22 * m.m21 + m23 * m.m31;
    m22 = m20 * m.m02 + m21 * m.m12 + m22 * m.m22 + m23 * m.m32;
    m23 = m20 * m.m03 + m21 * m.m13 + m22 * m.m23 + m23 * m.m33;

    m30 = m30 * m.m00 + m31 * m.m10 + m32 * m.m20 + m33 * m.m30;
    m31 = m30 * m.m01 + m31 * m.m11 + m32 * m.m21 + m33 * m.m31;
    m32 = m30 * m.m02 + m31 * m.m12 + m32 * m.m22 + m33 * m.m32;
    m33 = m30 * m.m03 + m31 * m.m13 + m32 * m.m23 + m33 * m.m33;
}

void Matrix4x4::multiplyByT(const Matrix4x4& m)
{
    m00 = m00 * m.m00 + m01 * m.m01 + m02 * m.m02 + m03 * m.m03;
    m01 = m00 * m.m10 + m01 * m.m11 + m02 * m.m12 + m03 * m.m13;
    m02 = m00 * m.m20 + m01 * m.m21 + m02 * m.m22 + m03 * m.m23;
    m03 = m00 * m.m30 + m01 * m.m31 + m02 * m.m32 + m03 * m.m33;

    m10 = m10 * m.m00 + m11 * m.m01 + m12 * m.m02 + m13 * m.m03;
    m11 = m10 * m.m10 + m11 * m.m11 + m12 * m.m12 + m13 * m.m13;
    m12 = m10 * m.m20 + m11 * m.m21 + m12 * m.m22 + m13 * m.m23;
    m13 = m10 * m.m30 + m11 * m.m31 + m12 * m.m32 + m13 * m.m33;

    m20 = m20 * m.m00 + m21 * m.m01 + m22 * m.m02 + m23 * m.m03;
    m21 = m20 * m.m10 + m21 * m.m11 + m22 * m.m12 + m23 * m.m13;
    m22 = m20 * m.m20 + m21 * m.m21 + m22 * m.m22 + m23 * m.m23;
    m23 = m20 * m.m30 + m21 * m.m31 + m22 * m.m32 + m23 * m.m33;

    m30 = m30 * m.m00 + m31 * m.m01 + m32 * m.m02 + m33 * m.m03;
    m31 = m30 * m.m10 + m31 * m.m11 + m32 * m.m12 + m33 * m.m13;
    m32 = m30 * m.m20 + m31 * m.m21 + m32 * m.m22 + m33 * m.m23;
    m33 = m30 * m.m30 + m31 * m.m31 + m32 * m.m32 + m33 * m.m33;
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
    Matrix4x4 m(a);
    m.multiplyBy(b);
    return m;
}

const Matrix4x4 productT(const Matrix4x4& a, const Matrix4x4& b)
{
    Matrix4x4 m(a);
    m.multiplyByT(b);
    return m;
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
