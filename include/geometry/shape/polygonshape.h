#ifndef GEOMETRY_SHAPE_POLYGONSHAPE_H_INCLUDED
#define GEOMETRY_SHAPE_POLYGONSHAPE_H_INCLUDED

#include <vector>

#include <geometry/vector2.h>

#include <geometry/shape/primitiveshape.h>

class PolygonShape : public PrimitiveShape
{
public:
    virtual ~PolygonShape();

    template <class In>
    PolygonShape(In first, In last);

    PolygonShape(const PolygonShape& other);

    int numVertices() const;

    const Vector2 vertex(int index) const;
    const Vector2 normal(int index) const;

    virtual PolygonShape* clone() const;
    virtual const Extents2 extents() const;

private:
    void updateNormals();

    std::vector<Vector2> vertices_;
    std::vector<Vector2> normals_;

    // hide the assignment operator
    PolygonShape& operator =(const PolygonShape&);
};

#endif // #ifndef GEOMETRY_SHAPE_POLYGONSHAPE_H_INCLUDED
