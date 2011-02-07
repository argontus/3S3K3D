/**
 * @file graphics/geometrynode.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/geometrynode.h>

#include <graphics/predrawparams.h>
#include <graphics/renderqueue.h>

GeometryNode::~GeometryNode()
{
    // ...
}

void GeometryNode::predraw(const PredrawParams& params) const
{
    // TODO: early out if the world extents are not visible

    params.renderQueue->append(this);
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
