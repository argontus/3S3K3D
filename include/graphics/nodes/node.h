/**
 * @file graphics/nodes/node.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_NODES_NODE_H_INCLUDED
#define GRAPHICS_NODES_NODE_H_INCLUDED

#include <vector>

#include <geometry/extents3.h>
#include <geometry/transform3.h>

class NodeVisitor;

// TODO: rename this to group node?
/**
 * Base class for all scene graph nodes. This class can be used as a group node
 * in node hierarchies.
 */
class Node
{
public:
    /**
     * Destructor. This node must be detached from its parent node before the
     * destructor is called.
     */
    virtual ~Node();

    /**
     * Default constructor.
     */
    Node();

    /**
     * Virtual copy constructor. This will also recursively clone all
     * descendant nodes.
     *
     * @return Dynamically allocated copy of this object.
     *
     * @warning The returned object is allocated via a C++ <code>new</code>
     * expression. The caller assumes its ownership and is responsible for
     * deleting it via a C++ <code>delete</code> expression.
     */
    virtual Node* clone() const;

    // recursive depth-first tree traversal, supports generic scene graph
    // queries
    void accept(NodeVisitor* visitor);

    // TODO: updates, controller management

    /**
     * @name Parent Node Queries
     */
    //@{
    /**
     * Gets the parent node.
     *
     * @return Parent node.
     */
    Node* parent() const;

    /**
     * Gets a boolean value indicating whether or not this node has a parent
     * node. The return value is equivalent to <code>parent() != 0</code>.
     *
     * @return <code>true</code>, if this node has a parent node,
     * <code>false</code> otherwise.
     */
    bool hasParent() const;
    //@}

    /**
     * @name Child Node Management
     */
    //@{
    /**
     * Attaches a child node to this node. This node assumes ownership of
     * <code>*p</code>.
     *
     * @param p Child node to attach. This must have been allocated via a C++
     * <code>new</code> expression and cannot be a null pointer.
     */
    void attachChild(Node* p);

    /**
     * Detaches a specified child node from this node.
     *
     * @param index Index of the child node to detach, must be between [0,
     * <code>numChildren()</code>).
     *
     * @return The detached child node.
     *
     * @warning The returned object is allocated via a C++ <code>new</code>
     * expression. The caller assumes its ownership and is responsible for
     * deleting it via a C++ <code>delete</code> expression.
     */
    Node* detachChild(int index);

    /**
     * Gets a specified child node.
     *
     * @param index Index of the child node to return, must be between [0,
     * <code>numChildren()</code>).
     *
     * @return The specified child node.
     */
    Node* child(int index) const;

    /**
     * Gets the number of child nodes.
     *
     * @return Number of child nodes.
     */
    int numChildren() const;

    /**
     * Gets a boolean value indicating whether or not this node has child
     * nodes. The return value is equivalent to <code>numChildren() > 0</code>.
     *
     * @return <code>true</code>, if this node has child nodes,
     * <code>false</code> otherwise.
     */
    bool hasChildren() const;
    //@}

    /**
     * @name Transform Management
     */
    //@{
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

    // TODO: is the scaling lock functionality needed anywhere?

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
     * Gets the model to world transform matrix.
     *
     * @return Model to world transform matrix.
     */
    const Matrix4x4 modelMatrix() const;
    //@}

    /**
     * @name Extents Queries
     */
    //@{
    /**
     * Gets the world space extents enclosing this subtree. The subtree
     * includes this node and all descendant nodes.
     *
     * @return World space extents enclosing this subtree.
     */
    const Extents3 subtreeExtents() const;

    /**
     * Gets the world space extents enclosing this node.
     *
     * @return World space extents enclosing this node.
     */
    const Extents3 extents() const;

    /**
     * Gets the model space extents enclosing this node.
     *
     * @return Model space extents enclosing this node.
     */
    const Extents3 modelExtents() const;
    //@}

    /**
     * @name Visibility State Management
     */
    //@{
    /**
     * Sets the subtree visibility state. The subtree includes this node and
     * all descendant nodes. Descendant nodes can override the visibility state
     * only by limiting it.
     *
     * @param visible Should this subtree be rendered?
     *
     * @see setVisible(bool)
     */
    void setSubtreeVisible(bool visible);

