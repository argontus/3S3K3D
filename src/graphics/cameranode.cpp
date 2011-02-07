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
    const Transform3 t = worldTransform();

    // TODO: the result could be initialized without matrix multiplications

    const Matrix4x4 translation = Matrix4x4::translation(-t.translation());
    const Matrix4x4 rotation = Matrix4x4(transpose(t.rotation()));

    // the order of application is negative translation first, inverse rotation
    // second
    return product(translation, rotation);
}

CameraNode* CameraNode::clone() const
{
    return new CameraNode(*this);
}

void CameraNode::predraw(const PredrawParams&) const
{
    // nothing to do
}

const Extents3 CameraNode::worldExtents() const
{
    // return empty extents
    return Extents3();
}
