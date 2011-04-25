/**
 * @file graphics/parameters/mat2parameter.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/parameters/mat2parameter.h>

Mat2Parameter::~Mat2Parameter()
{
    // ...
}

Mat2Parameter::Mat2Parameter(const std::string& name, const Matrix2x2& value)
:   Parameter(name),
    value_(value)
{
    // ...
}

Mat2Parameter* Mat2Parameter::clone() const
{
    return new Mat2Parameter(*this);
}

void Mat2Parameter::bind(Device* const device) const
{
    const GLint i = location(device);

    if (i != -1)
    {
        glUniformMatrix2fv(i, 1, false, value_.data());
    }
}

void Mat2Parameter::setValue(const Matrix2x2& value)
{
    value_ = value;
}

Mat2Parameter::Mat2Parameter(const Mat2Parameter& other)
:   Parameter(other),
    value_(other.value_)
{
    // ...
}
