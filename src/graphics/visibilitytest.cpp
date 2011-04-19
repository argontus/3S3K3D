/**
 * @file graphics/visibilitytest.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/visibilitytest.h>

#include <geometry/interval.h>
#include <geometry/math.h>

#include <graphics/runtimeassert.h>
#include <graphics/nodes/cameranode.h>

VisibilityTest::VisibilityTest()
{
    // ...
}

void VisibilityTest::init(const CameraNode& camera)
{
    switch (camera.projectionType())
    {
        case CameraNode::ProjectionType::Orthographic:
            initOrthographic(camera);
            break;

        case CameraNode::ProjectionType::Perspective:
            initPerspective(camera);
            break;

        default:
            GRAPHICS_RUNTIME_ASSERT(false);
            break;
    }
}

VisibilityState::Enum VisibilityTest::test(const Extents3& extents) const
{
    VisibilityState::Enum state = VisibilityState::CompletelyVisible;

    // for each frustum plane
    for (int i = 0; i < 6; ++i)
    {
        //const Interval interval = extents.intervalAlong(planes_[i].normal);
        const Interval interval = ::interval(extents, planes_[i].normal);

        if (interval.max < planes_[i].constant)
        {
            // invisible, early out
            return VisibilityState::Invisible;
        }

        if (interval.min <= planes_[i].constant)
        {
            // partially visible
            state = VisibilityState::PartiallyVisible;
        }
    }

    return state;
}

void VisibilityTest::swap(VisibilityTest& other)
{
    planes_[0].swap(other.planes_[0]);
    planes_[1].swap(other.planes_[1]);
    planes_[2].swap(other.planes_[2]);
    planes_[3].swap(other.planes_[3]);
    planes_[4].swap(other.planes_[4]);
    planes_[5].swap(other.planes_[5]);
}

void VisibilityTest::initOrthographic(const CameraNode& camera)
{
    float left;
    float right;
    float bottom;
    float top;
    float near;
    float far;

    camera.getFrustumParams(
        &left,
        &right,
        &bottom,
        &top,
        &near,
        &far
    );

    const Transform3 t = camera.worldTransform();

    // camera position and rotation in world space
    const Vector3 position = t.translation;
    const Matrix3x3 rotation = t.rotation;

    // direction, right and up axes
    const Vector3 d = -rotation.row(2);
    const Vector3 r =  rotation.row(0);
    const Vector3 u =  rotation.row(1);

    const float xMin = Math::min(left, right);
    const float xMax = Math::max(left, right);
    const float yMin = Math::min(bottom, top);
    const float yMax = Math::max(bottom, top);
    const float zMin = Math::min(near, far);
    const float zMax = Math::max(near, far);

    // initialize from plane normal and a point on the plane
    planes_[0] = Plane3( d, position + zMin * d);   // near
    planes_[1] = Plane3(-d, position + zMax * d);   // far
    planes_[2] = Plane3( r, position + xMin * r);   // left
    planes_[3] = Plane3(-r, position + xMax * r);   // right
    planes_[4] = Plane3( u, position + yMin * u);   // bottom
    planes_[5] = Plane3(-u, position + yMax * u);   // top
}

void VisibilityTest::initPerspective(const CameraNode& camera)
{
    float left;
    float right;
    float bottom;
    float top;
    float near;
    float far;

    camera.getFrustumParams(
        &left,
        &right,
        &bottom,
        &top,
        &near,
        &far
    );

    GRAPHICS_RUNTIME_ASSERT(near > 0.0f);
    GRAPHICS_RUNTIME_ASSERT(near < far);

    const Transform3 t = camera.worldTransform();

    // camera position and rotation in world space
    const Vector3 position = t.translation;
    const Matrix3x3 rotation = t.rotation;

    // direction, right and up axes
    const Vector3 d = -rotation.row(2);
    const Vector3 r =  rotation.row(0);
    const Vector3 u =  rotation.row(1);

    const float xMin = Math::min(left, right);
    const float xMax = Math::max(left, right);
    const float yMin = Math::min(bottom, top);
    const float yMax = Math::max(bottom, top);

    const Vector3 center        = position + near * d;
    const Vector3 centerFar     = position + far * d;
    const Vector3 bottomLeft    = center + xMin * r + yMin * u;
    const Vector3 topLeft       = center + xMin * r + yMax * u;
    const Vector3 bottomRight   = center + xMax * r + yMin * u;
    const Vector3 topRight      = center + xMax * r + yMax * u;

    // initialize from plane normal and a point on the plane
    planes_[0] = Plane3( d, center);                        // near
    planes_[1] = Plane3(-d, centerFar);                     // far

    // initialize from three CCW points on the plane
    planes_[2] = Plane3(position, bottomLeft, topLeft);     // left
    planes_[3] = Plane3(position, topRight, bottomRight);   // right
    planes_[4] = Plane3(position, bottomRight, bottomLeft); // bottom
    planes_[5] = Plane3(position, topLeft, topRight);       // top
}
