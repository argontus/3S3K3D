/**
 * @file geometry/transform2.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/transform2.h>

#include <algorithm>

#include <geometry/math.h>
#include <geometry/matrix2x2.h>

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
    rotation_(Math::wrapTo2Pi(rotation)),
    scaling_(scaling)
{
    GEOMETRY_RUNTIME_ASSERT(scaling_ > 0.0f);
}

void Transform2::transformBy(const Transform2& transform)
{
    GEOMETRY_RUNTIME_ASSERT(scaling_ > 0.0f);
    GEOMETRY_RUNTIME_ASSERT(transform.scaling_ > 0.0f);

    translation_ = transform.applyForward(translation_);
    rotation_ = Math::wrapTo2Pi(rotation_ + transform.rotation_);
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
    rotation_ = Math::wrapTo2Pi(rotation);
}

void Transform2::rotateBy(const float rotation)
{
    rotation_ = Math::wrapTo2Pi(rotation_ + rotation);
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

const Vector2 Transform2::applyForward(const Vector2& q) const
{
    GEOMETRY_RUNTIME_ASSERT(scaling_ > 0.0f);

    const Matrix2x2 rotation = Matrix2x2::rotation(rotation_);
    return product(scaling_ * q, rotation) + translation_;
}

const Vector2 Transform2::applyInverse(const Vector2& q) const
{
    GEOMETRY_RUNTIME_ASSERT(scaling_ > 0.0f);

    const Matrix2x2 rotation = Matrix2x2::rotation(rotation_);
    return productT(q - translation_, rotation) / scaling_;
}

void Transform2::swap(Transform2& other)
{
    translation_.swap(other.translation_);
    std::swap(rotation_, other.rotation_);
    std::swap(scaling_, other.scaling_);
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

const Transform2 invert(const Transform2& t)
{
    GEOMETRY_RUNTIME_ASSERT(t.scaling() > 0.0f);

    return Transform2(
        -t.translation(),
        -t.rotation(),
        1.0f / t.scaling()
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
