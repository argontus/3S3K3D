/**
 * @file graphics/viewport.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_VIEWPORT_H_INCLUDED
#define GRAPHICS_VIEWPORT_H_INCLUDED

#include <graphics/color.h>
#include <graphics/rectanglef.h>

class Camera;
class Node;

/**
 * Describes a viewport.
 */
class Viewport
{
public:
    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

    /**
     * Default constructor.
     */
    Viewport();

    /**
     * Sets the viewport area in normalized device coordinates. Out-of-range
     * coordinates are automatically clamped between [0, 1].
     *
     * @param area Viewport area to set.
     */
    void setArea(const RectangleF& area);

    /**
     * Gets the viewport area in normalized device coordinates.
     *
     * @return Viewport area in normalized device coordinates.
     */
    const RectangleF area() const;

    /**
     * Sets the clear color.
     *
     * @param color Clear color to set, the components are automatically
     * clamped between [0, 1].
     */
    void setClearColor(const Color& color);

    /**
     * Gets the clear color.
     *
     * @return Clear color.
     */
    const Color clearColor() const;

    /**
     * Enables or disables automatic clearing of this viewport. If automatic
     * clearing is enabled, the contents of this viewport will be filled with
     * the clear color before rendering any visible geometry.
     *
     * @param enabled Enable automatic clearing?
     */
    void setClearEnabled(bool enabled);

    /**
     * Gets a boolean value indicating whether or not this viewport is cleared
     * before rendering.
     *
     * @return <code>true</code>, if this viewport is cleared before rendering,
     * <code>false</code> otherwise.
     */
    bool isClearEnabled() const;

    /**
     * Sets the draw order index for depth sorting. Viewports are rendered in
     * ascending order determined by their draw order indices.
     *
     * @param zIndex Draw order index to set.
     */
    void setZIndex(int zIndex);

    /**
     * Gets the viewport draw order index.
     *
     * @return Draw order index.
     */
    int zIndex() const;

    /**
     * Sets the active camera.
     *
     * @param camera The camera to set.
     */
    void setCamera(Camera* camera);

    /**
     * Gets the active camera.
     *
     * @return The active camera.
     */
    Camera* camera() const;

    /**
     * Sets the active root node.
     *
     * @param rootNode The root node to set.
     */
    void setRootNode(Node* rootNode);

    /**
     * Gets the active root node.
     *
     * @return The active root node.
     */
    Node* rootNode() const;

private:
    RectangleF area_;   ///< Viewport area in normalized device coordinates.
    Color clearColor_;  ///< Clear color.
    bool clearEnabled_; ///< Clear viewport before rendering?
    int zIndex_;        ///< Draw order index for depth sorting.
    Camera* camera_;    ///< Active camera.
    Node* rootNode_;    ///< Active root node.
};

#endif // #ifndef GRAPHICS_VIEWPORT_H_INCLUDED
