/**
 * @file graphics/parameters/mat3parameter.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/parameters/mat3parameter.h>

Mat3Parameter::~Mat3Parameter()
{
    // ...
}

Mat3Parameter::Mat3Parameter(const std::string& name, const Matrix3x3& value)
:   Parameter(name),
    value_(value)
{
    // ...
}

Mat3Parameter* Mat3Parameter::clone() const
{
    return new Mat3Parameter(*this);
}

void Mat3Parameter::bind(Device* const device) const
{
    const GLint i = location(device);

    if (i != -1)
    {
        glUniformMatrix3fv(i, 1, false, value_.data());
    }
}

void Mat3Parameter::setValue(const Matrix3x3& value)
{
    value_ = value;
}

Mat3Parameter::Mat3Parameter(const Mat3Parameter& other)
:   Parameter(other),
    value_(other.value_)
{
    // ...
}
