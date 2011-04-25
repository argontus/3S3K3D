/**
 * @file graphics/parameters/mat4parameter.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_PARAMETERS_MAT4PARAMETER_H_INCLUDED
#define GRAPHICS_PARAMETERS_MAT4PARAMETER_H_INCLUDED

#include <geometry/matrix4x4.h>

#include <graphics/parameters/parameter.h>

class Mat4Parameter : public Parameter
{
public:
    virtual ~Mat4Parameter();

    Mat4Parameter(const std::string& name, const Matrix4x4& value);

    virtual Mat4Parameter* clone() const;
    virtual void bind(Device* device) const;
    virtual void setValue(const Matrix4x4& value);

private:
    Mat4Parameter(const Mat4Parameter& other);

    Matrix4x4 value_;

    // hide the assignment operator
    Mat4Parameter& operator =(const Mat4Parameter&);
};

#endif // #ifndef GRAPHICS_PARAMETERS_MAT4PARAMETER_H_INCLUDED
