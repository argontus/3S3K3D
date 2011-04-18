/**
 * @file graphics/nodes/cameranode.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/nodes/cameranode.h>

#include <geometry/matrix4x4.h>

#include <graphics/nodevisitors/nodevisitor.h>

CameraNode::~CameraNode()
{
    // ...
}

CameraNode::CameraNode()
:   Node(),
    projectionSettings_()
{
    // ...
}

void CameraNode::setProjectionSettings(const ProjectionSettings& settings)
{
    projectionSettings_ = settings;
}

const ProjectionSettings CameraNode::projectionSettings() const
{
    return projectionSettings_;
}

void CameraNode::setOrthographicProjection(
    const float left,
    const float right,
    const float bottom,
    const float top,
    const float near,
    const float far)
{
    projectionSettings_ = ProjectionSettings::orthographic(
        left,
        right,
        bottom,
        top,
        near,
        far
    );
}

void CameraNode::setPerspectiveProjection(
    const float fovy,
    const float aspectRatio,
    const float near,
    const float far)
{
    projectionSettings_ = ProjectionSettings::perspective(
        fovy,
        aspectRatio,
        near,
        far
    );
}

const Matrix4x4 CameraNode::viewMatrix() const
{
    // construct the world to view transform, reset scaling just in case
    Transform3 t = inverse(worldTransform());
    t.scaling = 1.0f;

    return toMatrix4x4(t);
}

const Matrix4x4 CameraNode::projectionMatrix() const
{
    return projectionSettings_.projectionMatrix();
}

CameraNode* CameraNode::clone() const
{
    return new CameraNode(*this);
}

void CameraNode::draw(const DrawParams&) const
{
    // ...
}

CameraNode::CameraNode(const CameraNode& other)
:   Node(other),
    projectionSettings_(other.projectionSettings_)
{
    // ...
}

bool CameraNode::acceptImpl(NodeVisitor* const visitor)
{
    return visitor->visit(this);
}
