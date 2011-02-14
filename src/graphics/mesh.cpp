/**
 * @file graphics/mesh.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/mesh.h>

#include <graphics/runtimeassert.h>

Mesh::~Mesh()
{
    // ...
}

Mesh::Mesh(const int numFaces)
:   vertices_(numFaces * 3),
    normals_(numFaces * 3)
{
    // ...
}

Mesh::Mesh(const Mesh& other)
:   vertices_(other.vertices_),
    normals_(other.normals_)
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
    GRAPHICS_RUNTIME_ASSERT(vertices_.size() % 3 == 0);
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
        normals_[i * 3 + 0] =
        normals_[i * 3 + 1] =
        normals_[i * 3 + 2] = faceNormal(i);
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
