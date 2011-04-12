/**
 * @file graphics/floatvariable.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/floatvariable.h>

FloatVariable::~FloatVariable()
{
    // ...
}

FloatVariable::FloatVariable(const std::string& name, const float value)
:   Variable(name),
    value_(value)
{
    // ...
}

void FloatVariable::bind() const
{
    glUniform1f(location(), value_);
}
