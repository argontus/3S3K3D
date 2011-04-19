/**
 * @file graphics/meshnode.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/meshnode.h>

#include <geometry/matrix4x4.h>

#include <graphics/drawparams.h>
#include <graphics/groupnode.h>
#include <graphics/mesh.h>
#include <graphics/opengl.h>
#include <graphics/program.h>
#include <graphics/runtimeassert.h>

MeshNode::~MeshNode()
{
    // ...
}

MeshNode::MeshNode()
:   GeometryNode(),
    diffuseMap(0),
    specularMap(0),
    glowMap(0),
    normalMap(0),
    worldExtentsValid_(false),
    worldExtents_(),
    modelExtents_(),
    mesh_(0)
{
    // ...
}

MeshNode::MeshNode(const MeshNode& other)
:   GeometryNode(other),
    diffuseMap(other.diffuseMap),
    specularMap(other.specularMap),
    glowMap(other.glowMap),
    normalMap(other.normalMap),
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

    const std::vector<Vector3>& vertices = mesh_->vertices();
    modelExtents_ = Extents3(vertices.begin(), vertices.end());
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

    const std::vector<Vector3>& coords = mesh_->vertices();
    const std::vector<Vector3>& normals = mesh_->normals();
    const std::vector<Vector3>& tangents = mesh_->tangents();
    const std::vector<Vector2>& texCoords = mesh_->texCoords();

    GRAPHICS_RUNTIME_ASSERT(coords.size() == normals.size());
    GRAPHICS_RUNTIME_ASSERT(coords.size() == tangents.size());
    GRAPHICS_RUNTIME_ASSERT(coords.size() == texCoords.size());

    // begin super hack
    const GLint _diffuseMapLocation = glGetUniformLocation(params.program->id(), "diffuseMap");
    const GLint _specularMapLocation = glGetUniformLocation(params.program->id(), "specularMap");
    const GLint _glowMapLocation = glGetUniformLocation(params.program->id(), "glowMap");
    const GLint _normalMapLocation = glGetUniformLocation(params.program->id(), "normalMap");

    int unit = 0;

    if (_diffuseMapLocation != -1)
    {
        glUniform1i(_diffuseMapLocation, unit);
        glActiveTexture(GL_TEXTURE0 + unit);
        glEnable(GL_TEXTURE_2D);
        diffuseMap->bindTexture();
        ++unit;
    }

    if (_specularMapLocation != -1)
    {
        glUniform1i(_specularMapLocation, unit);
        glActiveTexture(GL_TEXTURE0 + unit);
        glEnable(GL_TEXTURE_2D);
        specularMap->bindTexture();
        ++unit;
    }

    if (_glowMapLocation != -1)
    {
        glUniform1i(_glowMapLocation, unit);
        glActiveTexture(GL_TEXTURE0 + unit);
        glEnable(GL_TEXTURE_2D);
        glowMap->bindTexture();
        ++unit;
    }

    if (_normalMapLocation != -1)
    {
        glUniform1i(_normalMapLocation, unit);
        glActiveTexture(GL_TEXTURE0 + unit);
        glEnable(GL_TEXTURE_2D);
        normalMap->bindTexture();
        ++unit;
    }
    // end super hack

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

    const GLint coordLocation = glGetAttribLocation(params.program->id(), "coord");
    glVertexAttribPointer(coordLocation, 3, GL_FLOAT, false, 0, coords[0].data());
    glEnableVertexAttribArray(coordLocation);

    const GLint normalLocation = glGetAttribLocation(params.program->id(), "normal");
    glVertexAttribPointer(normalLocation, 3, GL_FLOAT, false, 0, normals[0].data());
    glEnableVertexAttribArray(normalLocation);

    const GLint tangentLocation = glGetAttribLocation(params.program->id(), "tangent");
    glVertexAttribPointer(tangentLocation, 3, GL_FLOAT, false, 0, tangents[0].data());
    glEnableVertexAttribArray(tangentLocation);

    const GLint texCoordLocation = glGetAttribLocation(params.program->id(), "texCoord");
    glVertexAttribPointer(texCoordLocation, 2, GL_FLOAT, false, 0, texCoords[0].data());
    glEnableVertexAttribArray(texCoordLocation);

    glDrawArrays(GL_TRIANGLES, 0, coords.size());

    glDisableVertexAttribArray(coordLocation);
    glDisableVertexAttribArray(normalLocation);
    glDisableVertexAttribArray(tangentLocation);
    glDisableVertexAttribArray(texCoordLocation);

//     begin super hack
//    glActiveTexture(GL_TEXTURE0);
//    glDisable(GL_TEXTURE_2D);
//    glActiveTexture(GL_TEXTURE1);
//    glDisable(GL_TEXTURE_2D);
//    glActiveTexture(GL_TEXTURE2);
//    glDisable(GL_TEXTURE_2D);
//    glActiveTexture(GL_TEXTURE3);
//    glDisable(GL_TEXTURE_2D);
//     end super hack
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
