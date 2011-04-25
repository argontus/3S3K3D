/**
 * @file graphics/parameters/vec3parameter.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/parameters/vec3parameter.h>

Vec3Parameter::~Vec3Parameter()
{
    // ...
}

Vec3Parameter::Vec3Parameter(const std::string& name, const Vector3& value)
:   Parameter(name),
    value_(value)
{
    // ...
}

Vec3Parameter* Vec3Parameter::clone() const
{
    return new Vec3Parameter(*this);
}

void Vec3Parameter::bind(Device* const device) const
{
    const GLint i = location(device);

    if (i != -1)
    {
        glUniform3fv(i, 1, value_.data());
    }
}

void Vec3Parameter::setValue(const Vector3& value)
{
    value_ = value;
}

Vec3Parameter::Vec3Parameter(const Vec3Parameter& other)
:   Parameter(other),
    value_(other.value_)
{
    // ...
}
