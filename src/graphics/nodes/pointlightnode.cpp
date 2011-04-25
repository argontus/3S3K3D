/**
 * @file graphics/nodes/pointlightnode.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/nodes/pointlightnode.h>

#include <graphics/runtimeassert.h>
#include <graphics/nodevisitors/nodevisitor.h>

PointLightNode::~PointLightNode()
{
    // ...
}

PointLightNode::PointLightNode()
:   Node(),
    color_(1.0f, 1.0f, 1.0f),
    range_(1.0f)
{
    // ...
}

void PointLightNode::setLightColor(const Vector3& color)
{
    color_ = color;
}

const Vector3 PointLightNode::lightColor() const
{
    return color_;
}

void PointLightNode::setLightRange(const float range)
{
    GRAPHICS_RUNTIME_ASSERT(range > 0.0f);
    range_ = range;
}

float PointLightNode::lightRange() const
{
    return range_;
}

PointLightNode* PointLightNode::clone() const
{
    return new PointLightNode(*this);
}

PointLightNode::PointLightNode(const PointLightNode& other)
:   Node(other),
    color_(other.color_),
    range_(other.range_)
{
    // ...
}

bool PointLightNode::acceptImpl(NodeVisitor* const visitor)
{
    return visitor->visit(this);
}
