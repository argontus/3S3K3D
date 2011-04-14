/**
 * @file graphics/drawparams.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_DRAWPARAMS_H_INCLUDED
#define GRAPHICS_DRAWPARAMS_H_INCLUDED

#include <geometry/matrix4x4.h>
#include <geometry/transform3.h>

class Program;
class Renderer;

/**
 * Describes draw parameters.
 */
class DrawParams
{
public:
    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

    /**
     * Default constructor.
     */
    DrawParams();

    // TODO: get rid of these
    Matrix4x4 viewMatrix;           ///< World to view transform matrix.
    Matrix4x4 projectionMatrix;     ///< Projection matrix.
    Matrix3x3 worldToViewRotation;  ///< World to view rotation matrix.

    Renderer* renderer;

    // TODO: quick & dirty
    Program* program;
    Transform3 cameraToWorld;
};

#endif // #ifndef GRAPHICS_DRAWPARAMS_H_INCLUDED
