/**
 * @file graphics/stencilstate.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_STENCILSTATE_H_INCLUDED
#define GRAPHICS_STENCILSTATE_H_INCLUDED

#include <graphics/opengl.h>

/**
 * Describes a stencil test state.
 */
class StencilState
{
public:
    /**
     * Enumeration wrapper for possible stencil test comparison functions.
     */
    struct CompareFunc
    {
        /**
         * Possible stencil test comparison functions.
         */
        enum Enum
        {
            /**
             * Always fails.
             */
            Never,

            /**
             * Passes if <code>(ref & mask) < (stencil & mask)</code>.
             */
            Less,

            /**
             * Passes if <code>(ref & mask) <= (stencil & mask)</code>.
             */
            LessEqual,

            /**
             * Passes if <code>(ref & mask) == (stencil & mask)</code>.
             */
            Equal,

            /**
             * Passes if <code>(ref & mask) > (stencil & mask)</code>.
             */
            Greater,

            /**
             * Passes if <code>(ref & mask) >= (stencil & mask)</code>.
             */
            GreaterEqual,

            /**
             * Passes if <code>(ref & mask) != (stencil & mask)</code>.
             */
            NotEqual,

            /**
             * Always passes.
             */
            Always
        };
    };

    /**
     * Enumeration wrapper for possible stencil test actions.
     */
    struct Action
    {
        /**
         * Possible stencil test actions.
         */
        enum Enum
        {
            /**
             * Keeps the current value.
             */
            Keep,

            /**
             * Sets the stencil buffer value to 0.
             */
            Zero,

            /**
             * Sets the stencil buffer value to the reference value.
             */
            Replace,

            /**
             * Increments the current stencil buffer value. Clamps to the
             * maximum representable unsigned value.
             */
            Increment,

            /**
             * Increments the current stencil buffer value. Wraps stencil
             * buffer value to zero when incrementing the maximum representable
             * unsigned value.
             */
            IncrementWrap,

            /**
             * Decrements the current stencil buffer value. Clamps to 0.
             */
            Decrement,

            /**
             * Decrements the current stencil buffer value. Wraps stencil
             * buffer value to the maximum representable unsigned value when
             * decrementing a stencil buffer value of zero.
             */
            DecrementWrap,

            /**
             * Bitwise inverts the current stencil buffer value.
             */
            Invert
        };
    };

    /**
     * Describes polygon face specific stencil test settings.
     */
    class FaceSettings
    {
    public:
        // compiler-generated destructor, copy constructor and assignment
        // operator are fine

        /**
         * Default constructor.
         */
        FaceSettings();

        /**
         * Comparison function.
         */
        CompareFunc::Enum compareFunc;

        /**
         * Reference value.
         */
        GLint reference;

        /**
         * Mask value.
         */
        GLuint mask;

        /**
         * Write mask value, controls writing of individual bits of stencil
         * buffer values.
         */
        GLuint writeMask;

        /**
         * Action to take when stencil test fails.
         */
        Action::Enum stencilFailAction;

        /**
         * Action to take when stencil test passes and depth test fails.
         */
        Action::Enum depthFailAction;

        /**
         * Action to take when both stencil and depth tests pass.
         */
        Action::Enum depthPassAction;
    };

    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

    /**
     * Default constructor.
     */
    StencilState();

    /**
     * Sets the comparison function for both back and front facing polygons.
     * Provided for convenience.
     *
     * @param compareFunc Comparison function.
     */
    void setCompareFunc(CompareFunc::Enum compareFunc);

    /**
     * Sets the reference value for both back and front facing polygons.
     * Provided for convenience.
     *
     * @param reference Reference value.
     */
    void setReference(GLint reference);

    /**
     * Sets the mask value for both back and front facing polygons. Provided
     * for convenience.
     *
     * @param mask Mask value.
     */
    void setMask(GLuint mask);

    /**
     * Sets the write mask value for both back and front facing polygons.
     * Provided for convenience.
     *
     * @param mask Mask value.
     */
    void setWriteMask(GLuint mask);

    /**
     * Sets the stencil test fail action for both back and front facing
     * polygons. Provided for convenience.
     *
     * @param action Action to take when stencil test fails.
     */
    void setStencilFailAction(Action::Enum action);

    /**
     * Sets the depth test fail action for both back and front facing polygons.
     * Provided for convenience.
     *
     * @param action Action to take when stencil test passes and depth test
     * fails.
     */
    void setDepthFailAction(Action::Enum action);

    /**
     * Sets the depth test pass action for both back and front facing polygons.
     * Provided for convenience.
     *
     * @param action Action to take when both stencil and depth tests pass.
     */
    void setDepthPassAction(Action::Enum action);

    /**
     * Settings for back facing polygons.
     */
    FaceSettings backFace;

    /**
     * Settings for front facing polygons.
     */
    FaceSettings frontFace;
};

#endif // #ifndef GRAPHICS_STENCILSTATE_H_INCLUDED