    /**
     * Gets the subtree visibility state. The subtree includes this node and
     * all descendant nodes.
     *
     * @return <code>true</code>, if this subtree should be rendered,
     * <code>false</code> otherwise.
     */
    bool isSubtreeVisible() const;

    // TODO: is node specific visibility state needed?

    /**
     * Sets the node visibility state. If the subtree visibility state has been
     * set to <code>false</code>, i.e.,
     * <code>isSubtreeVisible() == false</code>, setting the node visibility
     * state has no effect.
     *
     * @param visible Should this node be rendered?
     *
     * @see setSubtreeVisible(bool)
     */
    void setVisible(bool visible);

    /**
     * Gets the node visibility state.
     *
     * @return <code>true</code>, if this node should be rendered,
     * <code>false</code> otherwise.
     */
    bool isVisible() const;
    //@}

protected:
    /**
     * Copy constructor. This is used only for implementing the clone
     * functionality and is protected to prevent slicing.
     *
     * @param other The object to copy.
     */
    Node(const Node& other);

    /**
     * Sets the model space extents. Calling this function will invalidate the
     * world space node extents for this node and world space subtree extents
     * for this node and all anchestor nodes.
     *
     * @param modelExtents Model space extents.
     */
    void setModelExtents(const Extents3& modelExtents);

private:
    // derived classes must override this with an identical implementation
    virtual bool acceptImpl(NodeVisitor* visitor);

    /**
     * @name Helper Functions
     */
    //@{
    /**
     * Recursively deletes all descendant nodes.
     *
     * @warning This implements functionality common to the destructor and the
     * copy constructor, calling this member function from anywhere else would
     * leave this object in an invalid state.
     */
    void deleteChildren();
    //@}

    /**
     * @name Lazy Evaluation Support
     */
    //@{
    /**
     * Marks the world transform as invalid for this node and all descendant
     * nodes. This will also call <code>invalidateSubtreeExtents()</code> and
     * <code>invalidateExtents()</code>.
     *
     * @see invalidateSubtreeExtents() const
     * @see invalidateExtents() const
     */
    void invalidateWorldTransform() const;

    /**
     * Updates the world transform for this node. Calling this function will
     * propagate a recursive update to all anchestor nodes whose world
     * transform is invalid before calculating the new world transform.
     */
    void updateWorldTransform() const;

    /**
     * Marks the world space subtree extents as invalid for this node and all
     * anchestor nodes.
     */
    void invalidateSubtreeExtents() const;

    /**
     * Updates the world space subtree extents for this node. Calling this
     * function will propagate a recursive update call to all descendant nodes
     * whose world space subtree extents are invalid before calculating the new
     * subtree extents.
     */
    void updateSubtreeExtents() const;

    /**
     * Marks the world space node extents as invalid for this node.
     */
    void invalidateExtents() const;

    /**
     * Updates the world space node extents for this node.
     */
    void updateExtents() const;
    //@}

    // the implementation uses lazy evaluation for updating worldTransform_,
    // subtreeExtents_ and extents_

    Node* parent_;                      ///< Parent node.
    std::vector<Node*> children_;       ///< Child nodes.

    mutable bool worldTransformValid_;  ///< Is world transform valid?
    mutable Transform3 worldTransform_; ///< World transform.
    Transform3 localTransform_;         ///< Local transform.
    bool rotationLocked_;               ///< Is rotation locked to local?
    bool scalingLocked_;                ///< Is scaling locked to local?

    mutable bool subtreeExtentsValid_;  ///< Are subtree extents valid?
    mutable bool extentsValid_;         ///< Are node extents valid?
    mutable Extents3 subtreeExtents_;   ///< World space subtree extents.
    mutable Extents3 extents_;          ///< World space node extents.
    Extents3 modelExtents_;             ///< Model space node extents.

    bool subtreeVisible_;               ///< Is this subtree visible?
    bool visible_;                      ///< Is this node visible?

    // hide the assignment operator
    Node& operator =(const Node&);
};

#endif // #ifndef GRAPHICS_NODES_NODE_H_INCLUDED
