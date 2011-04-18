/**
 * @file graphics/drawparams.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_DRAWPARAMS_H_INCLUDED
#define GRAPHICS_DRAWPARAMS_H_INCLUDED

#include <geometry/matrix3x3.h>
#include <geometry/matrix4x4.h>

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

    Renderer* renderer;         ///< The renderer to use for drawing.
    Matrix4x4 viewMatrix;       ///< World to view transform matrix.
    Matrix3x3 viewRotation;     ///< World to view rotation matrix.
};

#endif // #ifndef GRAPHICS_DRAWPARAMS_H_INCLUDED
