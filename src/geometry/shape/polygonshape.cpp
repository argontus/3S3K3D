/**
 * @file geometry/shape/polygonshape.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/shape/polygonshape.h>

#include <geometry/extents2.h>

PolygonShape::~PolygonShape()
{
    // ...
}

PolygonShape::PolygonShape(const PolygonShape& other)
:   vertices_(other.vertices_),
    normals_(other.normals_)
{
    // ...
}

int PolygonShape::numVertices() const
{
    return vertices_.size();
}

const Vector2 PolygonShape::vertex(const int index) const
{
    GEOMETRY_RUNTIME_ASSERT(index >= 0 && index < numVertices());
    return vertices_[index];
}

const Vector2 PolygonShape::normal(const int index) const
{
    GEOMETRY_RUNTIME_ASSERT(index >= 0 && index < numVertices());
    return normals_[index];
}

PolygonShape* PolygonShape::clone() const
{
    return new PolygonShape(*this);
}

const Extents2 PolygonShape::extents() const
{
    return Extents2(vertices_.begin(), vertices_.end());
}
