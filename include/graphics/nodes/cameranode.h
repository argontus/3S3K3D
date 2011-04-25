/**
 * @file graphics/nodes/cameranode.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_NODES_CAMERANODE_H_INCLUDED
#define GRAPHICS_NODES_CAMERANODE_H_INCLUDED

#include <geometry/matrix4x4.h>

#include <graphics/nodes/node.h>

// TODO: implement a separate Camera class?
/**
 * Represents a camera node.
 */
class CameraNode : public Node
{
public:
    /**
     * Enumeration wrapper for possible projection types.
     */
    struct ProjectionType
    {
        /**
         * Possible projection types.
         */
        enum Enum
        {
            Orthographic,   ///< Orthographic projection.
            Perspective     ///< Perspective projection.
        };
    };

    /**
     * Destructor.
     */
    virtual ~CameraNode();

    /**
     * Default constructor.
     */
    CameraNode();

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

    /**
     * Sets a perspective projection.
     *
     * @param fovy Field of view along the y-axis in degrees, between (0, 180).
     * @param aspectRatio Aspect ratio, that is, width divided by height, must
     * be > 0.
     * @param near Distance to the near clipping plane, must be > 0.
     * @param far Distance to the far clipping plane, must be >
     * <code>near</code>.
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
     * Gets the projection type.
     *
     * @return Projection type.
     */
    ProjectionType::Enum projectionType() const;

    // TODO: use some helper class as the return value?
    /**
     * Gets the frustum parameters.
     *
     * @param left Pointer to the variable to which the coordinate for the left
     * clipping plane is stored, cannot be a null pointer.
     * @param right Pointer to the variable to which the coordinate for the
     * right clipping plane is stored, cannot be a null pointer.
     * @param bottom Pointer to the variable to which the coordinate for the
     * bottom clipping plane is stored, cannot be a null pointer.
     * @param top Pointer to the variable to which the coordinate for the top
     * clipping plane is stored, cannot be a null pointer.
     * @param near Pointer to the variable to which the distance to the near
     * clipping plane is stored, cannot be a null pointer.
     * @param far Pointer to the variable to which the distance to the far
     * clipping plane is stored, cannot be a null pointer.
     */
    void getFrustumParams(
        float* left,
        float* right,
        float* bottom,
        float* top,
        float* near,
        float* far) const;

    /**
     * @name Node Interface
     */
    //@{
    virtual CameraNode* clone() const;
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

    float left_;    ///< Coordinate for the left clipping plane.
    float right_;   ///< Coordinate for the right clipping plane.
    float bottom_;  ///< Coordinate for the bottom clipping plane.
    float top_;     ///< Coordinate for the top clipping plane.
    float near_;    ///< Distance to the near clipping plane.
    float far_;     ///< Distance to the far clipping plane.

    ProjectionType::Enum projectionType_;   ///< Projection type.
    Matrix4x4 projectionMatrix_;            ///< Projection matrix.

    // hide the copy assignment operator
    CameraNode& operator =(const CameraNode&);
};

#endif // #ifndef GRAPHICS_NODES_CAMERANODE_H_INCLUDED
