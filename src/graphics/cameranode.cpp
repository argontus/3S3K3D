/**
 * @file graphics/cameranode.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/cameranode.h>

#include <geometry/extents3.h>
#include <geometry/matrix4x4.h>

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

CameraNode::CameraNode(const CameraNode& other)
:   Node(other),
    projectionSettings_(other.projectionSettings_)
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

const Matrix4x4 CameraNode::projectionMatrix() const
{
    return projectionSettings_.projectionMatrix();
}

const Matrix4x4 CameraNode::worldToViewMatrix() const
{
    // construct the world to view transform, reset scaling just in case
    Transform3 t = inverse(worldTransform());
    t.scaling = 1.0f;

    return toMatrix4x4(t);
}

CameraNode* CameraNode::clone() const
{
    return new CameraNode(*this);
}

void CameraNode::predraw(const PredrawParams&, const bool) const
{
    // nothing to do
}

const Extents3 CameraNode::worldExtents() const
{
    // return empty extents
    return Extents3();
}
