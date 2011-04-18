/**
 * @file graphics/nodes/meshnode.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_MESHNODE_H_INCLUDED
#define GRAPHICS_MESHNODE_H_INCLUDED

#include <graphics/nodes/node.h>

class Mesh;
class VertexBuffer;

/**
 * Represents a triangle mesh.
 */
class MeshNode : public Node
{
public:
    /**
     * Destructor.
     */
    virtual ~MeshNode();

    /**
     * Default constructor.
     */
    MeshNode();

    /**
     * Updates the model space extents. This member function must be called if
     * the model geometry changes. The mesh pointer must be pointing to a valid
     * mesh when this member function is called.
     */
    void updateModelExtents();

    /**
     * Sets the mesh pointer. This object does not take ownership of the object
     * pointer by <code>p</code>.
     *
     * @param p Mesh pointer.
     */
    void setMesh(Mesh* p);

    /**
     * Gets the mesh pointer.
     *
     * @return Mesh pointer.
     */
    Mesh* mesh() const;

    // must be set before this object can be rendered
    void setVertexBuffer(VertexBuffer* vertexBuffer);
    VertexBuffer* vertexBuffer() const;

    /**
     * @name Node Interface
     */
    //@{
    virtual MeshNode* clone() const;
    virtual void draw(const DrawParams& params) const;
    //@}

protected:
    /**
     * Copy constructor. This is used only for implementing the clone
     * functionality and is protected to prevent slicing.
     *
     * @param other The object to copy.
     */
    MeshNode(const MeshNode& other);

private:
    /**
     * @name Private Node Interface
     */
    //@{
    virtual bool acceptImpl(NodeVisitor*);
    //@}

    // TODO: get rid of the mesh pointer?
    Mesh* mesh_;                    ///< Mesh pointer.
    VertexBuffer* vertexBuffer_;    ///< Vertex buffer.

    // hide the copy assignment operator
    MeshNode& operator =(const MeshNode&);
};

#endif // #ifndef GRAPHICS_MESHNODE_H_INCLUDED
