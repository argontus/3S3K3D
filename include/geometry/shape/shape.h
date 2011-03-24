#ifndef GEOMETRY_SHAPE_SHAPE_H_INCLUDED
#define GEOMETRY_SHAPE_SHAPE_H_INCLUDED

class Extents2;

class Shape
{
public:
    virtual ~Shape() {}

    virtual Shape* clone() const = 0;
    virtual const Extents2 extents() const = 0;

protected:
    Shape() {}

private:
    // prevent copying
    Shape(const Shape&);
    Shape& operator =(const Shape&);
};

#endif // #ifndef GEOMETRY_SHAPE_SHAPE_H_INCLUDED
