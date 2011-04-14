/**
 * @file graphics/meshnode.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/meshnode.h>

#include <geometry/matrix4x4.h>

#include <graphics/drawparams.h>
#include <graphics/groupnode.h>
#include <graphics/mesh.h>
#include <graphics/program.h>
#include <graphics/runtimeassert.h>
#include <graphics/vertexbuffer.h>

MeshNode::~MeshNode()
{
    // ...
}

MeshNode::MeshNode()
:   GeometryNode(),
    worldExtentsValid_(false),
    worldExtents_(),
    modelExtents_(),
    mesh_(0)
{
    // ...
}

MeshNode::MeshNode(const MeshNode& other)
:   GeometryNode(other),
    worldExtentsValid_(false),
    worldExtents_(),
    modelExtents_(other.modelExtents_),
    mesh_(other.mesh_)
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
    GRAPHICS_RUNTIME_ASSERT(mesh_ != 0);

    // TODO: this whole function should be 3 lines of code and the 3rd line
    // could be omitted as an optimization
    //
    // params.renderer->setVertexBuffer(vertexBuffer_);
    // params.renderer->renderPrimitives(Renderer::PrimitiveType::Triangles);
    // params.renderer->setVertexBuffer(0);

    const int vertexStride = sizeof(Mesh::Vertex);

    VertexBuffer vertexBuffer(
        mesh_->numVertices(),
        vertexStride,
        mesh_->vertices(),
        VertexBuffer::Usage::Static
    );

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer.id());

    const Matrix4x4 modelViewMatrix = toMatrix4x4(transformByInverse(worldTransform(), params.cameraToWorld));
    const Matrix3x3 normalMatrix = worldTransform().rotation * params.worldToViewRotation;

    glUniformMatrix4fv(
        glGetUniformLocation(params.program->id(), "modelViewMatrix"),
        1,
        false,
        modelViewMatrix.data()
    );

    // TODO: can be loaded in the draw initialization step
    glUniformMatrix4fv(
        glGetUniformLocation(params.program->id(), "projectionMatrix"),
        1,
        false,
        params.projectionMatrix.data()
    );

    glUniformMatrix3fv(
        glGetUniformLocation(params.program->id(), "normalMatrix"),
        1,
        false,
        normalMatrix.data()
    );

    const GLint positionLocation    = glGetAttribLocation(params.program->id(), "position");
    const GLint normalLocation      = glGetAttribLocation(params.program->id(), "normal");
    const GLint tangentLocation     = glGetAttribLocation(params.program->id(), "tangent");
    const GLint texCoordLocation    = glGetAttribLocation(params.program->id(), "texCoord");

    const GLvoid* positionOffset    = 0;
    const GLvoid* normalOffset      = reinterpret_cast<GLvoid*>(1 * sizeof(Vector3));
    const GLvoid* tangentOffset     = reinterpret_cast<GLvoid*>(2 * sizeof(Vector3));
    const GLvoid* texCoordOffset    = reinterpret_cast<GLvoid*>(3 * sizeof(Vector3));

    glEnableVertexAttribArray(positionLocation);
    glEnableVertexAttribArray(normalLocation);
    glEnableVertexAttribArray(tangentLocation);
    glEnableVertexAttribArray(texCoordLocation);

    glVertexAttribPointer(positionLocation, 3, GL_FLOAT, false, vertexStride, positionOffset);
    glVertexAttribPointer(normalLocation, 3, GL_FLOAT, false, vertexStride, normalOffset);
    glVertexAttribPointer(tangentLocation, 3, GL_FLOAT, false, vertexStride, tangentOffset);
    glVertexAttribPointer(texCoordLocation, 2, GL_FLOAT, false, vertexStride, texCoordOffset);

    glDrawArrays(GL_TRIANGLES, 0, mesh_->numVertices());

    glDisableVertexAttribArray(positionLocation);
    glDisableVertexAttribArray(normalLocation);
    glDisableVertexAttribArray(tangentLocation);
    glDisableVertexAttribArray(texCoordLocation);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
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
