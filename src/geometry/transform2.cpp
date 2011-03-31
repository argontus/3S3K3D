/**
 * @file geometry/transform2.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/transform2.h>

#include <geometry/math.h>
#include <geometry/matrix2x2.h>
#include <geometry/matrix4x4.h>

const Transform2 Transform2::identity()
{
    return Transform2(Vector2::zero(), Matrix2x2::identity(), 1.0f);
}

Transform2::Transform2()
:   translation(Vector2::zero()),
    rotation(Matrix2x2::identity()),
    scaling(1.0f)
{
    // ...
}

Transform2::Transform2(
    const Vector2& translation,
    const Matrix2x2& rotation,
    const float scaling)
:   translation(translation),
    rotation(rotation),
    scaling(scaling)
{
    GEOMETRY_RUNTIME_ASSERT(scaling > 0.0f);
}

void Transform2::swap(Transform2& other)
{
    translation.swap(other.translation);
    rotation.swap(other.rotation);
    Math::swap(scaling, other.scaling);
}

const Vector2 transform(const Vector2& q, const Transform2& t)
{
    GEOMETRY_RUNTIME_ASSERT(t.scaling > 0.0f);
    return (t.scaling * q) * t.rotation + t.translation;
}

const Vector2 transformByInverse(const Vector2& q, const Transform2& t)
{
    GEOMETRY_RUNTIME_ASSERT(t.scaling > 0.0f);
    return timesTranspose(q - t.translation, t.rotation) / t.scaling;
}

const Matrix4x4 toMatrix4x4(const Transform2& transform)
{
    const Vector2 t = transform.translation;
    const Matrix2x2 r = transform.rotation;
    const float s = transform.scaling;

    return Matrix4x4(
        r.m00 * s,  r.m01 * s,  0.0f,  0.0f,
        r.m10 * s,  r.m11 * s,  0.0f,  0.0f,
             0.0f,       0.0f,  1.0f,  0.0f,
              t.x,        t.y,  0.0f,  1.0f
    );
}

const Transform2 inverse(const Transform2& t)
{
    GEOMETRY_RUNTIME_ASSERT(t.scaling > 0.0f);

    const Matrix2x2 r = transpose(t.rotation);
    const float s = 1.0f / t.scaling;

    return Transform2(
        (-s * t.translation) * r,
        r,
        s
    );
}

const Transform2 slerp(const Transform2& a, const Transform2& b, const float t)
{
    GEOMETRY_RUNTIME_ASSERT(a.scaling > 0.0f);
    GEOMETRY_RUNTIME_ASSERT(b.scaling > 0.0f);

    return Transform2(
        mix(a.translation, b.translation, t),
        slerp(a.rotation, b.rotation, t),
        Math::mix(a.scaling, b.scaling, t)
    );
}

const Transform2 transform(const Transform2& a, const Transform2& b)
{
    GEOMETRY_RUNTIME_ASSERT(a.scaling > 0.0f);
    GEOMETRY_RUNTIME_ASSERT(b.scaling > 0.0f);

    return Transform2(
        transform(a.translation, b),
        a.rotation * b.rotation,
        a.scaling * b.scaling
    );
}

const Transform2 transformByInverse(const Transform2& a, const Transform2& b)
{
    GEOMETRY_RUNTIME_ASSERT(a.scaling > 0.0f);
    GEOMETRY_RUNTIME_ASSERT(b.scaling > 0.0f);

    return Transform2(
        transformByInverse(a.translation, b),
        timesTranspose(a.rotation, b.rotation),
        a.scaling / b.scaling
    );
}

const Transform2 transformInverseBy(const Transform2& a, const Transform2& b)
{
    GEOMETRY_RUNTIME_ASSERT(a.scaling > 0.0f);
    GEOMETRY_RUNTIME_ASSERT(b.scaling > 0.0f);

    const Matrix2x2 r = transposeTimes(a.rotation, b.rotation);
    const float s = b.scaling / a.scaling;

    return Transform2(
        (-s * a.translation) * r + b.translation,
        r,
        s
    );
}
