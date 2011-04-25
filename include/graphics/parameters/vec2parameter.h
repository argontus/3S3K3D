/**
 * @file graphics/parameters/vec2parameter.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_PARAMETERS_VEC2PARAMETER_H_INCLUDED
#define GRAPHICS_PARAMETERS_VEC2PARAMETER_H_INCLUDED

#include <geometry/vector2.h>

#include <graphics/parameters/parameter.h>

class Vec2Parameter : public Parameter
{
public:
    virtual ~Vec2Parameter();

    Vec2Parameter(const std::string& name, const Vector2& value);

    virtual Vec2Parameter* clone() const;
    virtual void bind(Device* device) const;
    virtual void setValue(const Vector2& value);

private:
    Vec2Parameter(const Vec2Parameter& other);

    Vector2 value_;

    // hide the assignment operator
    Vec2Parameter& operator =(const Vec2Parameter&);
};

#endif // #ifndef GRAPHICS_PARAMETERS_VEC2PARAMETER_H_INCLUDED
