/**
 * @file graphics/nodes/cameranode.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_NODES_CAMERANODE_H_INCLUDED
#define GRAPHICS_NODES_CAMERANODE_H_INCLUDED

#include <graphics/projectionsettings.h>
#include <graphics/nodes/node.h>

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
     * Gets the world to view transform matrix.
     *
     * @return World to view transform matrix.
     */
    const Matrix4x4 viewMatrix() const;

    /**
     * Gets the projection matrix.
     *
     * @return Projection matrix.
     */
    const Matrix4x4 projectionMatrix() const;

    /**
     * @name Node Interface
     */
    //@{
    virtual CameraNode* clone() const;
    virtual void draw(const DrawParams&) const;
    //@}

protected:
    /**
     * Copy constructor. This is used only for implementing the clone
     * functionality and is protected to prevent slicing.
     *
     * @param other The object to copy.
     */
    CameraNode(const CameraNode& other);

private:
    /**
     * @name Private Node Interface
     */
    //@{
    virtual bool acceptImpl(NodeVisitor*);
    //@}

    ProjectionSettings projectionSettings_; ///< Projection settings.

    // hide the copy assignment operator
    CameraNode& operator =(const CameraNode&);
};

#endif // #ifndef GRAPHICS_NODES_CAMERANODE_H_INCLUDED
