/**
 * @file graphics/geometrynode.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/geometrynode.h>

#include <geometry/extents3.h>

#include <graphics/predrawparams.h>
#include <graphics/renderqueue.h>
#include <graphics/visibilitytest.h>

GeometryNode::~GeometryNode()
{
    // ...
}

void GeometryNode::predraw(
    const PredrawParams& params,
    const bool testVisibility) const
{
    if (testVisibility
    &&  params.visibilityTest()->test(worldExtents()) == VisibilityState::Invisible)
    {
        // early out
        return;
    }

    params.renderQueue()->addGeometryNode(this);
}

GeometryNode::GeometryNode()
:   Node()
{
    // ...
}

GeometryNode::GeometryNode(const GeometryNode& other)
:   Node(other)
{
    // ...
}
