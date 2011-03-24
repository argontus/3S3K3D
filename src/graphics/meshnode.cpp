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

    const Vector3Array& coords = mesh_->vertices();
    const Vector3Array& normals = mesh_->normals();
    const Vector3Array& tangents = mesh_->tangents();
    const Vector2Array& texCoords = mesh_->texCoords();

    GRAPHICS_RUNTIME_ASSERT(coords.size() == normals.size());
    GRAPHICS_RUNTIME_ASSERT(coords.size() == tangents.size());
    GRAPHICS_RUNTIME_ASSERT(coords.size() == texCoords.size());

    const Matrix4x4 modelViewMatrix = conversion(worldTransform(), params.cameraToWorld).toMatrix4x4();
    const Matrix3x3 normalMatrix = worldTransform().rotation() * params.worldToViewRotation;

    params.shaderProgram->setUniformMatrix4x4fv(
        "modelViewMatrix",
        1,
        false,
        modelViewMatrix.data()
    );

    // TODO: can be loaded in the draw initialization step
    params.shaderProgram->setUniformMatrix4x4fv(
        "projectionMatrix",
        1,
        false,
        params.projectionMatrix.data()
    );

    params.shaderProgram->setUniformMatrix3x3fv(
        "normalMatrix",
        1,
        false,
        normalMatrix.data()
    );

    const GLint coordLocation = params.shaderProgram->attribLocation("coord");
    glVertexAttribPointer(coordLocation, 3, GL_FLOAT, false, 0, coords.componentData());
    glEnableVertexAttribArray(coordLocation);

    const GLint normalLocation = params.shaderProgram->attribLocation("normal");
    glVertexAttribPointer(normalLocation, 3, GL_FLOAT, false, 0, normals.componentData());
    glEnableVertexAttribArray(normalLocation);

    const GLint tangentLocation = params.shaderProgram->attribLocation("tangent");
    glVertexAttribPointer(tangentLocation, 3, GL_FLOAT, false, 0, tangents.componentData());
    glEnableVertexAttribArray(tangentLocation);

    const GLint texCoordLocation = params.shaderProgram->attribLocation("texCoord");
    glVertexAttribPointer(texCoordLocation, 2, GL_FLOAT, false, 0, texCoords.componentData());
    glEnableVertexAttribArray(texCoordLocation);

    glDrawArrays(GL_TRIANGLES, 0, coords.size());

    glDisableVertexAttribArray(coordLocation);
    glDisableVertexAttribArray(normalLocation);
    glDisableVertexAttribArray(tangentLocation);
    glDisableVertexAttribArray(texCoordLocation);
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

    // TODO: make sure this still works
    //worldExtents_ = modelExtents_;
    //worldExtents_.transformBy(worldTransform());
    worldExtents_ = ::transform(modelExtents_, worldTransform());

    worldExtentsValid_ = true;
}
