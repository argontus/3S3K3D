/**
 * @file graphics/nodes/node.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/nodes/node.h>

#include <geometry/matrix4x4.h>

#include <graphics/runtimeassert.h>
#include <graphics/nodevisitors/nodevisitor.h>

Node::~Node()
{
    // make sure we are not deleting a node that is still attached
    GRAPHICS_RUNTIME_ASSERT(hasParent() == false);

    // this will recrsively delete all descendant nodes
    deleteChildren();
}

Node::Node()
:   parent_(0),
    children_(),
    worldTransformValid_(false),
    worldTransform_(),
    localTransform_(),
    rotationLocked_(false),
    scalingLocked_(false),
    subtreeExtentsValid_(false),
    extentsValid_(false),
    subtreeExtents_(),
    extents_(),
    modelExtents_(),
    subtreeVisible_(true),
    visible_(true)
{
    // ...
}

Node* Node::clone() const
{
    return new Node(*this);
}

void Node::accept(NodeVisitor* const visitor)
{
    GRAPHICS_RUNTIME_ASSERT(visitor != 0);

    // TODO: try these as an optimization when FSP can be compared
    //visitor->pushState();

    // calls 'visitor->visit(this)' with 'this' converted to the actual
    // type of this object, returns true if child nodes should be visited
    if (acceptImpl(visitor))
    {
        for (size_t i = 0; i < children_.size(); ++i)
        {
            children_[i]->accept(visitor);
        }
    }

    // TODO: try these as an optimization when FSP can be compared
    //visitor->popState();
}

Node* Node::parent() const
{
    return parent_;
}

bool Node::hasParent() const
{
    return parent_ != 0;
}

void Node::attachChild(Node* const p)
{
    GRAPHICS_RUNTIME_ASSERT(p != 0);
    GRAPHICS_RUNTIME_ASSERT(p->hasParent() == false);

    // add the node and update its parent node back pointer
    children_.push_back(p);
    p->parent_ = this;

    // attached a new node, the subtree extents must be updated
    invalidateSubtreeExtents();
}

Node* Node::detachChild(const int index)
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < numChildren());

    Node* const p = children_[index];

    // remove the node and reset its parent node back pointer
    children_.erase(children_.begin() + index);
    p->parent_ = 0;

    // detached a node, the subtree extents must be updated
    invalidateSubtreeExtents();

    return p;
}

Node* Node::child(const int index) const
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < numChildren());
    return children_[index];
}

int Node::numChildren() const
{
    return children_.size();
}

bool Node::hasChildren() const
{
    return children_.empty() == false;
}

const Transform3 Node::worldTransform() const
{
    if (worldTransformValid_ == false)
    {
        updateWorldTransform();
    }

    return worldTransform_;
}

void Node::setTransform(const Transform3& transform)
{
    localTransform_ = transform;
    invalidateWorldTransform();
}

void Node::transformBy(const Transform3& transform)
{
    localTransform_ = ::transform(localTransform_, transform);
    invalidateWorldTransform();
}

const Transform3 Node::transform() const
{
    return localTransform_;
}

void Node::setTranslation(const Vector3& translation)
{
    localTransform_.translation = translation;
    invalidateWorldTransform();
}

void Node::translateBy(const Vector3& translation)
{
    localTransform_.translation += translation;
    invalidateWorldTransform();
}

const Vector3 Node::translation() const
{
    return localTransform_.translation;
}

void Node::setRotation(const Matrix3x3& rotation)
{
    localTransform_.rotation = rotation;
    invalidateWorldTransform();
}

void Node::rotateBy(const Matrix3x3& rotation)
{
    localTransform_.rotation *= rotation;
    invalidateWorldTransform();
}

const Matrix3x3 Node::rotation() const
{
    return localTransform_.rotation;
}

void Node::setScaling(const float scaling)
{
    GRAPHICS_RUNTIME_ASSERT(scaling > 0.0f);

    localTransform_.scaling = scaling;
    invalidateWorldTransform();
}

void Node::scaleBy(const float scaling)
{
    GRAPHICS_RUNTIME_ASSERT(scaling > 0.0f);

    localTransform_.scaling *= scaling;
    invalidateWorldTransform();
}

float Node::scaling() const
{
    return localTransform_.scaling;
}

void Node::setRotationLocked(const bool locked)
{
    if (rotationLocked_ == locked)
    {
        // nothing to do
        return;
    }

    rotationLocked_ = locked;
    invalidateWorldTransform();
}

bool Node::isRotationLocked() const
{
    return rotationLocked_;
}

void Node::setScalingLocked(const bool locked)
{
    if (scalingLocked_ == locked)
    {
        // nothing to do
        return;
    }

    scalingLocked_ = locked;
    invalidateWorldTransform();
}

bool Node::isScalingLocked() const
{
    return scalingLocked_;
}

const Matrix4x4 Node::modelMatrix() const
{
    // querying the world transform may trigger a recursive update all the way
    // to the root node
    return toMatrix4x4(worldTransform());
}

const Extents3 Node::subtreeExtents() const
{
    if (subtreeExtentsValid_ == false)
    {
        updateSubtreeExtents();
    }

    return subtreeExtents_;
}

const Extents3 Node::extents() const
{
    if (extentsValid_ == false)
    {
        updateExtents();
    }

    return extents_;
}

const Extents3 Node::modelExtents() const
{
    return modelExtents_;
}

void Node::setSubtreeVisible(const bool visible)
{
    subtreeVisible_ = visible;
}

bool Node::isSubtreeVisible() const
{
    return subtreeVisible_;
}

void Node::setVisible(const bool visible)
{
    visible_ = visible;
}

bool Node::isVisible() const
{
    return visible_;
}

Node::Node(const Node& other)
:   parent_(0),
    children_(),
    worldTransformValid_(false),
    worldTransform_(),
    localTransform_(other.localTransform_),
    rotationLocked_(other.rotationLocked_),
    scalingLocked_(other.scalingLocked_),
    subtreeExtentsValid_(false),
    extentsValid_(false),
    subtreeExtents_(),
    extents_(),
    modelExtents_(other.modelExtents_),
    subtreeVisible_(other.subtreeVisible_),
    visible_(other.visible_)
{
    try
    {
        // clone and attach all descendant nodes recursively
        for (size_t i = 0; i < other.children_.size(); ++i)
        {
            attachChild(other.children_[i]->clone());
        }
    }
    catch (...)
    {
        // deallocate the nodes we had allocated before an exception was thrown
        // and rethrow
        deleteChildren();
        throw;
    }
}

void Node::setModelExtents(const Extents3& modelExtents)
{
    modelExtents_ = modelExtents;

    // model extents have changed, subtree and node extents must be updated
    invalidateSubtreeExtents();
    invalidateExtents();
}

bool Node::acceptImpl(NodeVisitor* const visitor)
{
    return visitor->visit(this);
}

void Node::deleteChildren()
{
    // deallocate attached child nodes
    for (size_t i = 0; i < children_.size(); ++i)
    {
        children_[i]->parent_ = 0;
        delete children_[i];
    }
}

void Node::invalidateWorldTransform() const
{
    if (worldTransformValid_ == false)
    {
        GRAPHICS_RUNTIME_ASSERT(subtreeExtentsValid_ == false);
        GRAPHICS_RUNTIME_ASSERT(extentsValid_ == false);

        // TODO: make sure the subtree and node extents of all descendant nodes
        // are invalid

        // already invalidated, nothing to do
        return;
    }

    worldTransformValid_ = false;

    // world transform has changed, subtree and node extents must be updated
    invalidateSubtreeExtents();
    invalidateExtents();

    // propagate the call to all attached child nodes
    for (size_t i = 0; i < children_.size(); ++i)
    {
        // TODO: all child nodes will try to invalidate the subtree extents of
        // this node, get rid of unneeded invalidation attempts

        children_[i]->invalidateWorldTransform();
    }
}

void Node::updateWorldTransform() const
{
    // make sure we are not doing any unnecessary function calls
    GRAPHICS_RUNTIME_ASSERT(worldTransformValid_ == false);

    if (hasParent())
    {
        // world transform of the parent node, querying it may trigger a
        // recursive update all the way to the root node
        const Transform3 t = parent_->worldTransform();

        worldTransform_.translation = ::transform(localTransform_.translation, t);
        worldTransform_.rotation = localTransform_.rotation;
        worldTransform_.scaling = localTransform_.scaling;

        if (rotationLocked_ == false)
        {
            worldTransform_.rotation *= t.rotation;
        }

        if (scalingLocked_ == false)
        {
            worldTransform_.scaling *= t.scaling;
        }
    }
    else
    {
        // no parent node, world transform is equal to the local transform
        worldTransform_ = localTransform_;
    }

    worldTransformValid_ = true;
}

void Node::invalidateSubtreeExtents() const
{
    if (subtreeExtentsValid_ == false)
    {
        // TODO: make sure the subtree extents of all anchestor nodes are
        // invalid

        // already invalidated, nothing to do
        return;
    }

    subtreeExtentsValid_ = false;

    if (hasParent())
    {
        // propagate the call recursively to anchestor nodes
        parent_->invalidateSubtreeExtents();
    }
}

void Node::updateSubtreeExtents() const
{
    // make sure we are not doing any unnecessary function calls
    GRAPHICS_RUNTIME_ASSERT(subtreeExtentsValid_ == false);

    // TODO: should visibility flags affect the extents calculation?

    subtreeExtents_ = extents();

    for (size_t i = 0; i < children_.size(); ++i)
    {
        subtreeExtents_.enclose(children_[i]->subtreeExtents());
    }

    subtreeExtentsValid_ = true;
}

void Node::invalidateExtents() const
{
    extentsValid_ = false;
}

void Node::updateExtents() const
{
    // make sure we are not doing any unnecessary function calls
    GRAPHICS_RUNTIME_ASSERT(extentsValid_ == false);

    // TODO: should visibility flags affect the extents calculation?

    // querying the world transform may trigger a recursive update all the way
    // to the root node
    extents_ = ::transform(modelExtents_, worldTransform());
    extentsValid_ = true;
}
