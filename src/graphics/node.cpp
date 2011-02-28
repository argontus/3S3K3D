/**
 * @file graphics/node.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/node.h>

#include <geometry/matrix4x4.h>

#include <graphics/groupnode.h>
#include <graphics/runtimeassert.h>

Node::~Node()
{
    // make sure we are not deleting a node that is still attached
    GRAPHICS_RUNTIME_ASSERT(hasParent() == false);

    // TODO: unregister from scene
}

void Node::invalidateWorldTransform() const
{
    worldTransformValid_ = false;
}

const Transform3 Node::worldTransform() const
{
    if (worldTransformValid_ == false)
    {
        updateWorldTransform();

        // updateWorldTransform() should validate the world transform
        GRAPHICS_RUNTIME_ASSERT(worldTransformValid_ == true);
    }

    return worldTransform_;
}

void Node::setTransform(const Transform3& transform)
{
    localTransform_ = transform;
    invalidateWorldTransform();

    // invalidateWorlTransform() should invalidate the world transform
    GRAPHICS_RUNTIME_ASSERT(worldTransformValid_ == false);
}

void Node::transformBy(const Transform3& transform)
{
    localTransform_.transformBy(transform);
    invalidateWorldTransform();

    // invalidateWorlTransform() should invalidate the world transform
    GRAPHICS_RUNTIME_ASSERT(worldTransformValid_ == false);
}

const Transform3 Node::transform() const
{
    return localTransform_;
}

void Node::setTranslation(const Vector3& translation)
{
    localTransform_.setTranslation(translation);
    invalidateWorldTransform();

    // invalidateWorlTransform() should invalidate the world transform
    GRAPHICS_RUNTIME_ASSERT(worldTransformValid_ == false);
}

void Node::translateBy(const Vector3& translation)
{
    localTransform_.translateBy(translation);
    invalidateWorldTransform();

    // invalidateWorlTransform() should invalidate the world transform
    GRAPHICS_RUNTIME_ASSERT(worldTransformValid_ == false);
}

const Vector3 Node::translation() const
{
    return localTransform_.translation();
}

void Node::setRotation(const Matrix3x3& rotation)
{
    localTransform_.setRotation(rotation);
    invalidateWorldTransform();

    // invalidateWorlTransform() should invalidate the world transform
    GRAPHICS_RUNTIME_ASSERT(worldTransformValid_ == false);
}

void Node::rotateBy(const Matrix3x3& rotation)
{
    localTransform_.rotateBy(rotation);
    invalidateWorldTransform();

    // invalidateWorlTransform() should invalidate the world transform
    GRAPHICS_RUNTIME_ASSERT(worldTransformValid_ == false);
}

const Matrix3x3 Node::rotation() const
{
    return localTransform_.rotation();
}

void Node::setScaling(const float scaling)
{
    GRAPHICS_RUNTIME_ASSERT(scaling > 0.0f);

    localTransform_.setScaling(scaling);
    invalidateWorldTransform();

    // invalidateWorlTransform() should invalidate the world transform
    GRAPHICS_RUNTIME_ASSERT(worldTransformValid_ == false);
}

void Node::scaleBy(const float scaling)
{
    GRAPHICS_RUNTIME_ASSERT(scaling > 0.0f);

    localTransform_.scaleBy(scaling);
    invalidateWorldTransform();

    // invalidateWorlTransform() should invalidate the world transform
    GRAPHICS_RUNTIME_ASSERT(worldTransformValid_ == false);
}

float Node::scaling() const
{
    return localTransform_.scaling();
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

    // invalidateWorlTransform() should invalidate the world transform
    GRAPHICS_RUNTIME_ASSERT(worldTransformValid_ == false);
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

    // invalidateWorlTransform() should invalidate the world transform
    GRAPHICS_RUNTIME_ASSERT(worldTransformValid_ == false);
}

bool Node::isScalingLocked() const
{
    return scalingLocked_;
}

const Matrix4x4 Node::modelToWorldMatrix() const
{
    return worldTransform().toMatrix4x4();
}

void Node::setScene(Scene* const scene)
{
    // make sure that this node is not being registered to multiple scenes
    GRAPHICS_RUNTIME_ASSERT(scene_ == 0 || scene == 0);

    scene_ = scene;
}

Scene* Node::scene() const
{
    return scene_;
}

void Node::setParent(GroupNode* const parent)
{
    // make sure we are not doing any unnecessary function calls and that this
    // node is not being attached to multiple parents
    GRAPHICS_RUNTIME_ASSERT(parent_ != parent);
    GRAPHICS_RUNTIME_ASSERT(parent_ == 0 || parent == 0);

    parent_ = parent;
}

GroupNode* Node::parent() const
{
    return parent_;
}

bool Node::hasParent() const
{
    return parent_ != 0;
}

Node::Node()
:   worldTransformValid_(false),
    worldTransform_(),
    localTransform_(),
    rotationLocked_(false),
    scalingLocked_(false),
    scene_(0),
    parent_(0)
{
    // ...
}

Node::Node(const Node& other)
:   worldTransformValid_(false),
    worldTransform_(),
    localTransform_(other.localTransform_),
    rotationLocked_(other.rotationLocked_),
    scalingLocked_(other.scalingLocked_),
    scene_(0),
    parent_(0)
{
    // ...
}

bool Node::isWorldTransformValid() const
{
    return worldTransformValid_;
}

void Node::updateWorldTransform() const
{
    // make sure we are not doing any unnecessary function calls
    GRAPHICS_RUNTIME_ASSERT(worldTransformValid_ == false);

    if (hasParent())
    {
        // world transform of the parent node
        const Transform3 t = parent_->worldTransform();

        worldTransform_.setTranslation(t.applyForward(localTransform_.translation()));
        worldTransform_.setRotation(localTransform_.rotation());
        worldTransform_.setScaling(localTransform_.scaling());

        if (rotationLocked_ == false)
        {
            worldTransform_.rotateBy(t.rotation());
        }

        if (scalingLocked_ == false)
        {
            worldTransform_.scaleBy(t.scaling());
        }
    }
    else
    {
        // no parent node, world transform is equal to the local transform
        worldTransform_ = localTransform_;
    }

    worldTransformValid_ = true;
}
