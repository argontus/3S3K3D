/**
 * @file graphics/drawparams.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/drawparams.h>

DrawParams::DrawParams()
:   viewMatrix(Matrix4x4::identity()),
    projectionMatrix(Matrix4x4::identity()),
    worldToViewRotation(Matrix3x3::identity()),
    renderer(0),
    program(0),
    cameraToWorld()
{
    // ...
}
