/**
 * @file geometry/shape/intersectiontests.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_SHAPE_INTERSECTIONTESTS_H_INCLUDED
#define GEOMETRY_SHAPE_INTERSECTIONTESTS_H_INCLUDED

class Transform2;

class CircleShape;
class CompositeShape;
class PolygonShape;
class Shape;

// calls the correct specialized version based on the type of given shapes
bool intersect(const Shape& a, const Shape& b, const Transform2& t);

/**
 * @name Specialized Intersection Tests
 */
//@{
bool intersect(const CircleShape& a, const CircleShape& b, const Transform2& t);
bool intersect(const CircleShape& a, const PolygonShape& b, const Transform2& t);
bool intersect(const CompositeShape& a, const Shape& b, const Transform2& t);
bool intersect(const PolygonShape& a, const PolygonShape& b, const Transform2& t);
//@}

#endif // #ifndef GEOMETRY_SHAPE_INTERSECTIONTESTS_H_INCLUDED
