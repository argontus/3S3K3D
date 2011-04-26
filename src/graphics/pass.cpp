/**
 * @file graphics/pass.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/pass.h>

#include <graphics/device.h>
#include <graphics/runtimeassert.h>
#include <graphics/parameters/parameter.h>

Pass::~Pass()
{
    deleteParameters();
}

Pass::Pass(const std::string& name, const int numParameters)
:   name_(name),
    blendState_(0),
    depthState_(0),
    rasterizerState_(0),
    stencilState_(0),
    program_(0),
    parameters_(static_cast<size_t>(numParameters), 0) // fill with null ptrs
{
    // ...
}

Pass::Pass(const Pass& other)
:   name_(other.name_),
    blendState_(other.blendState_),
    depthState_(other.depthState_),
    rasterizerState_(other.rasterizerState_),
    stencilState_(other.stencilState_),
    program_(other.program_),
    parameters_(other.parameters_.size(), 0) // fill with null ptrs
{
    try
    {
        for (size_t i = 0; i < other.parameters_.size(); ++i)
        {
            parameters_[i] = other.parameters_[i]->clone();
        }
    }
    catch (...)
    {
        // deallocate the parameters that had been cloned before the exception
        // was thrown and rethrow
        deleteParameters();
        throw;
    }
}

const std::string Pass::name() const
{
    return name_;
}

Pass* Pass::clone() const
{
    return new Pass(*this);
}

void Pass::bind(Device* const device) const
{
    GRAPHICS_RUNTIME_ASSERT(device != 0);
    GRAPHICS_RUNTIME_ASSERT(blendState_ != 0);
    GRAPHICS_RUNTIME_ASSERT(depthState_ != 0);
    GRAPHICS_RUNTIME_ASSERT(rasterizerState_ != 0);
    GRAPHICS_RUNTIME_ASSERT(stencilState_ != 0);
    GRAPHICS_RUNTIME_ASSERT(program_ != 0);

    // disable all texture units
    for (int i = 0; i < device->numTextureUnits(); ++i)
    {
        device->setTexture(i, 0);
    }

    device->setBlendState(blendState_);
    device->setDepthState(depthState_);
    device->setRasterizerState(rasterizerState_);
    device->setStencilState(stencilState_);
    device->setProgram(program_);

    for (size_t i = 0; i < parameters_.size(); ++i)
    {
        parameters_[i]->bind(device);
    }
}

void Pass::setBlendState(const BlendState* const blendState)
{
    blendState_ = blendState;
}

const BlendState* Pass::blendState() const
{
    return blendState_;
}

void Pass::setDepthState(const DepthState* const depthState)
{
    depthState_ = depthState;
}

const DepthState* Pass::depthState() const
{
    return depthState_;
}

void Pass::setRasterizerState(const RasterizerState* const rasterizerState)
{
    rasterizerState_ = rasterizerState;
}

const RasterizerState* Pass::rasterizerState() const
{
    return rasterizerState_;
}

void Pass::setStencilState(const StencilState* const stencilState)
{
    stencilState_ = stencilState;
}

const StencilState* Pass::stencilState() const
{
    return stencilState_;
}

void Pass::setProgram(Program* const program)
{
    program_ = program;
}

Program* Pass::program() const
{
    return program_;
}

void Pass::setParameter(const int index, Parameter* const parameter)
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < numParameters());
    GRAPHICS_RUNTIME_ASSERT(parameter != 0);
    GRAPHICS_RUNTIME_ASSERT(parameters_[index] == 0);
    parameters_[index] = parameter;
}

Parameter* Pass::parameter(const int index)
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < numParameters());
    return parameters_[index];
}

const Parameter* Pass::parameter(const int index) const
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < numParameters());
    return parameters_[index];
}

Parameter* Pass::parameter(const std::string& name)
{
    // call the const version
    return const_cast<Parameter*>(const_cast<const Pass*>(this)->parameter(name));
}

const Parameter* Pass::parameter(const std::string& name) const
{
    for (size_t i = 0; i < parameters_.size(); ++i)
    {
        if (parameters_[i]->name() == name)
        {
            return parameters_[i];
        }
    }

    GRAPHICS_RUNTIME_ASSERT(false);
    return 0;
}

int Pass::numParameters() const
{
    return parameters_.size();
}

void Pass::deleteParameters()
{
    for (size_t i = 0; i < parameters_.size(); ++i)
    {
        delete parameters_[i];
    }
}
