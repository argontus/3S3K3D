/**
 * @file graphics/mesh.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/mesh.h>

#include <geometry/matrix3x3.h>

#include <graphics/runtimeassert.h>

Mesh::~Mesh()
{
    delete [] vertices_;
}

Mesh::Mesh(const int numFaces)
:   vertices_(0),
    numFaces_(numFaces),
    numVertices_(3 * numFaces)
{
    GRAPHICS_RUNTIME_ASSERT(numFaces > 0);
    vertices_ = new Vertex[numVertices_];
}

Mesh::Vertex& Mesh::vertex(const int index)
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < numVertices_);
    return vertices_[index];
}

const Mesh::Vertex& Mesh::vertex(const int index) const
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < numVertices_);
    return vertices_[index];
}

Mesh::Vertex* Mesh::vertices()
{
    return vertices_;
}

const Mesh::Vertex* Mesh::vertices() const
{
    return vertices_;
}

int Mesh::numFaces() const
{
    return numFaces_;
}

int Mesh::numVertices() const
{
    return numVertices_;
}

void Mesh::generateNormalsAndTangents()
{
    // for each face
    for (int i = 0; i < numFaces_; ++i)
    {
        Vertex& v0 = vertices_[i * 3 + 0];
        Vertex& v1 = vertices_[i * 3 + 1];
        Vertex& v2 = vertices_[i * 3 + 2];

        const Vector3 dPosition = v1.position - v0.position;
        const Vector2 dTexCoord = v1.texCoord - v0.texCoord;

        // texture coordinate delta direction
        const float d = angle(dTexCoord);

        // unit length normal vector
        const Vector3 n = faceNormal(i);

        // unit length tangent vector aligned with the horizontal texture
        // coordinate axis
        const Vector3 t = normalize(dPosition * Matrix3x3::rotation(n, -d));

        v0.normal = v1.normal = v2.normal = n;
        v0.tangent = v1.tangent = v2.tangent = t;
    }
}

const Vector3 Mesh::faceNormal(const int index) const
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < numFaces_);

    // vertex positions for the specified face, assume CCW winding
    const Vector3 p0 = vertices_[index * 3 + 0].position;
    const Vector3 p1 = vertices_[index * 3 + 1].position;
    const Vector3 p2 = vertices_[index * 3 + 2].position;

    return normalize(cross(p1 - p0, p2 - p0));
}
