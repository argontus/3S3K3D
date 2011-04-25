/**
 * @file graphics/parameters/floatparameter.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/parameters/floatparameter.h>

FloatParameter::~FloatParameter()
{
    // ...
}

FloatParameter::FloatParameter(const std::string& name, const float value)
:   Parameter(name),
    value_(value)
{
    // ...
}

FloatParameter* FloatParameter::clone() const
{
    return new FloatParameter(*this);
}

void FloatParameter::bind(Device* const device) const
{
    const GLint i = location(device);

    if (i != -1)
    {
        glUniform1f(i, value_);
    }
}

void FloatParameter::setValue(const float value)
{
    value_ = value;
}

FloatParameter::FloatParameter(const FloatParameter& other)
:   Parameter(other),
    value_(other.value_)
{
    // ...
}
