/**
 * @file geometry/shape/polygonshape.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_SHAPE_POLYGONSHAPE_H_INCLUDED
#define GEOMETRY_SHAPE_POLYGONSHAPE_H_INCLUDED

#include <vector>

#include <geometry/runtimeassert.h>
#include <geometry/vector2.h>

#include <geometry/shape/primitiveshape.h>

/**
 * Describes a convex polygon.
 */
class PolygonShape : public PrimitiveShape
{
public:
    /**
     * Destructor.
     */
    virtual ~PolygonShape();

    /**
     * Constructor, constructs a polygon from given vertices. The range
     * [<code>first</code>, <code>last</code>) must contain at least 3
     * vertices. The vertices are assumed to be in CCW order and they are
     * assumed to describe a non-self-intersecting convex polygon.
     *
     * @param first Iterator pointing to the first vertex.
     * @param last Iterator pointing one beyond the last vertex.
     */
    template <class In>
    PolygonShape(In first, In last);

    /**
     * Copy constructor.
     *
     * @param other The object to copy.
     */
    PolygonShape(const PolygonShape& other);

    /**
     * Gets the number of vertices.
     *
     * @return Number of vertices.
     */
    int numVertices() const;

    /**
     * Gets a specified vertex.
     *
     * @param index Index of the vertex to return, between [0,
     * <code>numVertices()</code>).
     *
     * @return The specified vertex.
     */
    const Vector2 vertex(int index) const;

    /**
     * Gets a specified edge normal.
     *
     * @param index Index of the edge normal to return, between [0,
     * <code>numVertices()</code>).
     *
     * @return The specified edge normal.
     */
    const Vector2 normal(int index) const;

    /**
     * @name Shape Interface
     */
    //@{
    virtual PolygonShape* clone() const;
    virtual const Extents2 extents() const;
    //@}

private:
    std::vector<Vector2> vertices_; ///< Vertices.
    std::vector<Vector2> normals_;  ///< Edge normals.

    // hide the assignment operator
    PolygonShape& operator =(const PolygonShape&);
};

template <class In>
PolygonShape::PolygonShape(const In first, const In last)
{
    // initializer list is not used to avoid a hard-to-find bug in case the
    // declaration order of PolygonShape::vertices_ and PolygonShape::normals_
    // changes

    // assign range [first, last)
    vertices_.assign(first, last);

    // make sure the range contained at least 3 vertices
    GEOMETRY_RUNTIME_ASSERT(vertices_.size() >= 3);

    normals_.resize(vertices_.size());

    for (size_t i = 0; i < vertices_.size(); ++i)
    {
        const size_t j = (i + 1) % vertices_.size();
        normals_[i] = normalize(perp(vertices_[i] - vertices_[j]));
    }
}

#endif // #ifndef GEOMETRY_SHAPE_POLYGONSHAPE_H_INCLUDED
