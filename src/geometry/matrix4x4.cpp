/**
 * @file geometry/matrix4x4.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/matrix4x4.h>

#include <geometry/math.h>
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

Matrix4x4& Matrix4x4::operator +=(const Matrix4x4& m)
{
    *this = *this + m;
    return *this;
}

Matrix4x4& Matrix4x4::operator -=(const Matrix4x4& m)
{
    *this = *this - m;
    return *this;
}

Matrix4x4& Matrix4x4::operator *=(const float k)
{
    *this = *this * k;
    return *this;
}

Matrix4x4& Matrix4x4::operator *=(const Matrix4x4& m)
{
    *this = *this * m;
    return *this;
}

Matrix4x4& Matrix4x4::operator /=(const float k)
{
    // TODO: use tolerances instead of exact values?
    GEOMETRY_RUNTIME_ASSERT(k != 0.0f);

    *this = *this / k;
    return *this;
}

float* Matrix4x4::data()
{
    return &m00;
}

const float* Matrix4x4::data() const
{
    return &m00;
}

const Vector4 Matrix4x4::row(const int index) const
{
    GEOMETRY_RUNTIME_ASSERT(index >= 0 && index <= 3);

    const float* const v = data() + 4 * index;
    return Vector4(v[0], v[1], v[2], v[3]);
}

void Matrix4x4::swap(Matrix4x4& other)
{
    Math::swap(m00, other.m00);
    Math::swap(m01, other.m01);
    Math::swap(m02, other.m02);
    Math::swap(m03, other.m03);

    Math::swap(m10, other.m10);
    Math::swap(m11, other.m11);
    Math::swap(m12, other.m12);
    Math::swap(m13, other.m13);

    Math::swap(m20, other.m20);
    Math::swap(m21, other.m21);
    Math::swap(m22, other.m22);
    Math::swap(m23, other.m23);

    Math::swap(m30, other.m30);
    Math::swap(m31, other.m31);
    Math::swap(m32, other.m32);
    Math::swap(m33, other.m33);
}

const Vector4 operator *(const Vector4& v, const Matrix4x4& m)
{
    return Vector4(
        v.x * m.m00 + v.y * m.m10 + v.z * m.m20 + v.w * m.m30,
        v.x * m.m01 + v.y * m.m11 + v.z * m.m21 + v.w * m.m31,
        v.x * m.m02 + v.y * m.m12 + v.z * m.m22 + v.w * m.m32,
        v.x * m.m03 + v.y * m.m13 + v.z * m.m23 + v.w * m.m33
    );
}

const Matrix4x4 operator +(const Matrix4x4& a, const Matrix4x4& b)
{
    return Matrix4x4(
        a.m00 + b.m00, a.m01 + b.m01, a.m02 + b.m02, a.m03 + b.m03,
        a.m10 + b.m10, a.m11 + b.m11, a.m12 + b.m12, a.m13 + b.m13,
        a.m20 + b.m20, a.m21 + b.m21, a.m22 + b.m22, a.m23 + b.m23,
        a.m30 + b.m30, a.m31 + b.m31, a.m32 + b.m32, a.m33 + b.m33
    );
}

const Matrix4x4 operator -(const Matrix4x4& m)
{
    return Matrix4x4(
        -m.m00, -m.m01, -m.m02, -m.m03,
        -m.m10, -m.m11, -m.m12, -m.m13,
        -m.m20, -m.m21, -m.m22, -m.m23,
        -m.m30, -m.m31, -m.m32, -m.m33
    );
}

const Matrix4x4 operator -(const Matrix4x4& a, const Matrix4x4& b)
{
    return Matrix4x4(
        a.m00 - b.m00, a.m01 - b.m01, a.m02 - b.m02, a.m03 - b.m03,
        a.m10 - b.m10, a.m11 - b.m11, a.m12 - b.m12, a.m13 - b.m13,
        a.m20 - b.m20, a.m21 - b.m21, a.m22 - b.m22, a.m23 - b.m23,
        a.m30 - b.m30, a.m31 - b.m31, a.m32 - b.m32, a.m33 - b.m33
    );
}

const Matrix4x4 operator *(const float k, const Matrix4x4& m)
{
    return Matrix4x4(
        k * m.m00, k * m.m01, k * m.m02, k * m.m03,
        k * m.m10, k * m.m11, k * m.m12, k * m.m13,
        k * m.m20, k * m.m21, k * m.m22, k * m.m23,
        k * m.m30, k * m.m31, k * m.m32, k * m.m33
    );
}

const Matrix4x4 operator *(const Matrix4x4& m, const float k)
{
    return k * m;
}

const Matrix4x4 operator *(const Matrix4x4& a, const Matrix4x4& b)
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

const Matrix4x4 operator /(const Matrix4x4& m, const float k)
{
    // TODO: use tolerances instead of exact values?
    GEOMETRY_RUNTIME_ASSERT(k != 0.0f);

    return Matrix4x4(
        m.m00 / k, m.m01 / k, m.m02 / k, m.m03 / k,
        m.m10 / k, m.m11 / k, m.m12 / k, m.m13 / k,
        m.m20 / k, m.m21 / k, m.m22 / k, m.m23 / k,
        m.m30 / k, m.m31 / k, m.m32 / k, m.m33 / k
    );
}

float determinant(const Matrix4x4& m)
{
    const float a0 = m.m00 * m.m11 - m.m01 * m.m10;
    const float a1 = m.m00 * m.m12 - m.m02 * m.m10;
    const float a2 = m.m00 * m.m13 - m.m03 * m.m10;
    const float a3 = m.m01 * m.m12 - m.m02 * m.m11;
    const float a4 = m.m01 * m.m13 - m.m03 * m.m11;
    const float a5 = m.m02 * m.m13 - m.m03 * m.m12;

    const float b0 = m.m20 * m.m31 - m.m21 * m.m30;
    const float b1 = m.m20 * m.m32 - m.m22 * m.m30;
    const float b2 = m.m20 * m.m33 - m.m23 * m.m30;
    const float b3 = m.m21 * m.m32 - m.m22 * m.m31;
    const float b4 = m.m21 * m.m33 - m.m23 * m.m31;
    const float b5 = m.m22 * m.m33 - m.m23 * m.m32;

    return a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;

}

const Vector4 timesTranspose(const Vector4& v, const Matrix4x4& m)
{
    return Vector4(
        v.x * m.m00 + v.y * m.m01 + v.z * m.m02 + v.w * m.m03,
        v.x * m.m10 + v.y * m.m11 + v.z * m.m12 + v.w * m.m13,
        v.x * m.m20 + v.y * m.m21 + v.z * m.m22 + v.w * m.m23,
        v.x * m.m30 + v.y * m.m31 + v.z * m.m32 + v.w * m.m33
    );
}

const Matrix4x4 adjoint(const Matrix4x4& m)
{
    const float a0 = m.m00 * m.m11 - m.m01 * m.m10;
    const float a1 = m.m00 * m.m12 - m.m02 * m.m10;
    const float a2 = m.m00 * m.m13 - m.m03 * m.m10;
    const float a3 = m.m01 * m.m12 - m.m02 * m.m11;
    const float a4 = m.m01 * m.m13 - m.m03 * m.m11;
    const float a5 = m.m02 * m.m13 - m.m03 * m.m12;

    const float b0 = m.m20 * m.m31 - m.m21 * m.m30;
    const float b1 = m.m20 * m.m32 - m.m22 * m.m30;
    const float b2 = m.m20 * m.m33 - m.m23 * m.m30;
    const float b3 = m.m21 * m.m32 - m.m22 * m.m31;
    const float b4 = m.m21 * m.m33 - m.m23 * m.m31;
    const float b5 = m.m22 * m.m33 - m.m23 * m.m32;

    return Matrix4x4
    (
        + m.m11 * b5 - m.m12 * b4 + m.m13 * b3,
        - m.m01 * b5 + m.m02 * b4 - m.m03 * b3,
        + m.m31 * a5 - m.m32 * a4 + m.m33 * a3,
        - m.m21 * a5 + m.m22 * a4 - m.m23 * a3,
        - m.m10 * b5 + m.m12 * b2 - m.m13 * b1,
        + m.m00 * b5 - m.m02 * b2 + m.m03 * b1,
        - m.m30 * a5 + m.m32 * a2 - m.m33 * a1,
        + m.m20 * a5 - m.m22 * a2 + m.m23 * a1,
        + m.m10 * b4 - m.m11 * b2 + m.m13 * b0,
        - m.m00 * b4 + m.m01 * b2 - m.m03 * b0,
        + m.m30 * a4 - m.m31 * a2 + m.m33 * a0,
        - m.m20 * a4 + m.m21 * a2 - m.m23 * a0,
        - m.m10 * b3 + m.m11 * b1 - m.m12 * b0,
        + m.m00 * b3 - m.m01 * b1 + m.m02 * b0,
        - m.m30 * a3 + m.m31 * a1 - m.m32 * a0,
        + m.m20 * a3 - m.m21 * a1 + m.m22 * a0
    );
}

const Matrix4x4 inverse(const Matrix4x4& m)
{
    const float det = determinant(m);

    // TODO: use tolerances instead of absolute values?
    GEOMETRY_RUNTIME_ASSERT(det != 0.0f);

    return 1.0f / det * adjoint(m);
}

const Matrix4x4 orthogonalize(const Matrix4x4& m)
{
    // TODO: In the worst case scenario, this could construct a matrix where
    // one or more rows are incorrectly set to Vector4(1.0f, 0.0f, 0.0f, 0.0f)
    // because of how normalize(const Vector4&) is implemented. Should this
    // function check for division by zero instead of relying on the default
    // behavior of vector normalization?

    const Vector4 x = normalize(m.row(0));

    Vector4 y = m.row(1);

    // extract the part that is parallel to x and normalize
    y -= x * dot(y, x);
    y = normalize(y);

    Vector4 z = m.row(2);

    // extract the parts that are parallel to x and y and normalize
    z -= x * dot(z, x);
    z -= y * dot(z, y);
    z = normalize(z);

    Vector4 w = m.row(3);

    // extract the parts that are parallel to x, y and z and normalize
    w -= x * dot(w, x);
    w -= y * dot(w, y);
    w -= z * dot(w, z);
    w = normalize(w);

    return Matrix4x4(x, y, z, w);
}

const Matrix4x4 timesTranspose(const Matrix4x4& a, const Matrix4x4& b)
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

const Matrix4x4 transposeTimes(const Matrix4x4& a, const Matrix4x4& b)
{
    return Matrix4x4(
        a.m00 * b.m00 + a.m10 * b.m10 + a.m20 * b.m20 + a.m30 * b.m30,
        a.m00 * b.m01 + a.m10 * b.m11 + a.m20 * b.m21 + a.m30 * b.m31,
        a.m00 * b.m02 + a.m10 * b.m12 + a.m20 * b.m22 + a.m30 * b.m32,
        a.m00 * b.m03 + a.m10 * b.m13 + a.m20 * b.m23 + a.m30 * b.m33,

        a.m01 * b.m00 + a.m11 * b.m10 + a.m21 * b.m20 + a.m31 * b.m30,
        a.m01 * b.m01 + a.m11 * b.m11 + a.m21 * b.m21 + a.m31 * b.m31,
        a.m01 * b.m02 + a.m11 * b.m12 + a.m21 * b.m22 + a.m31 * b.m32,
        a.m01 * b.m03 + a.m11 * b.m13 + a.m21 * b.m23 + a.m31 * b.m33,

        a.m02 * b.m00 + a.m12 * b.m10 + a.m22 * b.m20 + a.m32 * b.m30,
        a.m02 * b.m01 + a.m12 * b.m11 + a.m22 * b.m21 + a.m32 * b.m31,
        a.m02 * b.m02 + a.m12 * b.m12 + a.m22 * b.m22 + a.m32 * b.m32,
        a.m02 * b.m03 + a.m12 * b.m13 + a.m22 * b.m23 + a.m32 * b.m33,

        a.m03 * b.m00 + a.m13 * b.m10 + a.m23 * b.m20 + a.m33 * b.m30,
        a.m03 * b.m01 + a.m13 * b.m11 + a.m23 * b.m21 + a.m33 * b.m31,
        a.m03 * b.m02 + a.m13 * b.m12 + a.m23 * b.m22 + a.m33 * b.m32,
        a.m03 * b.m03 + a.m13 * b.m13 + a.m23 * b.m23 + a.m33 * b.m33
    );
}
