/**
 * @file graphics/variables/vec3variable.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/variables/vec3variable.h>

#include <graphics/color3.h>

Vec3Variable::~Vec3Variable()
{
    // ...
}

Vec3Variable::Vec3Variable(const std::string& name, const Color3& value)
:   Variable(name),
    value_(value.r, value.g, value.b)
{
    // ...
}

Vec3Variable::Vec3Variable(const std::string& name, const Vector3& value)
:   Variable(name),
    value_(value)
{
    // ...
}

void Vec3Variable::bind() const
{
    glUniform3fv(location(), 1, value_.data());
}
