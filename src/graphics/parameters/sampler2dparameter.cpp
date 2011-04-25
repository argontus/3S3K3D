/**
 * @file graphics/parameters/sampler2dparameter.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/parameters/sampler2dparameter.h>

#include <graphics/device.h>
#include <graphics/runtimeassert.h>

Sampler2DParameter::~Sampler2DParameter()
{
    // ...
}

Sampler2DParameter::Sampler2DParameter(
    const std::string& name,
    const int textureUnit,
    Texture* const texture)
:   Parameter(name),
    textureUnit_(textureUnit),
    texture_(texture)
{
    GRAPHICS_RUNTIME_ASSERT(textureUnit >= 0);
}

Sampler2DParameter* Sampler2DParameter::clone() const
{
    return new Sampler2DParameter(*this);
}

void Sampler2DParameter::bind(Device* const device) const
{
    GRAPHICS_RUNTIME_ASSERT(device != 0);
    GRAPHICS_RUNTIME_ASSERT(textureUnit_ >= 0);
    GRAPHICS_RUNTIME_ASSERT(textureUnit_ < device->numTextureUnits());
    GRAPHICS_RUNTIME_ASSERT(texture_ != 0);

    // Pass::bind(Device*) is responsible for disabling all texture units
    // before binding any parameters
    GRAPHICS_RUNTIME_ASSERT(device->texture(textureUnit_) == 0);

    const GLint i = location(device);

    if (i != -1)
    {
        // bind the specified texture unit to the sampler2D uniform variable
        glUniform1i(i, textureUnit_);

        // bind the texture to the specified texture unit
        device->setTexture(textureUnit_, texture_);
    }
}

void Sampler2DParameter::setValue(Texture* const texture)
{
    texture_ = texture;
}

Sampler2DParameter::Sampler2DParameter(const Sampler2DParameter& other)
:   Parameter(other),
    textureUnit_(other.textureUnit_),
    texture_(other.texture_)
{
    // ...
}
