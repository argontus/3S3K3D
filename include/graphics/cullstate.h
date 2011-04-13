/**
 * @file graphics/cullstate.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_CULLSTATE_H_INCLUDED
#define GRAPHICS_CULLSTATE_H_INCLUDED

/**
 * Describes a cull state.
 */
class CullState
{
public:
    /**
     * Enumeration wrapper for possible cull faces.
     */
    struct CullFace
    {
        /**
         * Possible cull faces.
         */
        enum Enum
        {
            /**
             * Cull back facing polygons.
             */
            Back,

            /**
             * Cull front facing polygons.
             */
            Front
        };
    };

    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

    /**
     * Default constructor.
     */
    CullState();

    /**
     * Which polygon faces are culled?
     */
    CullFace::Enum cullFace;
};

#endif // #ifndef GRAPHICS_CULLSTATE_H_INCLUDED
