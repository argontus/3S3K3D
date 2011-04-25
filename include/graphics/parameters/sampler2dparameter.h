/**
 * @file graphics/parameters/sampler2dparameter.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_PARAMETERS_SAMPLER2DPARAMETER_H_INCLUDED
#define GRAPHICS_PARAMETERS_SAMPLER2DPARAMETER_H_INCLUDED

#include <graphics/parameters/parameter.h>

class Sampler2DParameter : public Parameter
{
public:
    virtual ~Sampler2DParameter();

    Sampler2DParameter(
        const std::string& name,
        int textureUnit,
        Texture* texture);

    virtual Sampler2DParameter* clone() const;
    virtual void bind(Device* device) const;
    virtual void setValue(Texture* texture);

private:
    Sampler2DParameter(const Sampler2DParameter& other);

    int textureUnit_;
    Texture* texture_;

    // hide the assignment operator
    Sampler2DParameter& operator =(const Sampler2DParameter&);
};

#endif // #ifndef GRAPHICS_PARAMETERS_SAMPLER2DPARAMETER_H_INCLUDED
