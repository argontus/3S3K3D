/**
 * @file graphics/parameters/parameter.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/parameters/parameter.h>

#include <graphics/device.h>
#include <graphics/program.h>
#include <graphics/runtimeassert.h>

Parameter::~Parameter()
{
    // ...
}

const std::string Parameter::name() const
{
    return name_;
}

void Parameter::setValue(const float)
{
    GRAPHICS_RUNTIME_ASSERT(false);
}

void Parameter::setValue(const Vector2&)
{
    GRAPHICS_RUNTIME_ASSERT(false);
}

void Parameter::setValue(const Vector3&)
{
    GRAPHICS_RUNTIME_ASSERT(false);
}

void Parameter::setValue(const Vector4&)
{
    GRAPHICS_RUNTIME_ASSERT(false);
}

void Parameter::setValue(const Matrix2x2&)
{
    GRAPHICS_RUNTIME_ASSERT(false);
}

void Parameter::setValue(const Matrix3x3&)
{
    GRAPHICS_RUNTIME_ASSERT(false);
}

void Parameter::setValue(const Matrix4x4&)
{
    GRAPHICS_RUNTIME_ASSERT(false);
}

void Parameter::setValue(Texture* const)
{
    GRAPHICS_RUNTIME_ASSERT(false);
}

Parameter::Parameter(const std::string& name)
:   name_(name)
{
    // ...
}

Parameter::Parameter(const Parameter& other)
:   name_(other.name_)
{
    // ...
}

GLint Parameter::location(Device* const device) const
{
    GRAPHICS_RUNTIME_ASSERT(device != 0);
    GRAPHICS_RUNTIME_ASSERT(device->program() != 0);

    // glGetUniformLocation returns -1 on error
    const GLint location = glGetUniformLocation(
        device->program()->id(),
        name_.c_str()
    );

    return location;
}
