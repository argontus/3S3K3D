/**
 * @file graphics/material.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/material.h>

#include <graphics/program.h>
#include <graphics/runtimeassert.h>
#include <graphics/variable.h>

Material::~Material()
{
    for (size_t i = 0; i < variables_.size(); ++i)
    {
        delete variables_[i];
    }
}

Material::Material()
:   program_(0),
    variables_(),
    numTextureUnits_(0)
{
    // ...
}

void Material::setProgram(Program* const program)
{
    program_ = program;
}

Program* Material::program() const
{
    return program_;
}

void Material::addVariable(Variable* const variable)
{
    GRAPHICS_RUNTIME_ASSERT(variable != 0);
    variables_.push_back(variable);
}

void Material::bind() const
{
    GRAPHICS_RUNTIME_ASSERT(program_ != 0);

    glUseProgram(program_->id());

    for (size_t i = 0; i < variables_.size(); ++i)
    {
        variables_[i]->bind();
    }
}

void Material::unbind() const
{
    GRAPHICS_RUNTIME_ASSERT(program_ != 0);

    for (size_t i = 0; i < variables_.size(); ++i)
    {
        variables_[i]->unbind();
    }

    // disable shaders
    glUseProgram(0);
}

bool Material::link()
{
    GRAPHICS_RUNTIME_ASSERT(program_ != 0);

    // reset the counter, linking sampler variables will increment this
    numTextureUnits_ = 0;

    for (size_t i = 0; i < variables_.size(); ++i)
    {
        if (variables_[i]->link(this) == false)
        {
            // failed
            return false;
        }
    }

    return true;
}

int Material::generateTextureUnitIndex()
{
    return numTextureUnits_++;
}
