/**
 * @file graphics/nodes/meshnode.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/nodes/meshnode.h>

#include <graphics/drawparams.h>
#include <graphics/mesh.h>
#include <graphics/renderer.h>
#include <graphics/runtimeassert.h>
#include <graphics/nodevisitors/nodevisitor.h>

MeshNode::~MeshNode()
{
    // ...
}

MeshNode::MeshNode()
:   Node(),
    mesh_(0),
    vertexBuffer_(0)
{
    // ...
}

void MeshNode::updateModelExtents()
{
    GRAPHICS_RUNTIME_ASSERT(mesh_ != 0);

    // construct empty extents
    Extents3 e;

    for (int i = 0; i < mesh_->numVertices(); ++i)
    {
        e.enclose(mesh_->vertex(i).position);
    }

    setModelExtents(e);
}

void MeshNode::setMesh(Mesh* const p)
{
    mesh_ = p;
}

Mesh* MeshNode::mesh() const
{
    return mesh_;
}

void MeshNode::setVertexBuffer(VertexBuffer* const vertexBuffer)
{
    vertexBuffer_ = vertexBuffer;
}

VertexBuffer* MeshNode::vertexBuffer() const
{
    return vertexBuffer_;
}

MeshNode* MeshNode::clone() const
{
    return new MeshNode(*this);
}

void MeshNode::draw(const DrawParams& params) const
{
    GRAPHICS_RUNTIME_ASSERT(vertexBuffer_ != 0);

    const Transform3 t = worldTransform();

    const Matrix4x4 modelMatrix = toMatrix4x4(t);
    const Matrix4x4 modelViewMatrix = modelMatrix * params.viewMatrix;
    const Matrix3x3 normalMatrix = t.rotation * params.viewRotation;

    params.renderer->setModelViewMatrix(modelViewMatrix);
    params.renderer->setNormalMatrix(normalMatrix);
    params.renderer->setVertexBuffer(vertexBuffer_);

    params.renderer->drawPrimitives(Renderer::PrimitiveType::Triangles);

    params.renderer->setVertexBuffer(0);
}

MeshNode::MeshNode(const MeshNode& other)
:   Node(other),
    mesh_(other.mesh_),
    vertexBuffer_(other.vertexBuffer_)
{
    // ...
}

bool MeshNode::acceptImpl(NodeVisitor* const visitor)
{
    return visitor->visit(this);
}
