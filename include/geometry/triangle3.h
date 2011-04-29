/**
 * @file geometry/triangle3.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_TRIANGLE3_H_INCLUDED
#define GEOMETRY_TRIANGLE3_H_INCLUDED

#include <geometry/vector3.h>

class Line3;

// TODO: comments
class Triangle3
{
public:
    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

    /**
     * Default constructor, constructs an uninitialized triangle.
     */
    Triangle3();

    // assumes CCW ordering
    Triangle3(const Vector3& p0, const Vector3& p1, const Vector3& p2);

    Vector3 p0;
    Vector3 p1;
    Vector3 p2;
};

// TODO: comments
bool computeBarycentricCoords(
    const Triangle3& triangle,
    const Vector3& point,
    float b[3]);

// TODO: comments
bool intersect(const Triangle3& triangle, const Line3& line, float* t);

#endif // #ifndef GEOMETRY_TRIANGLE3_H_INCLUDED
