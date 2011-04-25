/**
 * @file graphics/drawparams.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/drawparams.h>

DrawParams::DrawParams()
:   device(0),
    viewMatrix(Matrix4x4::identity()),
    projectionMatrix(Matrix4x4::identity()),
    viewRotation(Matrix3x3::identity())
{
    // ...
}
