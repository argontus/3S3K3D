/**
 * @file graphics/parameters/mat2parameter.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_PARAMETERS_MAT2PARAMETER_H_INCLUDED
#define GRAPHICS_PARAMETERS_MAT2PARAMETER_H_INCLUDED

#include <geometry/matrix2x2.h>

#include <graphics/parameters/parameter.h>

class Mat2Parameter : public Parameter
{
public:
    virtual ~Mat2Parameter();

    Mat2Parameter(const std::string& name, const Matrix2x2& value);

    virtual Mat2Parameter* clone() const;
    virtual void bind(Device* device) const;
    virtual void setValue(const Matrix2x2& value);

private:
    Mat2Parameter(const Mat2Parameter& other);

    Matrix2x2 value_;

    // hide the assignment operator
    Mat2Parameter& operator =(const Mat2Parameter&);
};

#endif // #ifndef GRAPHICS_PARAMETERS_MAT2PARAMETER_H_INCLUDED
