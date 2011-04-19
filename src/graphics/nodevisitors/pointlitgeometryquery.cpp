/**
 * @file graphics/nodevisitors/pointlitgeometryquery.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/nodevisitors/pointlitgeometryquery.h>

#include <graphics/runtimeassert.h>
#include <graphics/nodes/cameranode.h>
#include <graphics/nodes/meshnode.h>

PointLitGeometryQuery::~PointLitGeometryQuery()
{
    // ...
}

PointLitGeometryQuery::PointLitGeometryQuery()
:   NodeVisitor(),
    effectSphere_(),
    meshNodes_()
{
    // ...
}

void PointLitGeometryQuery::reset()
{
    meshNodes_.clear();
}

void PointLitGeometryQuery::init(const Sphere& effectSphere)
{
    effectSphere_ = effectSphere;
}

MeshNode* PointLitGeometryQuery::meshNode(const int index) const
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < numMeshNodes());
    return meshNodes_[index];
}

int PointLitGeometryQuery::numMeshNodes() const
{
    return meshNodes_.size();
}

bool PointLitGeometryQuery::visit(CameraNode* const p)
{
    return visitOther(p);
}

bool PointLitGeometryQuery::visit(MeshNode* const p)
{
    if (p->isSubtreeVisible() == false)
    {
        return false;
    }

    if (intersect(p->subtreeExtents(), effectSphere_) == false)
    {
        return false;
    }

    if (p->isVisible() && intersect(p->extents(), effectSphere_))
    {
        meshNodes_.push_back(p);
    }

    return true;
}

bool PointLitGeometryQuery::visit(Node* const p)
{
    return visitOther(p);
}

bool PointLitGeometryQuery::visitOther(Node* const p)
{
    if (p->isSubtreeVisible() == false)
    {
        return false;
    }

    return intersect(p->subtreeExtents(), effectSphere_);
}
