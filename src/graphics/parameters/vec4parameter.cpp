/**
 * @file graphics/parameters/vec4parameter.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/parameters/vec4parameter.h>

Vec4Parameter::~Vec4Parameter()
{
    // ...
}

Vec4Parameter::Vec4Parameter(const std::string& name, const Vector4& value)
:   Parameter(name),
    value_(value)
{
    // ...
}

Vec4Parameter* Vec4Parameter::clone() const
{
    return new Vec4Parameter(*this);
}

void Vec4Parameter::bind(Device* const device) const
{
    const GLint i = location(device);

    if (i != -1)
    {
        glUniform4fv(i, 1, value_.data());
    }
}

void Vec4Parameter::setValue(const Vector4& value)
{
    value_ = value;
}

Vec4Parameter::Vec4Parameter(const Vec4Parameter& other)
:   Parameter(other),
    value_(other.value_)
{
    // ...
}
