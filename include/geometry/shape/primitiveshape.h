#ifndef GEOMETRY_SHAPE_PRIMITIVESHAPE_H_INCLUDED
#define GEOMETRY_SHAPE_PRIMITIVESHAPE_H_INCLUDED

#include <geometry/shape/shape.h>

class PrimitiveShape : public Shape
{
public:
    virtual ~PrimitiveShape() {}

    virtual PrimitiveShape* clone() const = 0;

protected:
    PrimitiveShape() {}

private:
    // prevent copying
    PrimitiveShape(const PrimitiveShape&);
    PrimitiveShape& operator =(const PrimitiveShape&);
};

#endif // #ifndef GEOMETRY_SHAPE_PRIMITIVESHAPE_H_INCLUDED
