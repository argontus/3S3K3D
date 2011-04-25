/**
 * @file graphics/parameters/mat4parameter.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/parameters/mat4parameter.h>

Mat4Parameter::~Mat4Parameter()
{
    // ...
}

Mat4Parameter::Mat4Parameter(const std::string& name, const Matrix4x4& value)
:   Parameter(name),
    value_(value)
{
    // ...
}

Mat4Parameter* Mat4Parameter::clone() const
{
    return new Mat4Parameter(*this);
}

void Mat4Parameter::bind(Device* const device) const
{
    const GLint i = location(device);

    if (i != -1)
    {
        glUniformMatrix4fv(i, 1, false, value_.data());
    }
}

void Mat4Parameter::setValue(const Matrix4x4& value)
{
    value_ = value;
}

Mat4Parameter::Mat4Parameter(const Mat4Parameter& other)
:   Parameter(other),
    value_(other.value_)
{
    // ...
}
