/**
 * @file graphics/parameters/mat3parameter.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_PARAMETERS_MAT3PARAMETER_H_INCLUDED
#define GRAPHICS_PARAMETERS_MAT3PARAMETER_H_INCLUDED

#include <geometry/matrix3x3.h>

#include <graphics/parameters/parameter.h>

class Mat3Parameter : public Parameter
{
public:
    virtual ~Mat3Parameter();

    Mat3Parameter(const std::string& name, const Matrix3x3& value);

    virtual Mat3Parameter* clone() const;
    virtual void bind(Device* device) const;
    virtual void setValue(const Matrix3x3& value);

private:
    Mat3Parameter(const Mat3Parameter& other);

    Matrix3x3 value_;

    // hide the assignment operator
    Mat3Parameter& operator =(const Mat3Parameter&);
};

#endif // #ifndef GRAPHICS_PARAMETERS_MAT3PARAMETER_H_INCLUDED
