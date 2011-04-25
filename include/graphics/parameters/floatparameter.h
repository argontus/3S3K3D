/**
 * @file graphics/parameters/floatparameter.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_PARAMETERS_FLOATPARAMETER_H_INCLUDED
#define GRAPHICS_PARAMETERS_FLOATPARAMETER_H_INCLUDED

#include <graphics/parameters/parameter.h>

class FloatParameter : public Parameter
{
public:
    virtual ~FloatParameter();

    FloatParameter(const std::string& name, float value);

    virtual FloatParameter* clone() const;
    virtual void bind(Device* device) const;
    virtual void setValue(float value);

private:
    FloatParameter(const FloatParameter& other);

    float value_;

    // hide the assignment operator
    FloatParameter& operator =(const FloatParameter&);
};

#endif // #ifndef GRAPHICS_PARAMETERS_FLOATPARAMETER_H_INCLUDED
