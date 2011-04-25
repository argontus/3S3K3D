/**
 * @file graphics/parameters/vec4parameter.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_PARAMETERS_VEC4PARAMETER_H_INCLUDED
#define GRAPHICS_PARAMETERS_VEC4PARAMETER_H_INCLUDED

#include <geometry/vector4.h>

#include <graphics/parameters/parameter.h>

class Vec4Parameter : public Parameter
{
public:
    virtual ~Vec4Parameter();

    Vec4Parameter(const std::string& name, const Vector4& value);

    virtual Vec4Parameter* clone() const;
    virtual void bind(Device* device) const;
    virtual void setValue(const Vector4& value);

private:
    Vec4Parameter(const Vec4Parameter& other);

    Vector4 value_;

    // hide the assignment operator
    Vec4Parameter& operator =(const Vec4Parameter&);
};

#endif // #ifndef GRAPHICS_PARAMETERS_VEC4PARAMETER_H_INCLUDED
