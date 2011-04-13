/**
 * @file graphics/blendstate.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_BLENDSTATE_H_INCLUDED
#define GRAPHICS_BLENDSTATE_H_INCLUDED

#include <graphics/color.h>

/**
 * Describes a blending state.
 */
class BlendState
{
public:
    /**
     * Enumeration wrapper for possible blend equations.
     */
    struct Equation
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
    struct SrcFactor
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

            // TODO: this list is out of date for OpenGL 3.3
        };
    };

    /**
     * Enumeration wrapper for possible destination blend factors.
     */
    struct DstFactor
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

            // TODO: this list is out of date for OpenGL 3.3
        };
    };

    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

    /**
     * Default constructor.
     */
    BlendState();

    /**
     * Sets <code>colorEquation</code> and <code>alphaEquation</code> to
     * <code>equation</code>. Provided for convenience.
     *
     * @param equation Blend equation.
     */
    void setEquation(Equation::Enum equation);

    /**
     * Sets <code>srcColorFactor</code> and <code>srcAlphaFactor</code> to
     * <code>factor</code>. Provided for convenience.
     *
     * @param factor Source blend factor.
     */
    void setSrcFactor(SrcFactor::Enum factor);

    /**
     * Sets <code>dstColorFactor</code> and <code>dstAlphaFactor</code> to
     * <code>factor</code>. Provided for convenience.
     *
     * @param factor Destination blend factor.
     */
    void setDstFactor(DstFactor::Enum factor);

    /**
     * Blend equation for RGB components.
     */
    Equation::Enum colorEquation;

    /**
     * Blend equation for alpha component.
     */
    Equation::Enum alphaEquation;

    /**
     * Blend factor for source RGB components.
     */
    SrcFactor::Enum srcColorFactor;

    /**
     * Blend factor for source alpha component.
     */
    SrcFactor::Enum srcAlphaFactor;

    /**
     * Blend factor for destination RGB components.
     */
    DstFactor::Enum dstColorFactor;

    /**
     * Blend factor for destination alpha component.
     */
    DstFactor::Enum dstAlphaFactor;

    /**
     * Blend color.
     */
    Color blendColor;
};

#endif // #ifndef GRAPHICS_BLENDSTATE_H_INCLUDED
