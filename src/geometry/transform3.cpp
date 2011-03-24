/**
 * @file geometry/transform3.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/transform3.h>

#include <geometry/math.h>
#include <geometry/matrix3x3.h>
#include <geometry/matrix4x4.h>

const Transform3& Transform3::identity()
{
    static const Transform3 transform(
        Vector3::zero(),
        Matrix3x3::identity(),
        1.0f
    );

    return transform;
}

const Transform3 Transform3::translation(const Vector3& translation)
{
    return Transform3(
        translation,
        Matrix3x3::identity(),
        1.0f
    );
}

const Transform3 Transform3::xRotation(const float rotation)
{
    return Transform3(
        Vector3::zero(),
        Matrix3x3::xRotation(rotation),
        1.0f
    );
}

const Transform3 Transform3::yRotation(const float rotation)
{
    return Transform3(
        Vector3::zero(),
        Matrix3x3::yRotation(rotation),
        1.0f
    );
}

const Transform3 Transform3::zRotation(const float rotation)
{
    return Transform3(
        Vector3::zero(),
        Matrix3x3::zRotation(rotation),
        1.0f
    );
}

const Transform3 Transform3::rotation(
    const Vector3& axis,
    const float rotation)
{
    return Transform3(
        Vector3::zero(),
        Matrix3x3::rotation(axis, rotation),
        1.0f
    );
}

const Transform3 Transform3::scaling(const float scaling)
{
    GEOMETRY_RUNTIME_ASSERT(scaling > 0.0f);

    return Transform3(
        Vector3::zero(),
        Matrix3x3::identity(),
        scaling
    );
}

Transform3::Transform3()
:   translation_(Vector3::zero()),
    rotation_(Matrix3x3::identity()),
    scaling_(1.0f)
{
    // ...
}

Transform3::Transform3(
    const Vector3& translation,
    const Matrix3x3& rotation,
    const float scaling)
:   translation_(translation),
    rotation_(rotation),
    scaling_(scaling)
{
    GEOMETRY_RUNTIME_ASSERT(scaling_ > 0.0f);
}

void Transform3::transformBy(const Transform3& transform)
{
    GEOMETRY_RUNTIME_ASSERT(scaling_ > 0.0f);
    GEOMETRY_RUNTIME_ASSERT(transform.scaling_ > 0.0f);

    translation_ = transform.applyForward(translation_);
    rotation_ *= transform.rotation_;
    scaling_ *= transform.scaling_;
}

void Transform3::setTranslation(const Vector3& translation)
{
    translation_ = translation;
}

void Transform3::translateBy(const Vector3& translation)
{
    translation_ += translation;
}

const Vector3 Transform3::translation() const
{
    return translation_;
}

void Transform3::setRotation(const Matrix3x3& rotation)
{
    rotation_ = rotation;
}

void Transform3::rotateBy(const Matrix3x3& rotation)
{
    rotation_ *= rotation;
}

const Matrix3x3 Transform3::rotation() const
{
    return rotation_;
}

void Transform3::setScaling(const float scaling)
{
    GEOMETRY_RUNTIME_ASSERT(scaling > 0.0f);
    scaling_ = scaling;
}

void Transform3::scaleBy(const float scaling)
{
    GEOMETRY_RUNTIME_ASSERT(scaling > 0.0f);
    scaling_ *= scaling;
}

float Transform3::scaling() const
{
    return scaling_;
}

const Matrix4x4 Transform3::toMatrix4x4() const
{
    const Vector3 t = translation_;
    const Matrix3x3 r = rotation_;
    const float s = scaling_;

    return Matrix4x4(
        r.m00 * s,  r.m01 * s,  r.m02 * s,  0.0f,
        r.m10 * s,  r.m11 * s,  r.m12 * s,  0.0f,
        r.m20 * s,  r.m21 * s,  r.m22 * s,  0.0f,
              t.x,        t.y,        t.z,  1.0f
    );
}

const Vector3 Transform3::applyForward(const Vector3& q) const
{
    GEOMETRY_RUNTIME_ASSERT(scaling_ > 0.0f);
    return (scaling_ * q) * rotation_ + translation_;
}

const Vector3 Transform3::applyInverse(const Vector3& q) const
{
    GEOMETRY_RUNTIME_ASSERT(scaling_ > 0.0f);
    return timesTranspose(q - translation_, rotation_) / scaling_;
}

void Transform3::swap(Transform3& other)
{
    translation_.swap(other.translation_);
    rotation_.swap(other.rotation_);
    Math::swap(scaling_, other.scaling_);
}

const Transform3 conversion(const Transform3& src, const Transform3& dst)
{
    GEOMETRY_RUNTIME_ASSERT(src.scaling() > 0.0f);
    GEOMETRY_RUNTIME_ASSERT(dst.scaling() > 0.0f);

    return Transform3(
        dst.applyInverse(src.translation()),
        timesTranspose(src.rotation(), dst.rotation()),
        src.scaling() / dst.scaling()
    );
}

const Transform3 product(const Transform3& a, const Transform3& b)
{
    GEOMETRY_RUNTIME_ASSERT(a.scaling() > 0.0f);
    GEOMETRY_RUNTIME_ASSERT(b.scaling() > 0.0f);

    return Transform3(
        b.applyForward(a.translation()),
        a.rotation() * b.rotation(),
        a.scaling() * b.scaling()
    );
}

const Transform3 invert(const Transform3& t)
{
    GEOMETRY_RUNTIME_ASSERT(t.scaling() > 0.0f);

    // inverse rotation and scaling
    const Matrix3x3 invRotation = transpose(t.rotation());
    const float invScaling = 1.0f / t.scaling();

    return Transform3(
        (-invScaling * t.translation()) * invRotation,
        invRotation,
        invScaling
    );
}
