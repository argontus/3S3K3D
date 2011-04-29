/**
 * @file geometry/triangle3.cpp
 * @author Mika Haarahiltunen
 */

#include <geometry/triangle3.h>

#include <geometry/line3.h>
#include <geometry/math.h>
#include <geometry/plane3.h>
#include <geometry/runtimeassert.h>

Triangle3::Triangle3()
{
    // ...
}

Triangle3::Triangle3(const Vector3& p0, const Vector3& p1, const Vector3& p2)
:   p0(p0),
    p1(p1),
    p2(p2)
{
    // ...
}

bool computeBarycentricCoords(
    const Triangle3& triangle,
    const Vector3& p,
    float b[3])
{
    // 3D Math Primer for Graphics and Game Development, 12.6.3

    GEOMETRY_RUNTIME_ASSERT(b != 0);

    const Vector3 v[] = { triangle.p0, triangle.p1, triangle.p2 };

    // First, compute two CCW edge vectors
    const Vector3 d1 = v[1] - v[0];
    const Vector3 d2 = v[2] - v[1];

    // Compute surface normal using cross product. In many cases
    // this step could be skipped, since we would have the surface
    // normal precomputed. We do not need to normalize it, although
    // if a precomputed normal was normalized, it would be OK.
    const Vector3 n = cross(d1, d2);

    // Locate dominant axis of normal, and select plane of projection
    float u1, u2, u3, u4;
    float v1, v2, v3, v4;

    if ((Math::abs(n.x) >= Math::abs(n.y)) && (Math::abs(n.x) >= Math::abs(n.z)))
    {
        // Discard x, project onto yz plane
        u1 = v[0].y - v[2].y;
        u2 = v[1].y - v[2].y;
        u3 = p.y - v[0].y;
        u4 = p.y - v[2].y;

        v1 = v[0].z - v[2].z;
        v2 = v[1].z - v[2].z;
        v3 = p.z - v[0].z;
        v4 = p.z - v[2].z;
    }
    else if (Math::abs(n.y) >= Math::abs(n.z))
    {
        // Discard y, project onto xz plane
        u1 = v[0].z - v[2].z;
        u2 = v[1].z - v[2].z;
        u3 = p.z - v[0].z;
        u4 = p.z - v[2].z;

        v1 = v[0].x - v[2].x;
        v2 = v[1].x - v[2].x;
        v3 = p.x - v[0].x;
        v4 = p.x - v[2].x;
    }
    else
    {
        // Discard z, project onto xy plane
        u1 = v[0].x - v[2].x;
        u2 = v[1].x - v[2].x;
        u3 = p.x - v[0].x;
        u4 = p.x - v[2].x;

        v1 = v[0].y - v[2].y;
        v2 = v[1].y - v[2].y;
        v3 = p.y - v[0].y;
        v4 = p.y - v[2].y;
    }

    // Compute denominator, check for invalid
    const float denom = v1 * u2 - v2 * u1;

    if (denom == 0.0f)
    {
        // Bogus triangle - probably triangle has zero area
        return false;
    }

    // Compute barycentric coordinates
    const float oneOverDenom = 1.0f / denom;
    b[0] = (v4 * u2 - v2 * u4) * oneOverDenom;
    b[1] = (v1 * u3 - v3 * u1) * oneOverDenom;
    b[2] = 1.0f - b[0] - b[1];

    // OK
    return true;
}

bool intersect(const Triangle3& triangle, const Line3& line, float* const tOut)
{
    const Plane3 plane(triangle.p0, triangle.p1, triangle.p2);

    if (dot(line.direction, plane.normal) >= 0.0f)
    {
        // back facing triangle, early out
        return false;
    }

    float t;

    if (intersect(plane, line, &t) == false)
    {
        return false;
    }

    const Vector3 intersection = line.point + t * line.direction;

    float b[3];

    if (computeBarycentricCoords(triangle, intersection, b) == false)
    {
        return false;
    }

    if (b[0] < 0.0f || b[1] < 0.0f || b[2] < 0.0f)
    {
        return false;
    }
/*
    // simple working implementation for comparison

    const Line3 edges[] = {
        Line3(triangle.p0, normalize(triangle.p1 - triangle.p0)),
        Line3(triangle.p1, normalize(triangle.p2 - triangle.p1)),
        Line3(triangle.p2, normalize(triangle.p0 - triangle.p2))
    };

    const Vector3 normals[] = {
        normalize(triangle.p2 - closestPoint(edges[0], triangle.p2)),
        normalize(triangle.p0 - closestPoint(edges[1], triangle.p0)),
        normalize(triangle.p1 - closestPoint(edges[2], triangle.p1))
    };

    const Plane3 planes[] = {
        Plane3(normals[0], triangle.p0),
        Plane3(normals[1], triangle.p1),
        Plane3(normals[2], triangle.p2)
    };

    for (int i = 0; i < 3; ++i)
    {
        if (separation(planes[i], intersection) < 0.0f)
        {
            return false;
        }
    }
*/
    if (tOut != 0)
    {
        *tOut = t;
    }

    return true;
}
