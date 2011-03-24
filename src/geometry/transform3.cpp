/**
 * @file geometry/transform3.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/transform3.h>

#include <geometry/math.h>
#include <geometry/matrix3x3.h>
#include <geometry/matrix4x4.h>

const Transform3 Transform3::identity()
{
    return Transform3(Vector3::zero(), Matrix3x3::identity(), 1.0f);
}

Transform3::Transform3()
:   translation(Vector3::zero()),
    rotation(Matrix3x3::identity()),
    scaling(1.0f)
{
    // ...
}

Transform3::Transform3(
    const Vector3& translation,
    const Matrix3x3& rotation,
    const float scaling)
:   translation(translation),
    rotation(rotation),
    scaling(scaling)
{
    GEOMETRY_RUNTIME_ASSERT(scaling > 0.0f);
}

void Transform3::swap(Transform3& other)
{
    translation.swap(other.translation);
    rotation.swap(other.rotation);
    Math::swap(scaling, other.scaling);
}

const Vector3 transform(const Vector3& q, const Transform3& t)
{
    GEOMETRY_RUNTIME_ASSERT(t.scaling > 0.0f);
    return (t.scaling * q) * t.rotation + t.translation;
}

const Vector3 transformByInverse(const Vector3& q, const Transform3& t)
{
    GEOMETRY_RUNTIME_ASSERT(t.scaling > 0.0f);
    return timesTranspose(q - t.translation, t.rotation) / t.scaling;
}

const Matrix4x4 toMatrix4x4(const Transform3& transform)
{
    const Vector3 t = transform.translation;
    const Matrix3x3 r = transform.rotation;
    const float s = transform.scaling;

    return Matrix4x4(
        r.m00 * s,  r.m01 * s,  r.m02 * s,  0.0f,
        r.m10 * s,  r.m11 * s,  r.m12 * s,  0.0f,
        r.m20 * s,  r.m21 * s,  r.m22 * s,  0.0f,
              t.x,        t.y,        t.z,  1.0f
    );
}

const Transform3 inverse(const Transform3& t)
{
    GEOMETRY_RUNTIME_ASSERT(t.scaling > 0.0f);

    const Matrix3x3 r = transpose(t.rotation);
    const float s = 1.0f / t.scaling;

    return Transform3(
        (-s * t.translation) * r,
        r,
        s
    );
}

const Transform3 transform(const Transform3& a, const Transform3& b)
{
    GEOMETRY_RUNTIME_ASSERT(a.scaling > 0.0f);
    GEOMETRY_RUNTIME_ASSERT(b.scaling > 0.0f);

    return Transform3(
        transform(a.translation, b),
        a.rotation * b.rotation,
        a.scaling * b.scaling
    );
}

const Transform3 transformByInverse(const Transform3& a, const Transform3& b)
{
    GEOMETRY_RUNTIME_ASSERT(a.scaling > 0.0f);
    GEOMETRY_RUNTIME_ASSERT(b.scaling > 0.0f);

    return Transform3(
        transformByInverse(a.translation, b),
        timesTranspose(a.rotation, b.rotation),
        a.scaling / b.scaling
    );
}

const Transform3 transformInverseBy(const Transform3& a, const Transform3& b)
{
    GEOMETRY_RUNTIME_ASSERT(a.scaling > 0.0f);
    GEOMETRY_RUNTIME_ASSERT(b.scaling > 0.0f);

    const Matrix3x3 r = transposeTimes(a.rotation, b.rotation);
    const float s = b.scaling / a.scaling;

    return Transform3(
        (-s * a.translation) * r + b.translation,
        r,
        s
    );
}
