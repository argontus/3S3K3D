/**
 * @file graphics/parameters/vec3parameter.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_PARAMETERS_VEC3PARAMETER_H_INCLUDED
#define GRAPHICS_PARAMETERS_VEC3PARAMETER_H_INCLUDED

#include <geometry/vector3.h>

#include <graphics/parameters/parameter.h>

class Vec3Parameter : public Parameter
{
public:
    virtual ~Vec3Parameter();

    Vec3Parameter(const std::string& name, const Vector3& value);

    virtual Vec3Parameter* clone() const;
    virtual void bind(Device* device) const;
    virtual void setValue(const Vector3& value);

private:
    Vec3Parameter(const Vec3Parameter& other);

    Vector3 value_;

    // hide the assignment operator
    Vec3Parameter& operator =(const Vec3Parameter&);
};

#endif // #ifndef GRAPHICS_PARAMETERS_VEC3PARAMETER_H_INCLUDED
