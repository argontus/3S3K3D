/**
 * @file graphics/nodes/pointlightnode.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_NODES_POINTLIGHTNODE_H_INCLUDED
#define GRAPHICS_NODES_POINTLIGHTNODE_H_INCLUDED

#include <graphics/nodes/node.h>

class PointLightNode : public Node
{
public:
    virtual ~PointLightNode();

    PointLightNode();

    void setLightColor(const Vector3& color);
    const Vector3 lightColor() const;

    void setLightRange(float range);
    float lightRange() const;

    /**
     * @name Node Interface
     */
    //@{
    virtual PointLightNode* clone() const;
    //@}

protected:
    /**
     * Copy constructor. This is used only for implementing the clone
     * functionality and is protected to prevent slicing.
     *
     * @param other The object to copy.
     */
    PointLightNode(const PointLightNode& other);

private:
    /**
     * @name Private Node Interface
     */
    //@{
    virtual bool acceptImpl(NodeVisitor*);
    //@}

    Vector3 color_;
    float range_;

    // hide the copy assignment operator
    PointLightNode& operator =(const PointLightNode&);
};

#endif // #ifndef GRAPHICS_NODES_POINTLIGHTNODE_H_INCLUDED
