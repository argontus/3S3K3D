/**
 * @file graphics/pass.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_PASS_H_INCLUDED
#define GRAPHICS_PASS_H_INCLUDED

#include <string>
#include <vector>

class BlendState;
class DepthState;
class Device;
class Parameter;
class Program;
class RasterizerState;
class StencilState;

// TODO: has a lot in common with Effect and Technique classes
class Pass
{
public:
    ~Pass();

    Pass(const std::string& name, int numParameters);
    Pass(const Pass& other);

    const std::string name() const;

    Pass* clone() const;
    void bind(Device* device) const;

    void setBlendState(const BlendState* blendState);
    const BlendState* blendState() const;

    void setDepthState(const DepthState* depthState);
    const DepthState* depthState() const;

    void setRasterizerState(const RasterizerState* rasterizerState);
    const RasterizerState* rasterizerState() const;

    void setStencilState(const StencilState* stencilState);
    const StencilState* stencilState() const;

    void setProgram(Program* program);
    Program* program() const;

    void setParameter(int index, Parameter* parameter);

    Parameter* parameter(int index);
    const Parameter* parameter(int index) const;

    Parameter* parameter(const std::string& name);
    const Parameter* parameter(const std::string& name) const;

    int numParameters() const;

private:
    void deleteParameters();

    std::string name_;
    const BlendState* blendState_;
    const DepthState* depthState_;
    const RasterizerState* rasterizerState_;
    const StencilState* stencilState_;
    Program* program_;
    std::vector<Parameter*> parameters_;

    // hide the assignment operator
    Pass& operator =(const Pass&);
};

#endif // #ifndef GRAPHICS_PASS_H_INCLUDED
