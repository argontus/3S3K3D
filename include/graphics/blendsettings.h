/**
 * @file graphics/blendsettings.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_BLENDSETTINGS_H_INCLUDED
#define GRAPHICS_BLENDSETTINGS_H_INCLUDED

#include <graphics/color.h>

/**
 * Enumeration wrapper for possible blend equations.
 */
struct BlendEquation
{
    /**
     * Possible blend equations.
     */
    enum Enum
    {
        /**
         * <code>f = min(1, sf * src + df * dst)</code>.
         */
        Add,

        /**
         * <code>f = max(0, sf * src - df * dst)</code>.
         */
        Subtract,

        /**
         * <code>f = max(0, df * dst - sf * src)</code>.
         */
        ReverseSubtract,

        /**
         * <code>f = min(src, dst)</code>, blend factors are ignored.
         */
        Min,

        /**
         * <code>f = max(src, dst)</code>, blend factors are ignored.
         */
        Max
    };
};

/**
 * Enumeration wrapper for possible source blend factors.
 */
struct SrcBlendFactor
{
    /**
     * Possible source blend factors.
     */
    enum Enum
    {
        /**
         * <code>f.x = 0</code>.
         */
        Zero,

        /**
         * <code>f.x = 1</code>.
         */
        One,

        /**
         * <code>f.x = src.x</code>.
         */
        SrcColor,

        /**
         * <code>f.x = 1 - src.x</code>.
         */
        OneMinusSrcColor,

        /**
         * <code>f.x = dst.x</code>.
         */
        DstColor,

        /**
         * <code>f.x = 1 - dst.x</code>.
         */
        OneMinusDstColor,

        /**
         * <code>f.x = src.a</code>.
         */
        SrcAlpha,

        /**
         * <code>f.x = 1 - src.a</code>.
         */
        OneMinusSrcAlpha,

        /**
         * <code>f.x = dst.a</code>.
         */
        DstAlpha,

        /**
         * <code>f.x = 1 - dst.a</code>.
         */
        OneMinusDstAlpha,

        /**
         * <code>f.x = c.x</code>.
         */
        ConstantColor,

        /**
         * <code>f.x = 1 - c.x</code>.
         */
        OneMinusConstantColor,

        /**
         * <code>f.x = c.a</code>.
         */
        ConstantAlpha,

        /**
         * <code>f.x = 1 - c.a</code>.
         */
        OneMinusConstantAlpha,

        /**
         * <code>f.r = f.g = f.b = min(src.a, 1 - dst.a), f.a = 1</code>.
         */
        SrcAlphaSaturate
    };
};

/**
 * Enumeration wrapper for possible destination blend factors.
 */
struct DstBlendFactor
{
    /**
     * Possible destination blend factors.
     */
    enum Enum
    {
        /**
         * <code>f.x = 0</code>.
         */
        Zero,

        /**
         * <code>f.x = 1</code>.
         */
        One,

        /**
         * <code>f.x = src.x</code>.
         */
        SrcColor,

        /**
         * <code>f.x = 1 - src.x</code>.
         */
        OneMinusSrcColor,

        /**
         * <code>f.x = dst.x</code>.
         */
        DstColor,

        /**
         * <code>f.x = 1 - dst.x</code>.
         */
        OneMinusDstColor,

        /**
         * <code>f.x = src.a</code>.
         */
        SrcAlpha,

        /**
         * <code>f.x = 1 - src.a</code>.
         */
        OneMinusSrcAlpha,

        /**
         * <code>f.x = dst.a</code>.
         */
        DstAlpha,

        /**
         * <code>f.x = 1 - dst.a</code>.
         */
        OneMinusDstAlpha,

        /**
         * <code>f.x = c.x</code>.
         */
        ConstantColor,

        /**
         * <code>f.x = 1 - c.x</code>.
         */
        OneMinusConstantColor,

        /**
         * <code>f.x = c.a</code>.
         */
        ConstantAlpha,

        /**
         * <code>f.x = 1 - c.a</code>.
         */
        OneMinusConstantAlpha
    };
};

/**
 * Describes blend settings.
 */
struct BlendSettings
{
    // compiler-generated destructor, copy constructor and copy assignment
    // operator are fine

    /**
     * Default constructor.
     */
    BlendSettings();

    /**
     * Sets <code>colorEquation</code> and <code>alphaEquation</code> to
     * <code>equation</code>. Provided for convenience.
     *
     * @param equation Blend equation.
     */
    void setEquation(BlendEquation::Enum equation);

    /**
     * Sets <code>srcColorFactor</code> and <code>srcAlphaFactor</code> to
     * <code>factor</code>. Provided for convenience.
     *
     * @param factor Source blend factor.
     */
    void setSrcFactor(SrcBlendFactor::Enum factor);

    /**
     * Sets <code>dstColorFactor</code> and <code>dstAlphaFactor</code> to
     * <code>factor</code>. Provided for convenience.
     *
     * @param factor Destination blend factor.
     */
    void setDstFactor(DstBlendFactor::Enum factor);

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(BlendSettings& other);

    /**
     * Is blending enabled?
     */
    bool enabled;

    /**
     * Blend color.
     */
    Color blendColor;

    /**
     * Blend equation for RGB components.
     */
    BlendEquation::Enum colorEquation;

    /**
     * Blend equation for alpha component.
     */
    BlendEquation::Enum alphaEquation;

    /**
     * Blend factor for source RGB components.
     */
    SrcBlendFactor::Enum srcColorFactor;

    /**
     * Blend factor for source alpha component.
     */
    SrcBlendFactor::Enum srcAlphaFactor;

    /**
     * Blend factor for destination RGB components.
     */
    DstBlendFactor::Enum dstColorFactor;

    /**
     * Blend factor for destination alpha component.
     */
    DstBlendFactor::Enum dstAlphaFactor;
};

#endif // #ifndef GRAPHICS_BLENDSETTINGS_H_INCLUDED
