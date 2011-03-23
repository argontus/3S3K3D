/**
 * @file geometry/transform2.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/transform2.h>

#include <geometry/math.h>
#include <geometry/matrix2x2.h>
#include <geometry/matrix4x4.h>

const Transform2& Transform2::identity()
{
    static const Transform2 transform(Vector2::zero(), 0.0f, 1.0f);
    return transform;
}

const Transform2 Transform2::translation(const Vector2& translation)
{
    return Transform2(translation, 0.0f, 1.0);
}

const Transform2 Transform2::rotation(const float rotation)
{
    return Transform2(Vector2::zero(), rotation, 1.0f);
}

const Transform2 Transform2::scaling(const float scaling)
{
    GEOMETRY_RUNTIME_ASSERT(scaling > 0.0f);
    return Transform2(Vector2::zero(), 0.0f, scaling);
}

Transform2::Transform2()
:   translation_(Vector2::zero()),
    rotation_(0.0f),
    scaling_(1.0f)
{
    // ...
}

Transform2::Transform2(
    const Vector2& translation,
    const float rotation,
    const float scaling)
:   translation_(translation),
    rotation_(Math::mod(rotation, 2.0f * Math::pi())),
    scaling_(scaling)
{
    GEOMETRY_RUNTIME_ASSERT(scaling_ > 0.0f);
}

void Transform2::transformBy(const Transform2& transform)
{
    GEOMETRY_RUNTIME_ASSERT(scaling_ > 0.0f);
    GEOMETRY_RUNTIME_ASSERT(transform.scaling_ > 0.0f);

    translation_ = transform.applyForward(translation_);
    rotation_ = Math::mod(rotation_ + transform.rotation_, 2.0f * Math::pi());
    scaling_ *= transform.scaling_;
}

void Transform2::setTranslation(const Vector2& translation)
{
    translation_ = translation;
}

void Transform2::translateBy(const Vector2& translation)
{
    translation_ += translation;
}

const Vector2 Transform2::translation() const
{
    return translation_;
}

void Transform2::setRotation(const float rotation)
{
    // wrap between [0, 2*pi)
    rotation_ = Math::mod(rotation, 2.0f * Math::pi());
}

void Transform2::rotateBy(const float rotation)
{
    // wrap between [0, 2*pi)
    rotation_ = Math::mod(rotation_ + rotation, 2.0f * Math::pi());
}

float Transform2::rotation() const
{
    return rotation_;
}

void Transform2::setScaling(const float scaling)
{
    GEOMETRY_RUNTIME_ASSERT(scaling > 0.0f);
    scaling_ = scaling;
}

void Transform2::scaleBy(const float scaling)
{
    GEOMETRY_RUNTIME_ASSERT(scaling > 0.0f);
    scaling_ *= scaling;
}

float Transform2::scaling() const
{
    return scaling_;
}

const Matrix4x4 Transform2::toMatrix4x4() const
{
    const Vector2 t = translation_;
    const Matrix2x2 r = Matrix2x2::rotation(rotation_);
    const float s = scaling_;

    return Matrix4x4(
        r.m00 * s,  r.m01 * s,  0.0f,  0.0f,
        r.m10 * s,  r.m11 * s,  0.0f,  0.0f,
             0.0f,       0.0f,  1.0f,  0.0f,
              t.x,        t.y,  0.0f,  1.0f
    );
}

const Vector2 Transform2::applyForward(const Vector2& q) const
{
    GEOMETRY_RUNTIME_ASSERT(scaling_ > 0.0f);

    const Matrix2x2 rotation = Matrix2x2::rotation(rotation_);
    return (scaling_ * q) * rotation + translation_;
}

const Vector2 Transform2::applyInverse(const Vector2& q) const
{
    GEOMETRY_RUNTIME_ASSERT(scaling_ > 0.0f);

    const Matrix2x2 rotation = Matrix2x2::rotation(rotation_);
    return timesTranspose(q - translation_, rotation) / scaling_;
}

void Transform2::swap(Transform2& other)
{
    translation_.swap(other.translation_);
    Math::swap(rotation_, other.rotation_);
    Math::swap(scaling_, other.scaling_);
}

const Transform2 conversion(const Transform2& src, const Transform2& dst)
{
    GEOMETRY_RUNTIME_ASSERT(src.scaling() > 0.0f);
    GEOMETRY_RUNTIME_ASSERT(dst.scaling() > 0.0f);

    return Transform2(
        dst.applyInverse(src.translation()),
        src.rotation() - dst.rotation(),
        src.scaling() / dst.scaling()
    );
}

const Transform2 product(const Transform2& a, const Transform2& b)
{
    GEOMETRY_RUNTIME_ASSERT(a.scaling() > 0.0f);
    GEOMETRY_RUNTIME_ASSERT(b.scaling() > 0.0f);

    return Transform2(
        b.applyForward(a.translation()),
        a.rotation() + b.rotation(),
        a.scaling() * b.scaling()
    );
}

const Transform2 invert(const Transform2& t)
{
    GEOMETRY_RUNTIME_ASSERT(t.scaling() > 0.0f);

    // inverse rotation and scaling
    const Matrix2x2 invRotation = Matrix2x2::rotation(-t.rotation());
    const float invScaling = 1.0f / t.scaling();

    return Transform2(
        (-invScaling * t.translation()) * invRotation,
        -t.rotation(),
        invScaling
    );
}
