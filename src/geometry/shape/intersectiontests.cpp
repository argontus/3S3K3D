/**
 * @file geometry/shape/intersectiontests.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/shape/intersectiontests.h>

#include <typeinfo>

#include <geometry/linesegment2.h>
#include <geometry/math.h>
#include <geometry/plane2.h>
#include <geometry/transform2.h>

#include <geometry/shape/circleshape.h>
#include <geometry/shape/compositeshape.h>
#include <geometry/shape/polygonshape.h>

namespace {

int referenceEdge(const PolygonShape& polygon, const Vector2& point)
{
    float maxSeparation = -Math::infinity();
    int index = 0;

    for (int i = 0; i < polygon.numVertices(); ++i)
    {
        const Vector2 axis = polygon.normal(i);

        const float dPoint = dot(point, axis);
        const float dReference = dot(polygon.vertex(i), axis);

        const float separation = dPoint - dReference;

        if (separation > maxSeparation)
        {
            maxSeparation = separation;
            index = i;
        }
    }

    return index;
}

int supportVertex(const PolygonShape& polygon, const Vector2& axis)
{
    float minExtent = dot(polygon.vertex(0), axis);
    int index = 0;

    for (int i = 1; i < polygon.numVertices(); ++i)
    {
        const float d = dot(polygon.vertex(i), axis);

        if (d < minExtent)
        {
            minExtent = d;
            index = i;
        }
    }

    return index;
}

bool intersectFirst(const PolygonShape& a, const PolygonShape& b, const Transform2& t)
{
    for (int i = 0; i < a.numVertices(); ++i)
    {
        // edge normal in local space of a
        const Vector2 axis = a.normal(i);

        const int n = supportVertex(b, axis * t.rotation);

        // maximum extent of a and minimum extent of b along axis in local
        // space of a
        const float aMax = dot(a.vertex(i), axis);
        const float bMin = dot(transformByInverse(b.vertex(n), t), axis);

        if (bMin > aMax)
        {
            // the polygons are separated, no intersection
            return false;
        }
    }

    return true;
}

} // namespace

bool intersect(const Shape& a, const Shape& b, const Transform2& t)
{
    if (typeid(a) == typeid(CircleShape))
    {
        if (typeid(b) == typeid(CircleShape))
        {
            return intersect(
                static_cast<const CircleShape&>(a),
                static_cast<const CircleShape&>(b),
                t
            );
        }
        else if (typeid(b) == typeid(CompositeShape))
        {
            return intersect(
                static_cast<const CompositeShape&>(b),
                a,
                inverse(t)
            );
        }
        else if (typeid(b) == typeid(PolygonShape))
        {
            return intersect(
                static_cast<const CircleShape&>(a),
                static_cast<const PolygonShape&>(b),
                t
            );
        }
    }
    else if (typeid(a) == typeid(CompositeShape))
    {
        return intersect(static_cast<const CompositeShape&>(a), b, t);
    }
    else if (typeid(a) == typeid(PolygonShape))
    {
        if (typeid(b) == typeid(CircleShape))
        {
            return intersect(
                static_cast<const CircleShape&>(b),
                static_cast<const PolygonShape&>(a),
                inverse(t)
            );
        }
        else if (typeid(b) == typeid(CompositeShape))
        {
            return intersect(
                static_cast<const CompositeShape&>(b),
                a,
                inverse(t)
            );
        }
        else if (typeid(b) == typeid(PolygonShape))
        {
            return intersect(
                static_cast<const PolygonShape&>(a),
                static_cast<const PolygonShape&>(b),
                t
            );
        }
    }

    GEOMETRY_RUNTIME_ASSERT(false);
    return false;
}

bool intersect(const CircleShape& a, const CircleShape& b, const Transform2& t)
{
    // center point and radius of a in local space of b
    const Vector2 center = transform(a.center(), t);
    const float radius = t.scaling * a.radius();

    return sqrDistance(center, b.center()) <= Math::sqr(radius + b.radius());
}

bool intersect(const CircleShape& a, const PolygonShape& b, const Transform2& t)
{
    // center point and radius of a in local space of b
    const Vector2 center = transform(a.center(), t);
    const float radius = t.scaling * a.radius();

    const int i = referenceEdge(b, center);
    const int j = (i + 1) % b.numVertices();

    const LineSegment2 refEdge(b.vertex(i), b.vertex(j));
    const Vector2 refNormal = b.normal(i);

    // reference edge side plane
    const Plane2 plane(perp(refNormal), refEdge.startPoint);

    const float d = separation(plane, center);

    if (d < 0.0f)
    {
        // the center is closest to refEdge.startPoint
        return sqrDistance(refEdge.startPoint, center) < Math::sqr(radius);
    }

    if (d > separation(plane, refEdge.endPoint))
    {
        // the center is closest to refEdge.endPoint
        return sqrDistance(refEdge.endPoint, center) < Math::sqr(radius);
    }

    const float aMin = dot(center, refNormal) - radius;
    const float bMax = dot(b.vertex(i), refNormal);

    const float separation = aMin - bMax;

    return separation <= 0.0f;
}

bool intersect(const CompositeShape& a, const Shape& b, const Transform2& t)
{
    for (int i = 0; i < a.numPrimitives(); ++i)
    {
        if (intersect(a.primitive(i), b, t))
        {
            return true;
        }
    }

    return false;
}

bool intersect(const PolygonShape& a, const PolygonShape& b, const Transform2& t)
{
    return intersectFirst(a, b, t) && intersectFirst(b, a, inverse(t));
}
