/**
 * @file geometry/shape/compositeshape.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_SHAPE_COMPOSITESHAPE_H_INCLUDED
#define GEOMETRY_SHAPE_COMPOSITESHAPE_H_INCLUDED

#include <vector>

#include <geometry/shape/shape.h>

class PrimitiveShape;

/**
 * Describes a shape that is composed of primitive shapes.
 */
class CompositeShape : public Shape
{
public:
    /**
     * Destructor.
     */
    virtual ~CompositeShape();

    /**
     * Default constructor.
     */
    CompositeShape();

    /**
     * Copy constructor.
     *
     * @param other The object to copy.
     */
    CompositeShape(const CompositeShape& other);

    /**
     * Adds a copy of <code>p</code> to this composite shape.
     *
     * @param p The primitive shape to add.
     */
    void addPrimitive(const PrimitiveShape& p);

    /**
     * Gets the number of primitive shapes.
     *
     * @return Number of primitive shapes.
     */
    int numPrimitives() const;

    /**
     * Gets a reference to the specified primitive shape.
     *
     * @param index Index specifying the primitive shape, between [0,
     * <code>numPrimitives()</code>).
     *
     * @return Reference to the specified primitive shape.
     */
    const PrimitiveShape& primitive(int index) const;

    /**
     * Removes all primitive shapes from this composite shape.
     */
    void clear();

    /**
     * @name Shape Interface
     */
    //@{
    virtual CompositeShape* clone() const;
    virtual const Extents2 extents() const;
    //@}

private:
    std::vector<PrimitiveShape*> primitives_;   ///< Primitive shapes.

    // hide the assignment operator
    CompositeShape& operator =(const CompositeShape&);
};

#endif // #ifndef GEOMETRY_SHAPE_COMPOSITESHAPE_H_INCLUDED
