/**
 * @file graphics/nodes/meshnode.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/nodes/meshnode.h>

#include <graphics/device.h>
#include <graphics/drawparams.h>
#include <graphics/effect.h>
#include <graphics/mesh.h>
#include <graphics/pass.h>
#include <graphics/runtimeassert.h>
#include <graphics/technique.h>
#include <graphics/nodevisitors/nodevisitor.h>
#include <graphics/parameters/parameter.h>

MeshNode::~MeshNode()
{
    // TODO: the effect should be reference counted
    delete effect_;
}

MeshNode::MeshNode()
:   Node(),
    mesh_(0),
    vertexBuffer_(0),
    effect_(0)
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

void MeshNode::setEffect(Effect* const effect)
{
    // TODO: the effect should be reference counted
    GRAPHICS_RUNTIME_ASSERT(effect_ == 0);
    effect_ = effect;
}

Effect* MeshNode::effect()
{
    return effect_;
}

const Effect* MeshNode::effect() const
{
    return effect_;
}

MeshNode* MeshNode::clone() const
{
    return new MeshNode(*this);
}

MeshNode::MeshNode(const MeshNode& other)
:   Node(other),
    mesh_(other.mesh_),
    vertexBuffer_(other.vertexBuffer_),
    effect_(0)
{
    if (other.effect_ != 0)
    {
        // TODO: the effect should be reference counted
        effect_ = other.effect_->clone();
    }
}

bool MeshNode::acceptImpl(NodeVisitor* const visitor)
{
    return visitor->visit(this);
}
