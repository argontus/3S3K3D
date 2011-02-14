/**
 * @file graphics/meshnode.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/meshnode.h>

#include <geometry/matrix4x4.h>
#include <geometry/vector3array.h>

#include <graphics/drawparams.h>
#include <graphics/groupnode.h>
#include <graphics/mesh.h>
#include <graphics/opengl.h>
#include <graphics/runtimeassert.h>
#include <graphics/shaderprogram.h>

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
    modelExtents_ = mesh_->vertices().extents();
    invalidateWorlExtents();
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

void MeshNode::invalidateWorlTransform() const
{
    if (isWorldTransformValid() == false)
    {
        // TODO: make sure the world transforms and extents of all anchestor
        //       nodes are invalid

        // already invalidated, nothing to do
        return;
    }

    // call the base class version
    GeometryNode::invalidateWorlTransform();

    // transforming a geometry node invalidates its world extents and the world
    // extents of all anchestor nodes
    invalidateWorlExtents();
}

void MeshNode::draw(const DrawParams& params) const
{
    GRAPHICS_RUNTIME_ASSERT(mesh_ != 0);

    const Vector3Array& vertices = mesh_->vertices();
    const Vector3Array& normals = mesh_->normals();

    GRAPHICS_RUNTIME_ASSERT(vertices.size() == normals.size());

    //const Matrix4x4 mMatrix = modelToWorldMatrix();
    //const Matrix4x4 mvMatrix = product(mMatrix, params.viewMatrix);
    const Matrix4x4 mvMatrix(conversion(worldTransform(), params.cameraToWorld));
    const Matrix4x4 mvpMatrix = product(mvMatrix, params.projectionMatrix);
    const Matrix3x3 normalMatrix = product(worldTransform().rotation(), params.worldToViewRotation);

    // TODO: get rid of this
    // needed for lighting, quick & dirty
    const GLint viewMatrixLocation = params.shaderProgram->uniformLocation("view_matrix");
    glUniformMatrix4fv(viewMatrixLocation, 1, false, params.viewMatrix.data());

    // needed for lighting
    const GLint mvMatrixLocation = params.shaderProgram->uniformLocation("mv_matrix");
    glUniformMatrix4fv(mvMatrixLocation, 1, false, mvMatrix.data());

    // needed for transforming vertex coordinates
    const GLint mvpMatrixLocation = params.shaderProgram->uniformLocation("mvp_matrix");
    glUniformMatrix4fv(mvpMatrixLocation, 1, false, mvpMatrix.data());

    // needed for lighting
    const GLint normalMatrixLocation = params.shaderProgram->uniformLocation("normal_matrix");
    glUniformMatrix3fv(normalMatrixLocation, 1, false, normalMatrix.data());

    const GLint coordLocation = params.shaderProgram->attribLocation("coord");
    glVertexAttribPointer(coordLocation, 3, GL_FLOAT, false, 0, vertices.componentData());
    glEnableVertexAttribArray(coordLocation);

    // needed for lighting
    const GLint normalLocation = params.shaderProgram->attribLocation("normal");
    glVertexAttribPointer(normalLocation, 3, GL_FLOAT, false, 0, normals.componentData());
    glEnableVertexAttribArray(normalLocation);

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    glDisableVertexAttribArray(coordLocation);
    glDisableVertexAttribArray(normalLocation);
}

void MeshNode::invalidateWorlExtents() const
{
    worldExtentsValid_ = false;

    if (hasParent())
    {
        parent()->invalidateWorlExtents();
    }
}

void MeshNode::updateWorldExtents() const
{
    // make sure we are not doing any unnecessary function calls
    GRAPHICS_RUNTIME_ASSERT(worldExtentsValid_ == false);

    worldExtents_ = modelExtents_;
    worldExtents_.transformBy(worldTransform());

    worldExtentsValid_ = true;
}
