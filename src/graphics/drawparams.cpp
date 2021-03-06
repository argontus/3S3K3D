/**
 * @file graphics/drawparams.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/drawparams.h>

#include <algorithm>

DrawParams::DrawParams()
:   viewMatrix(Matrix4x4::identity()),
    projectionMatrix(Matrix4x4::identity()),
    worldToViewRotation(Matrix3x3::identity()),
    program(0),
    cameraToWorld()
{
    // ...
}

void DrawParams::swap(DrawParams& other)
{
    viewMatrix.swap(other.viewMatrix);
    projectionMatrix.swap(other.projectionMatrix);
    worldToViewRotation.swap(other.worldToViewRotation);
    std::swap(program, other.program);
    cameraToWorld.swap(other.cameraToWorld);
}
