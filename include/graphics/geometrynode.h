/**
 * @file graphics/geometrynode.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_GEOMETRYNODE_H_INCLUDED
#define GRAPHICS_GEOMETRYNODE_H_INCLUDED

#include <graphics/node.h>

class DrawParams;

/**
 * Abstract base class for all geometry nodes.
 */
class GeometryNode : public Node
{
public:
    /**
     * Destructor.
     */
    virtual ~GeometryNode();

    /**
     * Draws this geometry node.
     *
     * @param params Draw parameters.
     */
    virtual void draw(const DrawParams& params) const = 0;

    /**
     * @name Node Interface
     */
    //@{
    virtual GeometryNode* clone() const = 0;
    virtual void predraw(const PredrawParams&, bool) const;
    //@}

protected:
    /**
     * Default constructor.
     */
    GeometryNode();

    /**
     * Copy constructor.
     *
     * @param other The object to copy.
     */
    GeometryNode(const GeometryNode& other);

private:
    // hide the copy assignment operator
    GeometryNode& operator =(const GeometryNode&);
};

#endif // #ifndef GRAPHICS_GEOMETRYNODE_H_INCLUDED
