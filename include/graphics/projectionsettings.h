/**
 * @file graphics/projectionsettings.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_PROJECTIONSETTINGS_H_INCLUDED
#define GRAPHICS_PROJECTIONSETTINGS_H_INCLUDED

class Matrix4x4;

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
 * Describes projection settings.
 */
class ProjectionSettings
{
public:
    /**
     * Gets projection settings describing an orthographic projection.
     *
     * @param left Coordinate for the left clipping plane.
     * @param right Coordinate for the right clipping plane.
     * @param bottom Coordinate for the bottom clipping plane.
     * @param top Coordinate for the top clipping plane.
     * @param near Distance to the near clipping plane.
     * @param far Distance to the far clipping plane.
     *
     * @return The created orthographic projection settings.
     */
    static const ProjectionSettings orthographic(
        float left,
        float right,
        float bottom,
        float top,
        float near,
        float far);

    // TODO: document valid parameter values
    /**
     * Gets projection settings describing a perspective projection.
     *
     * @param fovy Field of view along the y-axis in degrees.
     * @param aspectRatio Aspect ratio, that is width divided by height.
     * @param near Distance to the near clipping plane.
     * @param far Distance to the far clipping plane.
     *
     * @return The created perspective projection settings.
     */
    static const ProjectionSettings perspective(
        float fovy,
        float aspectRatio,
        float near,
        float far);

    // compiler-generated destructor, copy constructor and copy assignment
    // operator are fine

    /**
     * Default constructor.
     */
    ProjectionSettings();

    /**
     * Calculates the projection matrix for the current settings.
     *
     * @return The calculated projection matrix.
     */
    const Matrix4x4 projectionMatrix() const;

    ProjectionType::Enum type;  ///< Projection type.
    float left;                 ///< Coordinate for the left clipping plane.
    float right;                ///< Coordinate for the right clipping plane.
    float bottom;               ///< Coordinate for the bottom clipping plane.
    float top;                  ///< Coordinate for the top clipping plane.
    float near;                 ///< Distance to the near clipping plane.
    float far;                  ///< Distance to the far clipping plane.
};

#endif // #ifndef GRAPHICS_PROJECTIONSETTINGS_H_INCLUDED
