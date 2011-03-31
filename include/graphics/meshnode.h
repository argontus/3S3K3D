/**
 * @file graphics/meshnode.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_MESHNODE_H_INCLUDED
#define GRAPHICS_MESHNODE_H_INCLUDED

#include <geometry/extents3.h>

#include <graphics/geometrynode.h>

class Vector3Array;

class Mesh;

/**
 * Represents a triangle mesh.
 */
class MeshNode : public GeometryNode
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
     * Copy constructor.
     *
     * @param other The object to copy.
     */
    MeshNode(const MeshNode& other);

    /**
     * Updates model extents. This memeber function must be called if the model
     * geometry changes. The mesh pointer must be pointing to a valid mesh when
     * this member function is called.
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

    /**
     * @name Node Interface
     */
    //@{
    virtual MeshNode* clone() const;
    virtual const Extents3 worldExtents() const;

    // invalidates the world transform of this node, invalidates the world
    // extents of this node and all anchestor nodes
    virtual void invalidateWorldTransform() const;
    //@}

    /**
     * @name GeometryNode Interface
     */
    //@{
    /**
     * Draws this triangle mesh. The mesh pointer must be pointing to a valid
     * mesh when this member function is called.
     *
     * @param params Draw parameters.
     */
    virtual void draw(const DrawParams& params) const;
    //@}

private:
    /**
     * Invalidates the world extents.
     */
    void invalidateWorldExtents() const;

    /**
     * Updates and validates the world extents. This is called internally for
     * updating the world extents only when needed.
     */
    void updateWorldExtents() const;

    mutable bool worldExtentsValid_;    ///< Are world extents valid?
    mutable Extents3 worldExtents_;     ///< World extents.
    Extents3 modelExtents_;             ///< Model extents.
    Mesh* mesh_;                        ///< Mesh pointer.

    // hide the copy assignment operator
    MeshNode& operator =(const MeshNode&);
};

#endif // #ifndef GRAPHICS_MESHNODE_H_INCLUDED
