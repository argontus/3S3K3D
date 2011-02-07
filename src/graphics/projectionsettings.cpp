/**
 * @file graphics/projectionsettings.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/projectionsettings.h>

#include <geometry/math.h>
#include <geometry/matrix4x4.h>

#include <graphics/runtimeassert.h>

const ProjectionSettings ProjectionSettings::orthographic(
    const float left,
    const float right,
    const float bottom,
    const float top,
    const float near,
    const float far)
{
    ProjectionSettings settings;
    settings.type = ProjectionType::Orthographic;
    settings.left = left;
    settings.right = right;
    settings.bottom = bottom;
    settings.top = top;
    settings.near = near;
    settings.far = far;

    return settings;
}

const ProjectionSettings ProjectionSettings::perspective(
    const float fovy,
    const float aspectRatio,
    const float near,
    const float far)
{
    GRAPHICS_RUNTIME_ASSERT(fovy > 0.0f && fovy < 180.0f);
    GRAPHICS_RUNTIME_ASSERT(aspectRatio > 0.0f);
    GRAPHICS_RUNTIME_ASSERT(near > 0.0f);
    GRAPHICS_RUNTIME_ASSERT(far > near);

    const float angle = Math::degToRad(fovy / 2.0f);

    // k / near = tan(angle) -> k = tan(angle) * near
    const float k = Math::tan(angle) * near;

    ProjectionSettings settings;
    settings.type = ProjectionType::Perspective;
    settings.left = -aspectRatio * k;
    settings.right = aspectRatio * k;
    settings.bottom = -k;
    settings.top = k;
    settings.near = near;
    settings.far = far;

    return settings;
}

ProjectionSettings::ProjectionSettings()
:   type(ProjectionType::Orthographic),
    left(-1.0f),
    right(1.0f),
    bottom(-1.0f),
    top(1.0f),
    near(-1.0f),
    far(1.0f)
{
    // ...
}

const Matrix4x4 ProjectionSettings::projectionMatrix() const
{
    if (type == ProjectionType::Orthographic)
    {
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

        return Matrix4x4(
              sx,  0.0f,  0.0f,  0.0f,
            0.0f,    sy,  0.0f,  0.0f,
            0.0f,  0.0f,    sz,  0.0f,
              tx,    ty,    tz,  1.0f
        );
    }
    else
    {
        // let the compiler take care of common sub-expressions

        const float sx = 2.0f * near / (right - left);
        const float sy = 2.0f * near / (top - bottom);

        const float a = (right + left) / (right - left);
        const float b = (top + bottom) / (top - bottom);
        const float c = -(far + near) / (far - near);
        const float d = -2.0f * far * near / (far - near);

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

        return Matrix4x4(
              sx,  0.0f,  0.0f,  0.0f,
            0.0f,    sy,  0.0f,  0.0f,
               a,     b,     c, -1.0f,
            0.0f,  0.0f,     d,  0.0f
        );
    }
}
