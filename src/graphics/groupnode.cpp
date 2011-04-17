/**
 * @file graphics/groupnode.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/groupnode.h>

#include <graphics/predrawparams.h>
#include <graphics/renderqueue.h>
#include <graphics/runtimeassert.h>
#include <graphics/visibilitytest.h>

GroupNode::~GroupNode()
{
    deleteChildren();
}

GroupNode::GroupNode()
:   Node(),
    worldExtentsValid_(false),
    worldExtents_(),
    children_()
{
    // ...
}

GroupNode::GroupNode(const GroupNode& other)
:   Node(other),
    worldExtentsValid_(false),
    worldExtents_(),
    children_()
{
    try
    {
        for (size_t i = 0; i < other.children_.size(); ++i)
        {
            attachChild(other.children_[i]->clone());
        }
    }
    catch (...)
    {
        // deallocate the nodes we had allocated before an exception was thrown
        deleteChildren();

        throw;
    }
}

void GroupNode::attachChild(Node* const p)
{
    GRAPHICS_RUNTIME_ASSERT(p != 0);
    GRAPHICS_RUNTIME_ASSERT(p->hasParent() == false);

    children_.push_back(p);

    // update back pointer
    p->setParent(this);

    // TODO: shouldn't the world extents be invalidated here?
}

void GroupNode::detachChild(Node* const p)
{
    NodeVector::iterator i = children_.begin();

    while (i != children_.end())
    {
        const Node* child = *i;

        if (child == p)
        {
            // detach, do not delete
            children_.erase(i);
            p->setParent(0);
            // TODO: shouldn't the world extents be invalidated here?
            return;
        }

        ++i;
    }

    // not found
    GRAPHICS_RUNTIME_ASSERT(false);
}

Node* GroupNode::child(const int index) const
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < numChildren());
    return children_[index];
}

int GroupNode::numChildren() const
{
    return children_.size();
}

bool GroupNode::hasChildren() const
{
    return children_.empty() == false;
}

void GroupNode::invalidateWorldExtents() const
{
    if (worldExtentsValid_ == false)
    {
        // TODO: make sure the world extents of all anchestor nodes are invalid

        // already invalidated, nothing to do
        return;
    }

    worldExtentsValid_ = false;

    if (hasParent())
    {
        // propagate the call to anchestor nodes
        parent()->invalidateWorldExtents();
    }
}

GroupNode* GroupNode::clone() const
{
    return new GroupNode(*this);
}

void GroupNode::predraw(const PredrawParams& params, bool testVisibility) const
{
    if (testVisibility)
    {
        const VisibilityState::Enum state = params.visibilityTest()->test(worldExtents());

        if (state == VisibilityState::Invisible)
        {
            // early out
            return;
        }

        if (state == VisibilityState::CompletelyVisible)
        {
            // all child nodes are completely visible
            testVisibility = false;
        }
    }

    // propagate the call to all attached child nodes
    for (size_t i = 0; i < children_.size(); ++i)
    {
        children_[i]->predraw(params, testVisibility);
    }

    params.renderQueue()->addGroupNode(this);
}

const Extents3 GroupNode::worldExtents() const
{
    if (worldExtentsValid_ == false)
    {
        updateWorldExtents();

        // updateWorldExtents() should validate the world transform
        GRAPHICS_RUNTIME_ASSERT(worldExtentsValid_ == true);
    }

    return worldExtents_;
}

void GroupNode::invalidateWorldTransform() const
{
    if (isWorldTransformValid() == false)
    {
        // TODO: make sure the world extents of all child nodes are invalid

        // already invalidated, nothing to do
        return;
    }

    // call the base class version
    Node::invalidateWorldTransform();

    // propagate the call to all attached child nodes
    for (size_t i = 0; i < children_.size(); ++i)
    {
        // invalidates the world extents of this group node if any of the
        // direct or indirect child nodes is a geometry node
        children_[i]->invalidateWorldTransform();
    }
}

void GroupNode::deleteChildren()
{
    // deallocate attached child nodes
    for (size_t i = 0; i < children_.size(); ++i)
    {
        children_[i]->setParent(0);
        delete children_[i];
    }
}

void GroupNode::updateWorldExtents() const
{
    // make sure we are not doing any unnecessary function calls
    GRAPHICS_RUNTIME_ASSERT(worldExtentsValid_ == false);

    worldExtents_.clear();

    for (size_t i = 0; i < children_.size(); ++i)
    {
        worldExtents_.enclose(children_[i]->worldExtents());
    }

    worldExtentsValid_ = true;
}
