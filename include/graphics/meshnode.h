/**
 * @file graphics/meshnode.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_MESHNODE_H_INCLUDED
#define GRAPHICS_MESHNODE_H_INCLUDED

#include <geometry/extents3.h>

#include <graphics/geometrynode.h>

class Vector3Array;

class ColorArray;
class IndexArray;

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
     * geometry changes. The vertex and index array pointers must be pointing
     * to valid arrays when this member function is called.
     */
    void updateModelExtents();

    /**
     * Sets the vertex array pointer. This object does not take ownership of
     * the object pointer by <code>p</code>.
     *
     * @param p Vertex array pointer.
     */
    void setVertexArray(Vector3Array* p);

    /**
     * Gets the vertex array pointer.
     *
     * @return Vertex array pointer.
     */
    Vector3Array* vertexArray() const;

    void setNormalArray(Vector3Array* p) { normalArray_ = p; }
    Vector3Array* normalArray() const { return normalArray_; }

    void setColorArray(ColorArray* p) { colorArray_ = p; }
    ColorArray* colorArray() const { return colorArray_; }

    /**
     * Sets the index array pointer. This object does not take ownership of the
     * object pointer by <code>p</code>.
     *
     * @param p Index array pointer.
     */
    void setIndexArray(IndexArray* p);

    /**
     * Gets the index array pointer.
     *
     * @return Index array pointer.
     */
    IndexArray* indexArray() const;

    /**
     * @name Node Interface
     */
    //@{
    virtual MeshNode* clone() const;
    virtual const Extents3 worldExtents() const;

    // invalidates the world transform of this node, invalidates the world
    // extents of this node and all anchestor nodes
    virtual void invalidateWorlTransform() const;
    //@}

    /**
     * @name GeometryNode Interface
     */
    //@{
    /**
     * Draws this triangle mesh. The vertex and index array pointers must be
     * pointing to valid arrays when this member function is called.
     *
     * @param params Draw parameters.
     */
    virtual void draw(const DrawParams& params) const;
    //@}

private:
    /**
     * Invalidates the world extents.
     */
    void invalidateWorlExtents() const;

    /**
     * Updates and validates the world extents. This is called internally for
     * updating the world extents only when needed.
     */
    void updateWorldExtents() const;

    mutable bool worldExtentsValid_;    ///< Are world extents valid?
    mutable Extents3 worldExtents_;     ///< World extents.
    Extents3 modelExtents_;             ///< Model extents.
    Vector3Array* vertexArray_;         ///< Vertex array pointer.
    Vector3Array* normalArray_;         ///< Normal array pointer.
    ColorArray* colorArray_;            ///< Color array pointer.
    IndexArray* indexArray_;            ///< Index array pointer.

    // hide the copy assignment operator
    MeshNode& operator =(const MeshNode&);
};

#endif // #ifndef GRAPHICS_MESHNODE_H_INCLUDED
