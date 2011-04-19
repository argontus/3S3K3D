/**
 * @file graphics/visibilitytest.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_VISIBILITYTEST_H_INCLUDED
#define GRAPHICS_VISIBILITYTEST_H_INCLUDED

#include <geometry/plane3.h>

class Extents3;
class Transform3;

class CameraNode;
class ProjectionSettings;

/**
 * Enumeration wrapper for possible visibility states.
 */
struct VisibilityState
{
    /**
     * Possible visibility states.
     */
    enum Enum
    {
        CompletelyVisible,  ///< Completely visible.
        PartiallyVisible,   ///< Partially visible.
        Invisible           ///< Invisible.
    };
};

/**
 * Implements a plane culling visibility test.
 */
class VisibilityTest
{
public:
    // compiler-generated destructor, copy constructor and copy assignment
    // operator are fine

    /**
     * Default constructor, does not initialize the test parameters.
     */
    VisibilityTest();

    /**
     * Initializes the test parameters from the state of a given camera.
     *
     * @param camera The camera from whose state the visibility test parameters
     * are initialized.
     */
    void init(const CameraNode& camera);

    /**
     * Calculates the visibility state of given extents.
     *
     * @param extents The extents to test.
     *
     * @return The visibility state of <code>extents</code>.
     */
    VisibilityState::Enum test(const Extents3& extents) const;

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(VisibilityTest& other);

private:
    /**
     * Initializes the test parameters for an orthographic projection.
     *
     * @param camera The camera from whose state the visibility test parameters
     * are initialized.
     */
    void initOrthographic(const CameraNode& camera);

    /**
     * Initializes the test parameters for a perspective projection.
     *
     * @param camera The camera from whose state the visibility test parameters
     * are initialized.
     */
    void initPerspective(const CameraNode& camera);

    Plane3 planes_[6];  ///< Frustum planes.
};

#endif // #ifndef GRAPHICS_VISIBILITYTEST_H_INCLUDED
