/**
 * @file graphics/node.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_NODE_H_INCLUDED
#define GRAPHICS_NODE_H_INCLUDED

#include <geometry/transform3.h>

class Extents3;
class Matrix4x4;

class GroupNode;
class PredrawParams;

/**
 * Abstract base class for all scene graph nodes.
 */
class Node
{
public:
    // TODO: controllers, updates and render settings management

    /**
     * Destructor. <code>*this</code> must be detached from its parent node
     * before the destructor is called. Calling the destructor will
     * automatically unregister the node from the scene.
     */
    virtual ~Node();

    /**
     * Virtual copy constructor.
     *
     * @return Dynamically allocated copy of this object.
     *
     * @warning The returned object is allocated via a C++ <code>new</code>
     * expression. The caller is responsible for deleting it.
     */
    virtual Node* clone() const = 0;

    /**
     * Recursive predraw traversal. Only <code>GeometryNode</code> and
     * <code>GroupNode</code> classes should override this member function.
     *
     * @param params Predraw parameters.
     * @param testVisibility Use visibility test? If this is
     * <code>false</code>, nodes are added to the render queue unconditionally
     * without visibility testing.
     */
    virtual void predraw(
        const PredrawParams& params,
        bool testVisibility) const = 0;

    /**
     * Gets the world extents.
     *
     * @return World extents.
     */
    virtual const Extents3 worldExtents() const = 0;

    // TODO: documentation for this member function is out of date
    /**
     * Invalidates the world transform. Only <code>GeometryNode</code> and
     * <code>GroupNode</code> classes should override this member function.
     */
    virtual void invalidateWorldTransform() const;

    /**
     * Gets the world transform.
     *
     * @return World transform.
     */
    const Transform3 worldTransform() const;

    /**
     * Sets the local transform.
     *
     * @param transform The transform to set as the local transform.
     */
    void setTransform(const Transform3& transform);

    /**
     * Applies a transform to the local transform.
     *
     * @param transform The transform to apply.
     */
    void transformBy(const Transform3& transform);

    /**
     * Gets the local transform.
     *
     * @return Local transform.
     */
    const Transform3 transform() const;

    /**
     * Sets the local translation.
     *
     * @param translation The translation to set as the local translation.
     */
    void setTranslation(const Vector3& translation);

    /**
     * Applies a translation to the local transform.
     *
     * @param translation The translation to apply.
     */
    void translateBy(const Vector3& translation);

    /**
     * Gets the local translation.
     *
     * @return Local translation.
     */
    const Vector3 translation() const;

    /**
     * Sets the local rotation.
     *
     * @param rotation The rotation to set as the local rotation, must be a
     * valid rotation matrix.
     */
    void setRotation(const Matrix3x3& rotation);

    /**
     * Applies a rotation to the local transform.
     *
     * @param rotation The rotation to apply, must be a valid rotation matrix.
     */
    void rotateBy(const Matrix3x3& rotation);

    /**
     * Gets the local rotation.
     *
     * @return Local rotation.
     */
    const Matrix3x3 rotation() const;

    /**
     * Sets the local scaling.
     *
     * @param scaling The scaling to set as the local scaling, must be > 0.
     */
    void setScaling(float scaling);

    /**
     * Applies a scaling to the local transform.
     *
     * @param scaling The scaling to apply, must be > 0.
     */
    void scaleBy(float scaling);

    /**
     * Gets the local scaling.
     *
     * @return Local scaling.
     */
    float scaling() const;

    /**
     * Sets the rotation lock status.
     *
     * @param locked Lock the world rotation to local rotation?
     */
    void setRotationLocked(bool locked);

    /**
     * Gets a boolean value indicating whether or not the world rotation is
     * locked to local rotation.
     *
     * @return <code>true</code>, if world rotation is locked to local
     * rotation, <code>false</code> otherwise.
     */
    bool isRotationLocked() const;

    /**
     * Sets the scaling lock status.
     *
     * @param locked Lock the world scaling to local scaling?
     */
    void setScalingLocked(bool locked);

    /**
     * Gets a boolean value indicating whether or not the world scaling is
     * locked to local scaling.
     *
     * @return <code>true</code>, if world scaling is locked to local scaling,
     * <code>false</code> otherwise.
     */
    bool isScalingLocked() const;

    /**
     * Calculates the model to world transform matrix.
     *
     * @return The calculated model to world transform matrix.
     */
    const Matrix4x4 modelToWorldMatrix() const;

    /**
     * Sets the parent node.
     *
     * @param parent Parent node.
     *
     * @warning For internal use only.
     */
    void setParent(GroupNode* parent);

    /**
     * Gets the parent node.
     *
     * @return Parent node.
     */
    GroupNode* parent() const;

    /**
     * Gets a boolean value indicating whether or not this node has a parent
     * node. The return value is equivalent to <code>parent() != 0</code>.
     *
     * @return <code>true</code>, if this node has a parent node,
     * <code>false</code> otherwise.
     */
    bool hasParent() const;

protected:
    /**
     * Default constructor.
     */
    Node();

    /**
     * Copy constructor. Copies all state but the constructed node is not
     * registered to a scene or attached to a group node.
     *
     * @param other The object to copy.
     */
    Node(const Node& other);

    /**
     * Gets a boolean value indicating whether or not the world extents are
     * valid.
     *
     * @return <code>true</code>, if world extents are valid,
     * <code>false</code> otherwise.
     */
    bool isWorldTransformValid() const;

private:
    /**
     * Updates and validates the world transform. This is called internally for
     * updating the world transform only when needed.
     */
    void updateWorldTransform() const;

    mutable bool worldTransformValid_;  ///< Is world transform valid?
    mutable Transform3 worldTransform_; ///< World transform.
    Transform3 localTransform_;         ///< Local transform.
    bool rotationLocked_;               ///< Is rotation locked to local rotation?
    bool scalingLocked_;                ///< Is scaling locked to local scaling?
    GroupNode* parent_;                 ///< Parent node.

    // hide the copy assignment operator
    Node& operator =(const Node&);
};

#endif // #ifndef GRAPHICS_NODE_H_INCLUDED
