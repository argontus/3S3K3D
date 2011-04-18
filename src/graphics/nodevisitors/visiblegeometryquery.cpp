/**
 * @file graphics/nodevisitors/visiblegeometryquery.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/nodevisitors/visiblegeometryquery.h>

#include <graphics/runtimeassert.h>
#include <graphics/nodes/cameranode.h>
#include <graphics/nodes/meshnode.h>

VisibleGeometryQuery::~VisibleGeometryQuery()
{
    // ...
}

VisibleGeometryQuery::VisibleGeometryQuery()
:   test(),
    meshNodes(),
    otherNodes()
{
    // ...
}

void VisibleGeometryQuery::clear()
{
    meshNodes.clear();
    otherNodes.clear();
}

bool VisibleGeometryQuery::visit(CameraNode* const p)
{
    return visitOther(p);
}

bool VisibleGeometryQuery::visit(MeshNode* const p)
{
    const VisibilityState::Enum state = test.test(p->subtreeExtents());

    switch (state)
    {
        case VisibilityState::CompletelyVisible:
            // TODO: the visibility test could be disabled here
            // the subtree is completely visible, no need to test individual
            // nodes
            meshNodes.push_back(p);
            return true;

        case VisibilityState::PartiallyVisible:
            if (test.test(p->extents()) != VisibilityState::Invisible)
            {
                meshNodes.push_back(p);
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

bool VisibleGeometryQuery::visitOther(Node* const p)
{
    const VisibilityState::Enum state = test.test(p->subtreeExtents());

    switch (state)
    {
        case VisibilityState::CompletelyVisible:
            // TODO: the visibility test could be disabled here
            // the subtree is completely visible, no need to test individual
            // nodes
            otherNodes.push_back(p);
            return true;

        case VisibilityState::PartiallyVisible:
            // objects of type Node do not have own extents
            otherNodes.push_back(p);
            return true;

        case VisibilityState::Invisible:
            // the subtree is invisible, no need to test individual nodes
            return false;

        default:
            GRAPHICS_RUNTIME_ASSERT(false);
            return false;
    }
}
