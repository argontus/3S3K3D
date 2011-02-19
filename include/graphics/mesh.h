/**
 * @file graphics/mesh.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_MESH_H_INCLUDED
#define GRAPHICS_MESH_H_INCLUDED

#include <geometry/vector2array.h>
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
     * Sets the vertices. The size of the given array must be a multiple of 3.
     * If vertex data is updated, the normal and texture coordinate data must
     * also be updated either by supplying the arrays or by generating them.
     *
     * @param vertices Vertex array to copy.
     *
     * @see setNormals(const Vector3Array&)
     * @see setTexCoords(const Vector2Array&)
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
     * Sets the vertex normals. The size of the given array must be a multiple
     * of 3 and should match the vertex array size.
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
     * Sets the vertex tangents. The size of the given array must be a multiple
     * of 3 and should match the vertex array size.
     *
     * @param tangents Vertex tangent array to copy.
     */
    void setTangents(const Vector3Array& tangents);

    /**
     * Gets the vertex tangents.
     *
     * @return Vertex tangents.
     */
    Vector3Array& tangents();

    /**
     * Provided for const-correctness.
     *
     * @see tangents()
     */
    const Vector3Array& tangents() const;

    /**
     * Sets the vertex texture coordinates. The size of the given array must be
     * a multiple of 3 and should match the vertex array size.
     *
     * @param texCoords Vertex texture coordinate array to copy.
     */
    void setTexCoords(const Vector2Array& texCoords);

    /**
     * Gets the vertex texture coordinates.
     *
     * @return Vertex texture coordinates.
     */
    Vector2Array& texCoords();

    /**
     * Provided for const-correctness.
     *
     * @see texCoords()
     */
    const Vector2Array& texCoords() const;

    /**
     * Gets the number of faces in this mesh.
     *
     * @return Number of faces in this mesh.
     */
    int numFaces() const;

    // TODO: generates tangents, update documentation
    /**
     * Generates the vertex normals from vertex data. The generated vertex
     * normals are calculated from face normals without interpolation. This
     * generation method produces flat surface lighting.
     */
    void generateFlatNormals();

    // TODO: is this needed?
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
    Vector3Array vertices_;     ///< Vertex coordinates.
    Vector3Array normals_;      ///< Vertex normals.
    Vector3Array tangents_;     ///< Vertex tangents for normal mapping.
    Vector2Array texCoords_;    ///< Vertex texture coordinates.
};

#endif // #ifndef GRAPHICS_MESH_H_INCLUDED
