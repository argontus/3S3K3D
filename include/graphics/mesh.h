/**
 * @file graphics/mesh.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_MESH_H_INCLUDED
#define GRAPHICS_MESH_H_INCLUDED

#include <geometry/vector3array.h>

/**
 * Represents a 3D triangle mesh.
 */
class Mesh
{
public:
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
     * Copy constructor.
     *
     * @param other The object to copy.
     */
    Mesh(const Mesh& other);

    /**
     * Copy assignment operator.
     *
     * @param other The object to assign to <code>*this</code>.
     *
     * @return Reference to <code>*this</code>.
     */
    Mesh& operator =(const Mesh& other);

    // TODO: this assumes CCW winding
    /**
     * Sets the vertices. The size of the given vertex array must be a multiple
     * of 3. If vertex data is updated, the normal data must also be updated
     * either by supplying the vertex normalsor by generating them.
     *
     * @param vertices Vertex array to copy.
     *
     * @see setNormals(const Vector3Array&) const
     * @see generateFlatNormals()
     * @see generateSmoothNormals()
     */
    void setVertices(const Vector3Array& vertices);

    /**
     * Gets the vertices.
     *
     * @return Vertices.
     */
    Vector3Array& vertices();

    /**
     * Provided for const-correctness.
     *
     * @see vertices()
     */
    const Vector3Array& vertices() const;

    /**
     * Sets the vertex normals. The size of the given vertex array must be a
     * multiple of 3 and should match the vertex array size.
     *
     * @param normals Vertex normal array to copy.
     */
    void setNormals(const Vector3Array& normals);

    /**
     * Gets the vertex normals.
     *
     * @return Vertex normals.
     */
    Vector3Array& normals();

    /**
     * Provided for const-correctness.
     *
     * @see normals()
     */
    const Vector3Array& normals() const;

    /**
     * Gets the number of faces in this mesh.
     *
     * @return Number of faces in this mesh.
     */
    int numFaces() const;

    /**
     * Generates the vertex normals from vertex data. The generated vertex
     * normals are calculated from face normals without interpolation. This
     * generation method produces flat surface lighting.
     */
    void generateFlatNormals();

    /**
     * Generates the vertex normals from vertex data. The generated vertex
     * normals are calculated by interpolating the normals of adjecent faces.
     * This generation method produces smooth surface lighting.
     */
    void generateSmoothNormals();

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(Mesh& other);

private:
    /**
     * Calculates the normal of a specified face. If the face normal cannot be
     * calculated due to invalid vertex data or floating point precision
     * errors, the return value is <code>Vector3(1.0f, 0.0f, 0.0f)</code>.
     *
     * @param index Index of the face whose normal is to be calculated.
     *
     * @return The calculated face normal.
     */
    const Vector3 faceNormal(int index) const;

    // TODO: VBOs
    // TODO: texture coordinates
    Vector3Array vertices_; ///< Vertices.
    Vector3Array normals_;  ///< Normals.
};

#endif // #ifndef GRAPHICS_MESH_H_INCLUDED
