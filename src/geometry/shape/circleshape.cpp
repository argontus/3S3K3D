/**
 * @file geometry/shape/circleshape.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/shape/circleshape.h>

#include <geometry/extents2.h>
#include <geometry/runtimeassert.h>

CircleShape::~CircleShape()
{
    // ...
}

CircleShape::CircleShape(const Vector2& center, float radius)
:   center_(center),
    radius_(radius)
{
    // TODO: use tolerances instead of absolute values?
    GEOMETRY_RUNTIME_ASSERT(radius > 0.0f);
}

CircleShape::CircleShape(const CircleShape& other)
:   center_(other.center_),
    radius_(other.radius_)
{
    // ...
}

const Vector2 CircleShape::center() const
{
    return center_;
}

float CircleShape::radius() const
{
    return radius_;
}

CircleShape* CircleShape::clone() const
{
    return new CircleShape(*this);
}

const Extents2 CircleShape::extents() const
{
    return Extents2(
        Vector2(center_.x - radius_, center_.y - radius_),
        Vector2(center_.x + radius_, center_.y + radius_)
    );
}
