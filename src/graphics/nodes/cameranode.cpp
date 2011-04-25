/**
 * @file graphics/nodes/cameranode.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/nodes/cameranode.h>

#include <geometry/math.h>

#include <graphics/runtimeassert.h>
#include <graphics/nodevisitors/nodevisitor.h>

CameraNode::~CameraNode()
{
    // ...
}

CameraNode::CameraNode()
:   Node()
{
    setOrthographicProjection(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
}

void CameraNode::setOrthographicProjection(
    const float left,
    const float right,
    const float bottom,
    const float top,
    const float near,
    const float far)
{
    left_ = left;
    right_ = right;
    bottom_ = bottom;
    top_ = top;
    near_ = near;
    far_ = far;
    projectionType_ = ProjectionType::Orthographic;

    // let the compiler take care of common sub-expressions

    const float sx = 2.0f / (right - left);
    const float sy = 2.0f / (top - bottom);
    const float sz = -2.0f / (far - near);

    const float tx = -(right + left) / (right - left);
    const float ty = -(top + bottom) / (top - bottom);
    const float tz = -(far + near) / (far - near);

    // After a vector has been multiplied by the projection matrix, the
    // resulting components are:
    //
    // x' = sx * x + tx
    // y' = sy * y + ty
    // z' = sz * z + tz
    // w' = w
    //
    // If the w component was 1, there is no need to divide the components
    // by the w component. After all components have been divided by the w
    // component, the resulting components are:
    //
    // x' = (sx * x + tx) / w
    // y' = (sy * y + ty) / w
    // z' = (sz * z + tz) / w
    // w' = w / w = 1

    projectionMatrix_ = Matrix4x4(
          sx,  0.0f,  0.0f,  0.0f,
        0.0f,    sy,  0.0f,  0.0f,
        0.0f,  0.0f,    sz,  0.0f,
          tx,    ty,    tz,  1.0f
    );
}

void CameraNode::setPerspectiveProjection(
    const float fovy,
    const float aspectRatio,
    const float near,
    const float far)
{
    GRAPHICS_RUNTIME_ASSERT(fovy > 0.0f && fovy < 180.0f);
    GRAPHICS_RUNTIME_ASSERT(aspectRatio > 0.0f);
    GRAPHICS_RUNTIME_ASSERT(near > 0.0f);
    GRAPHICS_RUNTIME_ASSERT(near < far);

    const float angle = Math::radians(fovy / 2.0f);

    // k / near = tan(angle) -> k = tan(angle) * near
    const float k = Math::tan(angle) * near;

    left_ = -aspectRatio * k;
    right_ = aspectRatio * k;
    bottom_ = -k;
    top_ = k;
    near_ = near;
    far_ = far;
    projectionType_ = ProjectionType::Perspective;

    // let the compiler take care of common sub-expressions

    const float sx = 2.0f * near_ / (right_ - left_);
    const float sy = 2.0f * near_ / (top_ - bottom_);

    const float a = (right_ + left_) / (right_ - left_);
    const float b = (top_ + bottom_) / (top_ - bottom_);
    const float c = -(far_ + near_) / (far_ - near_);
    const float d = -2.0f * far_ * near_ / (far_ - near_);

    // After a vector has been multiplied by the projection matrix, the
    // resulting components are:
    //
    // x' = sx * x + a * z
    // y' = sy * y + b * z
    // z' = c * z + d
    // w' = -z
    //
    // After all components have been divided by the w component, the
    // resulting components are:
    //
    // x' = (sx * x + a * z) / -z = -sx * x / z - a
    // y' = (sy * y + b * z) / -z = -sy * y / z - b
    // z' = (c * z + d) / -z = -d / z - c
    // w' = -z / -z = 1

    projectionMatrix_ = Matrix4x4(
          sx,  0.0f,  0.0f,  0.0f,
        0.0f,    sy,  0.0f,  0.0f,
           a,     b,     c, -1.0f,
        0.0f,  0.0f,     d,  0.0f
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
    return projectionMatrix_;
}

CameraNode::ProjectionType::Enum CameraNode::projectionType() const
{
    return projectionType_;
}

void CameraNode::getFrustumParams(
    float* const left,
    float* const right,
    float* const bottom,
    float* const top,
    float* const near,
    float* const far) const
{
    GRAPHICS_RUNTIME_ASSERT(left != 0);
    GRAPHICS_RUNTIME_ASSERT(right != 0);
    GRAPHICS_RUNTIME_ASSERT(bottom != 0);
    GRAPHICS_RUNTIME_ASSERT(top != 0);
    GRAPHICS_RUNTIME_ASSERT(near != 0);
    GRAPHICS_RUNTIME_ASSERT(far != 0);

    *left = left_;
    *right = right_;
    *bottom = bottom_;
    *top = top_;
    *near = near_;
    *far = far_;
}

CameraNode* CameraNode::clone() const
{
    return new CameraNode(*this);
}

CameraNode::CameraNode(const CameraNode& other)
:   Node(other),
    left_(other.left_),
    right_(other.right_),
    bottom_(other.bottom_),
    top_(other.top_),
    near_(other.near_),
    far_(other.far_),
    projectionType_(other.projectionType_),
    projectionMatrix_(other.projectionMatrix_)
{
    // ...
}

bool CameraNode::acceptImpl(NodeVisitor* const visitor)
{
    return visitor->visit(this);
}
