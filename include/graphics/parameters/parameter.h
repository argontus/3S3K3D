/**
 * @file graphics/parameters/parameter.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_PARAMETERS_PARAMETER_H_INCLUDED
#define GRAPHICS_PARAMETERS_PARAMETER_H_INCLUDED

#include <string>

#include <graphics/opengl.h>

class Matrix2x2;
class Matrix3x3;
class Matrix4x4;
class Vector2;
class Vector3;
class Vector4;

class Device;
class Texture;

class Parameter
{
public:
    virtual ~Parameter();

    const std::string name() const;

    virtual Parameter* clone() const = 0;
    virtual void bind(Device* device) const = 0;

    virtual void setValue(float value);
    virtual void setValue(const Vector2& value);
    virtual void setValue(const Vector3& value);
    virtual void setValue(const Vector4& value);
    virtual void setValue(const Matrix2x2& value);
    virtual void setValue(const Matrix3x3& value);
    virtual void setValue(const Matrix4x4& value);
    virtual void setValue(Texture* value);

protected:
    explicit Parameter(const std::string& name);
    Parameter(const Parameter& other);

    GLint location(Device* device) const;

private:
    std::string name_;

    // hide the assignment operator
    Parameter& operator =(const Parameter&);
};

#endif // #ifndef GRAPHICS_PARAMETERS_PARAMETER_H_INCLUDED
