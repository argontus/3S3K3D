/**
 * @file geometry/shape/primitiveshape.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_SHAPE_PRIMITIVESHAPE_H_INCLUDED
#define GEOMETRY_SHAPE_PRIMITIVESHAPE_H_INCLUDED

#include <geometry/shape/shape.h>

/**
 * Abstract base class for all primitive, i.e., convex shapes.
 */
class PrimitiveShape : public Shape
{
public:
    /**
     * Destructor.
     */
    virtual ~PrimitiveShape() {}

    /**
     * @name Shape Interface
     */
    //@{
    virtual PrimitiveShape* clone() const = 0;
    //@}

protected:
    /**
     * Default constructor.
     */
    PrimitiveShape() {}

private:
    // prevent copying
    PrimitiveShape(const PrimitiveShape&);
    PrimitiveShape& operator =(const PrimitiveShape&);
};

#endif // #ifndef GEOMETRY_SHAPE_PRIMITIVESHAPE_H_INCLUDED
