/**
 * @file graphics/meshnode.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/meshnode.h>

#include <GL/glew.h>

#include <geometry/matrix4x4.h>
#include <geometry/vector3array.h>

#include <graphics/colorarray.h>
#include <graphics/drawparams.h>
#include <graphics/groupnode.h>
#include <graphics/indexarray.h>
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
    vertexArray_(0),
    normalArray_(0),
    colorArray_(0),
    indexArray_(0)
{
    // ...
}

MeshNode::MeshNode(const MeshNode& other)
:   GeometryNode(other),
    worldExtentsValid_(false),
    worldExtents_(),
    modelExtents_(other.modelExtents_),
    vertexArray_(other.vertexArray_),
    normalArray_(other.normalArray_),
    colorArray_(other.colorArray_),
    indexArray_(other.indexArray_)
{
    // ...
}

void MeshNode::updateModelExtents()
{
    GRAPHICS_RUNTIME_ASSERT(vertexArray_ != 0);
    GRAPHICS_RUNTIME_ASSERT(indexArray_ != 0);
    GRAPHICS_RUNTIME_ASSERT(indexArray_->size() % 3 == 0);

    modelExtents_.clear();

    const Vector3* vertices = vertexArray_->data();
    const uint32_t* indices = indexArray_->data();

    for (int i = 0; i < indexArray_->size(); ++i)
    {
        const int index = indices[i];

        // make sure index is not out of bounds
        GRAPHICS_RUNTIME_ASSERT(index < vertexArray_->size());

        modelExtents_.growToContain(vertices[index]);
    }

    invalidateWorlExtents();
}

void MeshNode::setVertexArray(Vector3Array* const p)
{
    vertexArray_ = p;
}

Vector3Array* MeshNode::vertexArray() const
{
    return vertexArray_;
}

void MeshNode::setIndexArray(IndexArray* const p)
{
    indexArray_ = p;
}

IndexArray* MeshNode::indexArray() const
{
    return indexArray_;
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
    GRAPHICS_RUNTIME_ASSERT(vertexArray_ != 0);
    GRAPHICS_RUNTIME_ASSERT(indexArray_ != 0);
    GRAPHICS_RUNTIME_ASSERT(indexArray_->size() % 3 == 0);

    //const Matrix4x4 mMatrix = modelToWorldMatrix();
    //const Matrix4x4 mvMatrix = product(mMatrix, params.viewMatrix);
    const Matrix4x4 mvMatrix(conversion(worldTransform(), params.cameraToWorld));
    const Matrix4x4 mvpMatrix = product(mvMatrix, params.projectionMatrix);
    const Matrix3x3 normalMatrix = product(worldTransform().rotation(), params.worldToViewRotation);

    // needed for lighting, quick & dirty
    const GLint viewMatrixLocation = params.shaderProgram->uniformLocation("view_matrix");
    glUniformMatrix4fv(viewMatrixLocation, 1, false, params.viewMatrix.data());

    // needed for lighting
    const GLint mvMatrixLocation = params.shaderProgram->uniformLocation("mv_matrix");
    glUniformMatrix4fv(mvMatrixLocation, 1, false, mvMatrix.data());

    const GLint mvpMatrixLocation = params.shaderProgram->uniformLocation("mvp_matrix");
    glUniformMatrix4fv(mvpMatrixLocation, 1, false, mvpMatrix.data());

    // needed for lighting
    const GLint normalMatrixLocation = params.shaderProgram->uniformLocation("normal_matrix");
    glUniformMatrix3fv(normalMatrixLocation, 1, false, normalMatrix.data());

    const GLint coordLocation = params.shaderProgram->attribLocation("coord");
    glVertexAttribPointer(coordLocation, 3, GL_FLOAT, false, 0, vertexArray_->componentData());
    glEnableVertexAttribArray(coordLocation);

    // needed for lighting
    const GLint normalLocation = params.shaderProgram->attribLocation("normal");
    glVertexAttribPointer(normalLocation, 3, GL_FLOAT, false, 0, normalArray_->componentData());
    glEnableVertexAttribArray(normalLocation);

    const GLint colorLocation = params.shaderProgram->attribLocation("color");
    glVertexAttribPointer(colorLocation, 4, GL_FLOAT, false, 0, colorArray_->componentData());
    glEnableVertexAttribArray(colorLocation);

    glDrawElements(
        GL_TRIANGLES,
        indexArray_->size(),
        GL_UNSIGNED_INT,
        indexArray_->data()
    );

    glDisableVertexAttribArray(coordLocation);
    glDisableVertexAttribArray(normalLocation);
    glDisableVertexAttribArray(colorLocation);
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
