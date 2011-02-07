/**
 * @file graphics/drawparams.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_DRAWPARAMS_H_INCLUDED
#define GRAPHICS_DRAWPARAMS_H_INCLUDED

#include <geometry/matrix4x4.h>
#include <geometry/transform3.h>

class ShaderProgram;

/**
 * Describes draw parameters.
 */
class DrawParams
{
public:
    // compiler-generated destructor, copy constructor and copy assignment
    // operator are fine

    /**
     * Default constructor.
     */
    DrawParams();

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(DrawParams& other);

    Matrix4x4 viewMatrix;           ///< World to view transform matrix.
    Matrix4x4 projectionMatrix;     ///< Projection matrix.
    Matrix3x3 worldToViewRotation;  ///< World to view rotation matrix.

    // TODO: quick & dirty
    ShaderProgram* shaderProgram;
    Transform3 cameraToWorld;
};

#endif // #ifndef GRAPHICS_DRAWPARAMS_H_INCLUDED
