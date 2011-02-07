/**
 * @file graphics/groupnode.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_GROUPNODE_H_INCLUDED
#define GRAPHICS_GROUPNODE_H_INCLUDED

#include <vector>

#include <geometry/extents3.h>

#include <graphics/node.h>

/**
 * A node that can contain child nodes.
 */
class GroupNode : public Node
{
public:
    /**
     * Destructor.
     */
    virtual ~GroupNode();

    /**
     * Default constructor.
     */
    GroupNode();

    /**
     * Copy constructor.
     *
     * @param other The object to copy.
     */
    GroupNode(const GroupNode& other);

    // TODO: comments
    void attachChild(Node* p);
    void detachChild(Node* p);
    Node* child(int index) const;
    int numChildren() const;
    bool hasChildren() const;

    /**
     * Invalidates the world extents.
     */
    void invalidateWorlExtents() const;

    /**
     * @name Node Interface
     */
    //@{
    virtual GroupNode* clone() const;
    virtual void predraw(const PredrawParams& params) const;
    virtual const Extents3 worldExtents() const;

    // invalidates the world transform of this node and all direct and indirect
    // child nodes
    virtual void invalidateWorlTransform() const;

    virtual void setScene(Scene* scene);
    //@}

private:
    /**
     * Deallocates all attached child nodes. Calling this member function will
     * leave the object in an invalid state.
     */
    void deleteChildren();

    /**
     * Updates and validates the world extents. This is called internally for
     * updating the world extents only when needed.
     */
    void updateWorldExtents() const;

    typedef std::vector<Node*> NodeVector;

    mutable bool worldExtentsValid_;    ///< Are world extents valid?
    mutable Extents3 worldExtents_;     ///< World extents.
    NodeVector children_;               ///< Child nodes.

    // hide the copy assignment operator
    GroupNode& operator =(const GroupNode&);
};

#endif // #ifndef GRAPHICS_GROUPNODE_H_INCLUDED
