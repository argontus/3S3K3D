/**
 * @file graphics/stenciltestsettings.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_STENCILTESTSETTINGS_H_INCLUDED
#define GRAPHICS_STENCILTESTSETTINGS_H_INCLUDED

#include <stdint.h>

/**
 * Enumeration wrapper for possible stencil test comparison functions.
 */
struct StencilTestCompareFunc
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
         * Always passes.
         */
        Always,

        /**
         * Passes if <code>(ref & mask) < (stencil & mask)</code>.
         */
        Less,

        /**
         * Passes if <code>(ref & mask) <= (stencil & mask)</code>.
         */
        LessEqual,

        /**
         * Passes if <code>(ref & mask) > (stencil & mask)</code>.
         */
        Greater,

        /**
         * Passes if <code>(ref & mask) >= (stencil & mask)</code>.
         */
        GreaterEqual,

        /**
         * Passes if <code>(ref & mask) == (stencil & mask)</code>.
         */
        Equal,

        /**
         * Passes if <code>(ref & mask) != (stencil & mask)</code>.
         */
        NotEqual
    };
};

/**
 * Enumeration wrapper for possible stencil test actions.
 */
struct StencilTestAction
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
         * Increments the current stencil buffer value. Clamps to the maximum
         * representable unsigned value.
         */
        Increment,

        /**
         * Increments the current stencil buffer value. Wraps stencil buffer
         * value to zero when incrementing the maximum representable unsigned
         * value.
         */
        IncrementWrap,

        /**
         * Decrements the current stencil buffer value. Clamps to 0.
         */
        Decrement,

        /**
         * Decrements the current stencil buffer value. Wraps stencil buffer
         * value to the maximum representable unsigned value when decrementing
         * a stencil buffer value of zero.
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
class StencilTestFaceSettings
{
public:
    // compiler-generated destructor, copy constructor and copy assignment
    // operator are fine

    /**
     * Default constructor.
     */
    StencilTestFaceSettings();

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(StencilTestFaceSettings& other);

    /**
     * Comparison function.
     */
    StencilTestCompareFunc::Enum compareFunc;

    /**
     * Reference value.
     */
    int32_t reference;

    /**
     * Mask value.
     */
    uint32_t mask;

    /**
     * Action to take when stencil test fails.
     */
    StencilTestAction::Enum stencilFailAction;

    /**
     * Action to take when stencil test passes and depth test fails.
     */
    StencilTestAction::Enum depthFailAction;

    /**
     * Action to take when both stencil and depth tests pass.
     */
    StencilTestAction::Enum depthPassAction;
};

/**
 * Describes stencil test settings.
 */
class StencilTestSettings
{
public:
    // compiler-generated destructor, copy constructor and copy assignment
    // operator are fine

    /**
     * Default constructor.
     */
    StencilTestSettings();

    /**
     * Sets the comparison function for both back and front facing polygons.
     * Provided for convenience.
     *
     * @param compareFunc Comparison function.
     */
    void setCompareFunc(StencilTestCompareFunc::Enum compareFunc);

    /**
     * Sets the reference value for both back and front facing polygons.
     * Provided for convenience.
     *
     * @param reference Reference value.
     */
    void setReference(int32_t reference);

    /**
     * Sets the mask value for both back and front facing polygons. Provided
     * for convenience.
     *
     * @param mask Mask value.
     */
    void setMask(uint32_t mask);

    /**
     * Sets the stencil test fail action for both back and front facing
     * polygons. Provided for convenience.
     *
     * @param action Action to take when stencil test fails.
     */
    void setStencilFailAction(StencilTestAction::Enum action);

    /**
     * Sets the depth test fail action for both back and front facing polygons.
     * Provided for convenience.
     *
     * @param action Action to take when stencil test passes and depth test
     * fails.
     */
    void setDepthFailAction(StencilTestAction::Enum action);

    /**
     * Sets the depth test pass action for both back and front facing polygons.
     * Provided for convenience.
     *
     * @param action Action to take when both stencil and depth tests pass.
     */
    void setDepthPassAction(StencilTestAction::Enum action);

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(StencilTestSettings& other);

    /**
     * Is stenciling enabled?
     */
    bool enabled;

    /**
     * Settings for back facing polygons.
     */
    StencilTestFaceSettings backFaceSettings;

    /**
     * Settings for front facing polygons.
     */
    StencilTestFaceSettings frontFaceSettings;
};

#endif // #ifndef GRAPHICS_STENCILTESTSETTINGS_H_INCLUDED
