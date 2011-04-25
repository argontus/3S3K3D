/**
 * @file graphics/nodevisitors/visiblegeometryquery.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/nodevisitors/visiblegeometryquery.h>

#include <graphics/runtimeassert.h>
#include <graphics/nodes/cameranode.h>
#include <graphics/nodes/meshnode.h>
#include <graphics/nodes/pointlightnode.h>

VisibleGeometryQuery::~VisibleGeometryQuery()
{
    // ...
}

VisibleGeometryQuery::VisibleGeometryQuery()
:   NodeVisitor(),
    test_(),
    meshNodes_()
{
    // ...
}

void VisibleGeometryQuery::reset()
{
    meshNodes_.clear();
}

void VisibleGeometryQuery::init(const CameraNode& camera)
{
    test_.init(camera);
}

MeshNode* VisibleGeometryQuery::meshNode(const int index) const
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < numMeshNodes());
    return meshNodes_[index];
}

int VisibleGeometryQuery::numMeshNodes() const
{
    return meshNodes_.size();
}

bool VisibleGeometryQuery::visit(CameraNode* const p)
{
    return visitOther(p);
}

bool VisibleGeometryQuery::visit(MeshNode* const p)
{
    if (p->isSubtreeVisible() == false)
    {
        return false;
    }

    const VisibilityState::Enum state = test_.test(p->subtreeExtents());

    switch (state)
    {
        case VisibilityState::CompletelyVisible:
            // TODO: the visibility test could be disabled here
            // the subtree is completely visible, no need to test individual
            // nodes
            if (p->isVisible())
            {
                meshNodes_.push_back(p);
            }

            return true;

        case VisibilityState::PartiallyVisible:
            if (p->isVisible()
            &&  test_.test(p->extents()) != VisibilityState::Invisible)
            {
                meshNodes_.push_back(p);
            }

            return true;

        case VisibilityState::Invisible:
            // the subtree is invisible, no need to test individual nodes
            return false;

        default:
            GRAPHICS_RUNTIME_ASSERT(false);
            return false;
    }
}

bool VisibleGeometryQuery::visit(Node* const p)
{
    return visitOther(p);
}

bool VisibleGeometryQuery::visit(PointLightNode* const p)
{
    return visitOther(p);
}

bool VisibleGeometryQuery::visitOther(Node* const p)
{
    if (p->isSubtreeVisible() == false)
    {
        return false;
    }

    return test_.test(p->subtreeExtents()) != VisibilityState::Invisible;
}
