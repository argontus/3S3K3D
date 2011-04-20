/**
 * @file graphics/variables/variable.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/variables/variable.h>

#include <graphics/material.h>
#include <graphics/program.h>
#include <graphics/runtimeassert.h>

Variable::~Variable()
{
    // ...
}

const std::string Variable::name() const
{
    return name_;
}

GLint Variable::location() const
{
    return location_;
}

void Variable::unbind() const
{
    // ...
}

bool Variable::link(Material* const material)
{
    GRAPHICS_RUNTIME_ASSERT(material != 0);
    GRAPHICS_RUNTIME_ASSERT(material->program() != 0);

    // glGetUniformLocation returns -1 on error
    const GLuint programId = material->program()->id();
    location_ = glGetUniformLocation(programId, name_.c_str());

    return location_ != -1;
}

Variable::Variable(const std::string& name)
:   name_(name),
    location_(-1)
{
    // ...
}
