/**
 * @file graphics/predrawparams.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_PREDRAWPARAMS_H_INCLUDED
#define GRAPHICS_PREDRAWPARAMS_H_INCLUDED

#include <vector>

class GroupNode;
class RenderQueue;
class VisibilityTest;

/**
 * Describes predraw parameters.
 */
class PredrawParams
{
public:
    // compiler-generated destructor, copy constructor and copy assignment
    // operator are fine

    /**
     * Default constructor.
     */
    PredrawParams();

    /**
     * Sets the render queue pointer.
     *
     * @param p Render queue pointer to set.
     */
    void setRenderQueue(RenderQueue* p);

    /**
     * Gets the render queue pointer.
     *
     * @return The render queue pointer.
     */
    RenderQueue* renderQueue() const;

    /**
     * Sets the visibility test pointer.
     *
     * @param p Visibility test pointer to set.
     */
    void setVisibilityTest(VisibilityTest* p);

    /**
     * Gets the visibility test pointer.
     *
     * @return The visibility test pointer.
     */
    VisibilityTest* visibilityTest() const;

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(PredrawParams& other);

private:
    RenderQueue* renderQueue_;          ///< Render queue.
    VisibilityTest* visibilityTest_;    ///< Visibility test.
};

#endif // #ifndef GRAPHICS_PREDRAWPARAMS_H_INCLUDED
