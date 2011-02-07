/**
 * @file graphics/predrawparams.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_PREDRAWPARAMS_H_INCLUDED
#define GRAPHICS_PREDRAWPARAMS_H_INCLUDED

#include <vector>

class GroupNode;
class RenderQueue;

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
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(PredrawParams& other);

    RenderQueue* renderQueue;   ///< Render queue.

    std::vector<const GroupNode*>* visibleGroups;

    // TODO: add visibility test
};

#endif // #ifndef GRAPHICS_PREDRAWPARAMS_H_INCLUDED
