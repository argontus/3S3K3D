#ifndef GEOMETRY_SHAPE_CIRCLESHAPE_H_INCLUDED
#define GEOMETRY_SHAPE_CIRCLESHAPE_H_INCLUDED

#include <geometry/vector2.h>

#include <geometry/shape/primitiveshape.h>

class CircleShape : public PrimitiveShape
{
public:
    virtual ~CircleShape();

    CircleShape(const Vector2& center, float radius);
    CircleShape(const CircleShape& other);

    const Vector2 center() const;
    float radius() const;

    virtual CircleShape* clone() const;
    virtual const Extents2 extents() const;

private:
    Vector2 center_;
    float radius_;

    // hide the assignment operator
    CircleShape& operator =(const CircleShape&);
};

#endif // #ifndef GEOMETRY_SHAPE_CIRCLESHAPE_H_INCLUDED
