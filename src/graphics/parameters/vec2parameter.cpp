/**
 * @file graphics/parameters/vec2parameter.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/parameters/vec2parameter.h>

Vec2Parameter::~Vec2Parameter()
{
    // ...
}

Vec2Parameter::Vec2Parameter(const std::string& name, const Vector2& value)
:   Parameter(name),
    value_(value)
{
    // ...
}

Vec2Parameter* Vec2Parameter::clone() const
{
    return new Vec2Parameter(*this);
}

void Vec2Parameter::bind(Device* const device) const
{
    const GLint i = location(device);

    if (i != -1)
    {
        glUniform2fv(i, 1, value_.data());
    }
}

void Vec2Parameter::setValue(const Vector2& value)
{
    value_ = value;
}

Vec2Parameter::Vec2Parameter(const Vec2Parameter& other)
:   Parameter(other),
    value_(other.value_)
{
    // ...
}
