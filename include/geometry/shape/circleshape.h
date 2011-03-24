/**
 * @file geometry/shape/circleshape.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_SHAPE_CIRCLESHAPE_H_INCLUDED
#define GEOMETRY_SHAPE_CIRCLESHAPE_H_INCLUDED

#include <geometry/vector2.h>

#include <geometry/shape/primitiveshape.h>

/**
 * Describes a circle.
 */
class CircleShape : public PrimitiveShape
{
public:
    /**
     * Destructor.
     */
    virtual ~CircleShape();

    /**
     * Constructor.
     *
     * @param center Center point.
     * @param radius Radius, must be greater than zero.
     */
    CircleShape(const Vector2& center, float radius);

    /**
     * Copy constructor.
     *
     * @param other The object to copy.
     */
    CircleShape(const CircleShape& other);

    /**
     * Gets the center point.
     *
     * @return Center point.
     */
    const Vector2 center() const;

    /**
     * Gets the radius.
     *
     * @return Radius.
     */
    float radius() const;

    /**
     * @name Shape Interface
     */
    //@{
    virtual CircleShape* clone() const;
    virtual const Extents2 extents() const;
    //@}

private:
    Vector2 center_;    ///< Center point.
    float radius_;      ///< Radius.

    // hide the assignment operator
    CircleShape& operator =(const CircleShape&);
};

#endif // #ifndef GEOMETRY_SHAPE_CIRCLESHAPE_H_INCLUDED
