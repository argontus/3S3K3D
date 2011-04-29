/**
 * @file graphics/nodevisitors/segmentmeshintersectionquery.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/nodevisitors/segmentmeshintersectionquery.h>

#include <geometry/linesegment3.h>
#include <geometry/math.h>
#include <geometry/triangle3.h>

#include <graphics/mesh.h>
#include <graphics/nodes/cameranode.h>
#include <graphics/nodes/meshnode.h>
#include <graphics/nodes/pointlightnode.h>

// TODO: does not belong here
namespace {

bool intersect(const Transform3& tr, const Mesh& mesh, const Line3& line, float* const tEnterOut)
{
    // TODO: transform the line instead of vertex positions

    bool intersects = false;
    float tEnter = Math::infinity();

    for (int i = 0; i < mesh.numFaces(); ++i)
    {
        const int i0 = 3 * i + 0;
        const int i1 = 3 * i + 1;
        const int i2 = 3 * i + 2;

        const Triangle3 triangle(
            transform(mesh.vertex(i0).position, tr),
            transform(mesh.vertex(i1).position, tr),
            transform(mesh.vertex(i2).position, tr)
        );

        float t;

        if (intersect(triangle, line, &t))
        {
            //if (t < tEnter)
            if (t < tEnter && t >= 0.0f)
            {
                tEnter = t;
                intersects = true;
            }
        }
    }

    if (intersects && tEnterOut != 0)
    {
        *tEnterOut = tEnter;
    }

    return intersects;
}

}

SegmentMeshIntersectionQuery::~SegmentMeshIntersectionQuery()
{
    // ...
}

SegmentMeshIntersectionQuery::SegmentMeshIntersectionQuery()
:   NodeVisitor(),
    line_(),
    meshNode_(0),
    tEnter_(0.0f)
{
    // ...
}

void SegmentMeshIntersectionQuery::init(const LineSegment3& segment)
{
    line_.point = segment.startPoint;
    line_.direction = segment.endPoint - segment.startPoint;
    meshNode_ = 0;
    tEnter_ = Math::infinity();
}

MeshNode* SegmentMeshIntersectionQuery::meshNode() const
{
    return meshNode_;
}

float SegmentMeshIntersectionQuery::tEnter() const
{
    return tEnter_;
}

bool SegmentMeshIntersectionQuery::visit(CameraNode* const p)
{
    return visitOther(p);
}

bool SegmentMeshIntersectionQuery::visit(MeshNode* const p)
{
    if (p->isSubtreeVisible() == false)
    {
        return false;
    }

    float tEnter;
    float tLeave;

    if (intersect(p->subtreeExtents(), line_, &tEnter, &tLeave))
    {
        if (tLeave < 0.0f || tEnter > 1.0f)
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    if (intersect(p->extents(), line_, &tEnter, &tLeave))
    {
/*
        // AABB - segment intersection
        if (tEnter >= 0.0f && tEnter <= 1.0f && tEnter < tEnter_)
        {
            meshNode_ = p;
            tEnter_ = tEnter;
        }
*/

        if (tLeave >= 0.0f && tEnter <= 1.0f)
        {
            // accurate mesh intersection test
            if (intersect(p->worldTransform(), *p->mesh(), line_, &tEnter))
            {
                if (tEnter >= 0.0f && tEnter <= 1.0f && tEnter < tEnter_)
                {
                    meshNode_ = p;
                    tEnter_ = tEnter;
                }
            }
        }

    }

    return true;
}

bool SegmentMeshIntersectionQuery::visit(Node* const p)
{
    return visitOther(p);
}

bool SegmentMeshIntersectionQuery::visit(PointLightNode* const p)
{
    return visitOther(p);
}

bool SegmentMeshIntersectionQuery::visitOther(Node* const p)
{
    if (p->isSubtreeVisible() == false)
    {
        return false;
    }

    return true;

    float tEnter;
    float tLeave;

    if (intersect(p->subtreeExtents(), line_, &tEnter, &tLeave))
    {
        return tLeave >= 0.0f && tEnter <= 1.0f;
    }
    else
    {
        return false;
    }
}
