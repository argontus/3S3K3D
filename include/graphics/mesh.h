/**
 * @file graphics/mesh.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_MESH_H_INCLUDED
#define GRAPHICS_MESH_H_INCLUDED

#include <geometry/vector2.h>
#include <geometry/vector3.h>

/**
 * Represents a 3D triangle mesh. Assumes CCW vertex winding. Useful as a
 * helper class in generating vertex data for vertex buffers.
 */
class Mesh
{
public:
    /**
     * Describes a single vertex.
     */
    class Vertex
    {
    public:
        // compiler-generated destructor, default constructor, copy constructor
        // and assignment operator are fine

        Vector3 position;   ///< Vertex position.
        Vector3 normal;     ///< Vertex normal.
        Vector3 tangent;    ///< Vertex tangent.
        Vector2 texCoord;   ///< Vertex texture coordinate.
    };

    /**
     * Destructor.
     */
    ~Mesh();

    /**
     * Constructor.
     *
     * @param numFaces number of faces to allocate, must be > 0.
     */
    explicit Mesh(int numFaces);

    /**
     * Gets a specified vertex.
     *
     * @param index Index of the vertex to return, must be between [0,
     * <code>numVertices()</code>).
     */
    Vertex& vertex(int index);

    /**
     * Provided for const-correctness.
     *
     * @see vertex(int)
     */
    const Vertex& vertex(int index) const;

    /**
     * Gets a pointer to the stored vertices.
     *
     * @return Pointer to the stored vertices.
     */
    Vertex* vertices();

    /**
     * Provided for const-correctness.
     *
     * @see vertices()
     */
    const Vertex* vertices() const;

    /**
     * Gets the number of faces.
     *
     * @return Number of faces.
     */
    int numFaces() const;

    /**
     * Gets the number of vertices.
     *
     * @return Number of vertices.
     */
    int numVertices() const;

    /**
     * Generates the vertex normals and tangents from vertex data. The
     * generated vertex normals are calculated from face normals without
     * interpolation. This generation method produces flat surface lighting.
     * The tangents are generated from face normals and texture coordinates to
     * ensure that tangents are defined consistently. Inconsistently defined
     * tangents could lead to large lighting errors.
     */
    void generateNormalsAndTangents();

private:
    /**
     * Calculates the normal of a specified face. If the face normal cannot be
     * calculated due to invalid vertex data or floating point precision
     * errors, the return value is <code>Vector3(1.0f, 0.0f, 0.0f)</code>.
     *
     * @param index Index of the face whose normal is to be calculated, must be
     * between [0, <code>numFaces()</code>).
     *
     * @return The calculated face normal.
     */
    const Vector3 faceNormal(int index) const;

    Vertex* vertices_;  ///< Vertices.
    int numFaces_;      ///< Number of faces.
    int numVertices_;   ///< Number of vertices.

    // prevent copying
    Mesh(const Mesh&);
    Mesh& operator =(const Mesh&);
};

#endif // #ifndef GRAPHICS_MESH_H_INCLUDED
