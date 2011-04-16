/**
 * @file graphics/depthstate.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_DEPTHSTATE_H_INCLUDED
#define GRAPHICS_DEPTHSTATE_H_INCLUDED

/**
 * Describes a depth buffer test state.
 */
class DepthState
{
public:
    /**
     * Enumeration wrapper for possible depth test comparison functions.
     */
    struct CompareFunc
    {
        /**
         * Possible depth test comparison functions.
         */
        enum Enum
        {
            /**
             * Never passes.
             */
            Never,

            /**
             * Passes if the incoming depth value is less than the stored depth
             * value.
             */
            Less,

            /**
             * Passes if the incoming depth value is less than or equal to the
             * stored depth value.
             */
            LessEqual,

            /**
             * Passes if the incoming depth value is equal to the stored depth
             * value.
             */
            Equal,

            /**
             * Passes if the incoming depth value is greater than the stored
             * depth value.
             */
            Greater,

            /**
             * Passes if the incoming depth value is greater than or equal to
             * the stored depth value.
             */
            GreaterEqual,

            /**
             * Passes if the incoming depth value is not equal to the stored
             * depth value.
             */
            NotEqual,

            /**
             * Always passes.
             */
            Always
        };
    };

    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

    /**
     * Default constructor.
     */
    DepthState();

    /**
     * Is depth buffer write enabled?
     */
    bool writeEnabled;

    /**
     * Comparison function for depth buffer comparisons.
     */
    CompareFunc::Enum compareFunc;
};

#endif // #ifndef GRAPHICS_DEPTHSTATE_H_INCLUDED
