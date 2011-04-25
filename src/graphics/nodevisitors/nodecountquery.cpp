/**
 * @file graphics/nodevisitors/nodecountquery.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/nodevisitors/nodecountquery.h>

NodeCountQuery::~NodeCountQuery()
{
    // ...
}

NodeCountQuery::NodeCountQuery()
:   NodeVisitor(),
    numCameraNodes_(0),
    numMeshNodes_(0),
    numNodes_(0),
    numPointLightNodes_(0)
{
    // ...
}

void NodeCountQuery::reset()
{
    numCameraNodes_ = 0;
    numMeshNodes_ = 0;
    numNodes_ = 0;
    numPointLightNodes_ = 0;
}

int NodeCountQuery::numCameraNodes() const
{
    return numCameraNodes_;
}

int NodeCountQuery::numMeshNodes() const
{
    return numMeshNodes_;
}

int NodeCountQuery::numNodes() const
{
    return numNodes_;
}

int NodeCountQuery::numPointLightNodes() const
{
    return numPointLightNodes_;
}

int NodeCountQuery::total() const
{
    return numCameraNodes_ + numMeshNodes_ + numNodes_ + numPointLightNodes_;
}

bool NodeCountQuery::visit(CameraNode* const)
{
    ++numCameraNodes_;
    return true;
}

bool NodeCountQuery::visit(MeshNode* const)
{
    ++numMeshNodes_;
    return true;
}

bool NodeCountQuery::visit(Node* const)
{
    ++numNodes_;
    return true;
}

bool NodeCountQuery::visit(PointLightNode* const)
{
    ++numPointLightNodes_;
    return true;
}
