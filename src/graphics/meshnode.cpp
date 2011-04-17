/**
 * @file graphics/meshnode.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/meshnode.h>

#include <graphics/drawparams.h>
#include <graphics/groupnode.h>
#include <graphics/mesh.h>
#include <graphics/renderer.h>
#include <graphics/runtimeassert.h>

MeshNode::~MeshNode()
{
    // ...
}

MeshNode::MeshNode()
:   GeometryNode(),
    worldExtentsValid_(false),
    worldExtents_(),
    modelExtents_(),
    mesh_(0),
    vertexBuffer_(0)
{
    // ...
}

MeshNode::MeshNode(const MeshNode& other)
:   GeometryNode(other),
    worldExtentsValid_(false),
    worldExtents_(),
    modelExtents_(other.modelExtents_),
    mesh_(other.mesh_),
    vertexBuffer_(other.vertexBuffer_)
{
    // ...
}

void MeshNode::updateModelExtents()
{
    GRAPHICS_RUNTIME_ASSERT(mesh_ != 0);

    modelExtents_.clear();

    for (int i = 0; i < mesh_->numVertices(); ++i)
    {
        modelExtents_.enclose(mesh_->vertex(i).position);
    }

    invalidateWorldExtents();
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

const Extents3 MeshNode::worldExtents() const
{
    if (worldExtentsValid_ == false)
    {
        updateWorldExtents();

        // updateWorldExtents() should validate the world transform
        GRAPHICS_RUNTIME_ASSERT(worldExtentsValid_ == true);
    }

    return worldExtents_;
}

void MeshNode::invalidateWorldTransform() const
{
    if (isWorldTransformValid() == false)
    {
        // TODO: make sure the world transforms and extents of all anchestor
        //       nodes are invalid

        // already invalidated, nothing to do
        return;
    }

    // call the base class version
    GeometryNode::invalidateWorldTransform();

    // transforming a geometry node invalidates its world extents and the world
    // extents of all anchestor nodes
    invalidateWorldExtents();
}

void MeshNode::draw(const DrawParams& params) const
{
    GRAPHICS_RUNTIME_ASSERT(vertexBuffer_ != 0);

    const Matrix4x4 modelViewMatrix = toMatrix4x4(transformByInverse(worldTransform(), params.cameraToWorld));
    const Matrix3x3 normalMatrix = worldTransform().rotation * params.worldToViewRotation;

    params.renderer->setModelViewMatrix(modelViewMatrix);
    params.renderer->setNormalMatrix(normalMatrix);
    params.renderer->setVertexBuffer(vertexBuffer_);

    params.renderer->drawPrimitives(Renderer::PrimitiveType::Triangles);

    params.renderer->setVertexBuffer(0);
}

void MeshNode::invalidateWorldExtents() const
{
    worldExtentsValid_ = false;

    if (hasParent())
    {
        parent()->invalidateWorldExtents();
    }
}

void MeshNode::updateWorldExtents() const
{
    // make sure we are not doing any unnecessary function calls
    GRAPHICS_RUNTIME_ASSERT(worldExtentsValid_ == false);

    worldExtents_ = ::transform(modelExtents_, worldTransform());
    worldExtentsValid_ = true;
}
