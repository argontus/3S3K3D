/**
 * @file graphics/mesh.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/mesh.h>

#include <geometry/matrix3x3.h>

#include <graphics/runtimeassert.h>

Mesh::~Mesh()
{
    // ...
}

Mesh::Mesh(const int numFaces)
:   vertices_(numFaces * 3),
    normals_(numFaces * 3),
    tangents_(numFaces * 3),
    texCoords_(numFaces * 3)
{
    // ...
}

Mesh::Mesh(const Mesh& other)
:   vertices_(other.vertices_),
    normals_(other.normals_),
    tangents_(other.tangents_),
    texCoords_(other.texCoords_)
{
    // ...
}

Mesh& Mesh::operator =(const Mesh& other)
{
    Mesh(other).swap(*this);
    return *this;
}

void Mesh::setVertices(const Vector3Array& vertices)
{
    GRAPHICS_RUNTIME_ASSERT(vertices.size() % 3 == 0);
    vertices_ = vertices;
}

Vector3Array& Mesh::vertices()
{
    return vertices_;
}

const Vector3Array& Mesh::vertices() const
{
    return vertices_;
}

void Mesh::setNormals(const Vector3Array& normals)
{
    GRAPHICS_RUNTIME_ASSERT(normals.size() % 3 == 0);
    normals_ = normals;
}

Vector3Array& Mesh::normals()
{
    return normals_;
}

const Vector3Array& Mesh::normals() const
{
    return normals_;
}

void Mesh::setTangents(const Vector3Array& tangents)
{
    GRAPHICS_RUNTIME_ASSERT(tangents.size() % 3 == 0);
    tangents_ = tangents;
}

Vector3Array& Mesh::tangents()
{
    return tangents_;
}

const Vector3Array& Mesh::tangents() const
{
    return tangents_;
}

void Mesh::setTexCoords(const Vector2Array& texCoords)
{
    GRAPHICS_RUNTIME_ASSERT(texCoords.size() % 3 == 0);
    texCoords_ = texCoords;
}

Vector2Array& Mesh::texCoords()
{
    return texCoords_;
}

const Vector2Array& Mesh::texCoords() const
{
    return texCoords_;
}

int Mesh::numFaces() const
{
    GRAPHICS_RUNTIME_ASSERT(vertices_.size() % 3 == 0);
    return vertices_.size() / 3;
}

void Mesh::generateFlatNormals()
{
    if (vertices_.size() != normals_.size())
    {
        // resize the normal array
        // TODO: make resize(int) a member of Vector3Array?
        Vector3Array(vertices_.size()).swap(normals_);
    }

    GRAPHICS_RUNTIME_ASSERT(vertices_.size() == normals_.size());
    GRAPHICS_RUNTIME_ASSERT(vertices_.size() % 3 == 0);

    // for each face
    for (int i = 0; i < numFaces(); ++i)
    {
        const Vector3 v0 = vertices_[i * 3 + 0];
        const Vector3 v1 = vertices_[i * 3 + 1];

        // unnormalized tangent vector
        Vector3 t = v1 - v0;

        const float k = length(t);

        // avoid division by zero
        if (k > 0.0f)
        {
            // normalize the tangent vector
            t /= k;
        }
        else
        {
            // unable to normalize, use x-axis as the tangent vector
            t = Vector3::xAxis();
        }

        const Vector2 t0 = texCoords_[i * 3 + 0];
        const Vector2 t1 = texCoords_[i * 3 + 1];

        Vector2 t0t1 = t1 - t0;

        if (length(t0t1) == 0.0f)
        {
            t0t1 = Vector2::xAxis();
        }

        //const float vCoordAngle = 0.0f; // TODO: ...
        const float tCoordAngle = angle(t0t1);

        // normal
        const Vector3 n = faceNormal(i);

        // align tangent with the horizontal texture axis
        //t = product(t, Matrix3x3::rotation(n, tCoordAngle - vCoordAngle));
        t = product(t, Matrix3x3::rotation(n, -tCoordAngle));
        t.normalize();

        // binormal
        //const Vector3 b = cross(t, n);

        normals_[i * 3 + 0] =
        normals_[i * 3 + 1] =
        normals_[i * 3 + 2] = n;

        tangents_[i * 3 + 0] =
        tangents_[i * 3 + 1] =
        tangents_[i * 3 + 2] = t;
    }
}

void Mesh::generateSmoothNormals()
{
    // TODO: ...
}

void Mesh::swap(Mesh& other)
{
    vertices_.swap(other.vertices_);
    normals_.swap(other.normals_);
    tangents_.swap(other.tangents_);
    texCoords_.swap(other.texCoords_);
}

const Vector3 Mesh::faceNormal(const int index) const
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < vertices_.size());
    GRAPHICS_RUNTIME_ASSERT(vertices_.size() % 3 == 0);

    // face vertices, assume CCW winding
    const Vector3 v0 = vertices_[index * 3 + 0];
    const Vector3 v1 = vertices_[index * 3 + 1];
    const Vector3 v2 = vertices_[index * 3 + 2];

    // TODO: suffers from loss of precision, use 64-bit precision for
    // calculating the normal vector?
    const Vector3 n = cross(v1 - v0, v2 - v0);
    const float k = length(n);

    // avoid division by zero
    if (k > 0.0f)
    {
        // return normalized n
        return n / k;
    }
    else
    {
        // unable to normalize, return the x-axis
        return Vector3::xAxis();
    }
}
