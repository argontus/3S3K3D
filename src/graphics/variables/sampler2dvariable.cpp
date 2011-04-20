/**
 * @file graphics/variables/sampler2dvariable.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/variables/sampler2dvariable.h>

#include <graphics/material.h>
#include <graphics/runtimeassert.h>
#include <graphics/texture.h>

Sampler2DVariable::~Sampler2DVariable()
{
    // ...
}

Sampler2DVariable::Sampler2DVariable(
    const std::string& name,
    Texture* const texture)
:   Variable(name),
    texture_(texture),
    textureUnit_(-1)
{
    // ...
}

void Sampler2DVariable::bind() const
{
    GRAPHICS_RUNTIME_ASSERT(texture_ != 0);
    GRAPHICS_RUNTIME_ASSERT(textureUnit_ >= 0);

    glUniform1i(location(), textureUnit_);
    glActiveTexture(GL_TEXTURE0 + textureUnit_);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_->getTextureHandle());
}

void Sampler2DVariable::unbind() const
{
    GRAPHICS_RUNTIME_ASSERT(texture_ != 0);
    GRAPHICS_RUNTIME_ASSERT(textureUnit_ >= 0);

    glActiveTexture(GL_TEXTURE0 + textureUnit_);
    glDisable(GL_TEXTURE_2D);
}

bool Sampler2DVariable::link(Material* const material)
{
    GRAPHICS_RUNTIME_ASSERT(material != 0);

    // call the base class implementation
    if (Variable::link(material) == false)
    {
        // failed
        return false;
    }

    // ask material to assign a texture unit for this sampler variable
    textureUnit_ = material->generateTextureUnitIndex();
    GRAPHICS_RUNTIME_ASSERT(textureUnit_ >= 0);

    return true;
}
