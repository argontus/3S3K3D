/**
 * @file graphics/cameranode.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_CAMERANODE_H_INCLUDED
#define GRAPHICS_CAMERANODE_H_INCLUDED

#include <graphics/node.h>
#include <graphics/projectionsettings.h>

/**
 * Represents a camera node.
 */
class CameraNode : public Node
{
public:
    /**
     * Destructor.
     */
    virtual ~CameraNode();

    /**
     * Default constructor.
     */
    CameraNode();

    /**
     * Copy constructor.
     *
     * @param other The object to copy.
     */
    CameraNode(const CameraNode& other);

    /**
     * Sets the projection settings.
     *
     * @param settings Projection settings.
     */
    void setProjectionSettings(const ProjectionSettings& settings);

    /**
     * Gets the projection settings.
     *
     * @return Projection settings.
     */
    const ProjectionSettings projectionSettings() const;

    /**
     * Sets an orthographic projection.
     *
     * @param left Coordinate for the left clipping plane.
     * @param right Coordinate for the right clipping plane.
     * @param bottom Coordinate for the bottom clipping plane.
     * @param top Coordinate for the top clipping plane.
     * @param near Distance to the near clipping plane.
     * @param far Distance to the far clipping plane.
     */
    void setOrthographicProjection(
        float left,
        float right,
        float bottom,
        float top,
        float near,
        float far);

    // TODO: document valid parameter values
    /**
     * Sets a perspective projection.
     *
     * @param fovy Field of view along the y-axis in degrees.
     * @param aspectRatio Aspect ratio, that is width divided by height.
     * @param near Distance to the near clipping plane.
     * @param far Distance to the far clipping plane.
     */
    void setPerspectiveProjection(
        float fovy,
        float aspectRatio,
        float near,
        float far);

    /**
     * Calculates the world to view transform matrix.
     *
     * @return The calculated world to view transform matrix.
     */
    const Matrix4x4 viewMatrix() const;

    /**
     * Calculates the projection matrix for the current settings.
     *
     * @return The calculated projection matrix.
     */
    const Matrix4x4 projectionMatrix() const;

    /**
     * @name Node Interface
     */
    //@{
    virtual CameraNode* clone() const;
    virtual void predraw(const PredrawParams&, bool) const;
    virtual const Extents3 worldExtents() const;
    //@}

private:
    ProjectionSettings projectionSettings_; ///< Projection settings.

    // hide the copy assignment operator
    CameraNode& operator =(const CameraNode&);
};

#endif // #ifndef GRAPHICS_CAMERANODE_H_INCLUDED
