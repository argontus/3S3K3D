/**
 * @file geometry/circle.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/circle.h>

#include <geometry/math.h>

Circle::Circle()
{
    // ...
}

Circle::Circle(const Vector2& center, const float radius)
:   center(center),
    radius(radius)
{
    // ...
}

void Circle::swap(Circle& other)
{
    center.swap(other.center);
    Math::swap(radius, other.radius);
}
