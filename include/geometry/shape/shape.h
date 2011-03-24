/**
 * @file geometry/shape/shape.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_SHAPE_SHAPE_H_INCLUDED
#define GEOMETRY_SHAPE_SHAPE_H_INCLUDED

class Extents2;

/**
 * Abstract base class for all shapes.
 */
class Shape
{
public:
    /**
     * Destructor.
     */
    virtual ~Shape() {}

    /**
     * Virtual copy constructor.
     *
     * @return Dynamically allocated copy of this object.
     *
     * @warning The returned object is allocated via a C++ <code>new</code>
     * expression. The caller is responsible for deleting it.
     */
    virtual Shape* clone() const = 0;

    /**
     * Gets the extents of this shape.
     *
     * @return Extents of this shape.
     */
    virtual const Extents2 extents() const = 0;

protected:
    /**
     * Default constructor.
     */
    Shape() {}

private:
    // prevent copying
    Shape(const Shape&);
    Shape& operator =(const Shape&);
};

#endif // #ifndef GEOMETRY_SHAPE_SHAPE_H_INCLUDED
