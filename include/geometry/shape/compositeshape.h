#ifndef GEOMETRY_SHAPE_COMPOSITESHAPE_H_INCLUDED
#define GEOMETRY_SHAPE_COMPOSITESHAPE_H_INCLUDED

#include <vector>

#include <geometry/shape/shape.h>

class PrimitiveShape;

class CompositeShape : public Shape
{
public:
    virtual ~CompositeShape();

    CompositeShape();
    CompositeShape(const CompositeShape& other);

    void addPrimitive(const PrimitiveShape& p);

    int numPrimitives() const;

    const PrimitiveShape& primitive(int index) const;

    virtual CompositeShape* clone() const;
    virtual const Extents2 extents() const;

private:
    std::vector<PrimitiveShape*> shapes_;

    // hide the assignment operator
    CompositeShape& operator =(const CompositeShape&);
};

#endif // #ifndef GEOMETRY_SHAPE_COMPOSITESHAPE_H_INCLUDED
