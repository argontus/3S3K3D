/**
 * @file graphics/color.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_COLOR_H_INCLUDED
#define GRAPHICS_COLOR_H_INCLUDED

#include <graphics/staticassert.h>

/**
 * Represents an RGBA color. The components are stored as normalized floating
 * point values.
 */
class Color
{
public:
    // compiler-generated destructor, copy constructor and copy assignment
    // operator are fine

    /**
     * Default constructor, constructs an uninitialized color.
     */
    Color();

    /**
     * Constructor.
     *
     * @param r The red component.
     * @param g The green component.
     * @param b The blue component.
     * @param a The alpha component.
     */
    Color(float r, float g, float b, float a);

    /**
     * Color addition.
     *
     * @param c The color to add to <code>*this</code>.
     *
     * @return Reference to <code>*this</code>.
     */
    Color& operator +=(const Color& c);

    /**
     * Color subtraction.
     *
     * @param c The color to subtract from <code>*this</code>.
     *
     * @return Reference to <code>*this</code>.
     */
    Color& operator -=(const Color& c);

    // TODO: not very intuitive, make this a named function?
    /**
     * Color modulation. Multiplies the components of <code>*this</code> by the
     * components of <code>c</code>.
     *
     * @param c The color by which this color is to be modulated.
     *
     * @return Reference to <code>*this</code>.
     */
    Color& operator *=(const Color& c);

    /**
     * Color-times-scalar multiplication.
     *
     * @param k The multiplier.
     *
     * @return Reference to <code>*this</code>.
     */
    Color& operator *=(float k);

    /**
     * Color-times-inverse scalar multiplication.
     *
     * @param k The divisor, cannot be zero.
     *
     * @return Reference to <code>*this</code>.
     */
    Color& operator /=(float k);

    /**
     * Array access operator.
     *
     * @param i Index of the component to return, between [0, 3].
     *
     * @return Reference to the specified component.
     */
    float& operator [](int i);

    /**
     * Provided for const-correctness.
     *
     * @see operator [](int)
     */
    float operator [](int i) const;

    /**
     * Gets the component array.
     *
     * @return The component array.
     */
    float* data();

    /**
     * Provided for const-correctness.
     *
     * @see data()
     */
    const float* data() const;

    /**
     * Clamps all components between [0, 1].
     */
    void clamp();

    /**
     * Negates this color.
     */
    void negate();

    /**
     * Sets all components.
     *
     * @param r The red component to set.
     * @param g The green component to set.
     * @param b The blue component to set.
     * @param a The alpha component to set.
     */
    void set(float r, float g, float b, float a);

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(Color& other);

    float r;    ///< The red component.
    float g;    ///< The green component.
    float b;    ///< The blue component.
    float a;    ///< The alpha component.
};

/// @cond
// verify packing assumptions
GRAPHICS_STATIC_ASSERT(sizeof(Color[2]) == sizeof(float) * 8);
/// @endcond

/**
 * Color addition.
 *
 * @param a The first color.
 * @param b The other color.
 *
 * @return <code>a + b</code>.
 */
const Color operator +(const Color& a, const Color& b);

/**
 * Color subtraction.
 *
 * @param a The first color.
 * @param b The other color.
 *
 * @return <code>a - b</code>.
 */
const Color operator -(const Color& a, const Color& b);

/**
 * Color negation.
 *
 * @param c The color to negate.
 *
 * @return Negated <code>c</code>.
 */
const Color operator -(const Color& c);

// TODO: not very intuitive, make this a named function?
/**
 * Color modulation. Multiplies the components of <code>a</code> by the
 * components of <code>b</code>.
 *
 * @param a The first color.
 * @param b The other color.
 *
 * @return The modulated color.
 */
const Color operator *(const Color& a, const Color& b);

/**
 * Scalar-times-color multiplication.
 *
 * @param k The multiplier.
 * @param c The color to multiply.
 *
 * @return <code>c</code> scaled by <code>k</code>.
 */
const Color operator *(float k, const Color& c);

/**
 * Color-times-scalar multiplication.
 *
 * @param c The color to multiply.
 * @param k The multiplier.
 *
 * @return <code>c</code> scaled by <code>k</code>.
 */
const Color operator *(const Color& c, float k);

/**
 * Color-times-inverse scalar multiplication.
 *
 * @param c The vector to multiply.
 * @param k The divisor, cannot be zero.
 *
 * @return <code>c</code> scaled by the inverse of <code>k</code>.
 */
const Color operator /(const Color& c, float k);

/**
 * Calculates a clamped color. Clamping a color means that its components are
 * clamped between [0, 1].
 *
 * @param c The color from which the result color is to be calculated.
 *
 * @return Clamped <code>c</code>.
 */
const Color clamp(const Color& c);

/**
 * Linear interpolation between two colors.
 *
 * @param a Begin color.
 * @param b End color.
 * @param t Weight coefficient.
 *
 * @return <code>a + t * (b - a)</code>.
 */
const Color mix(const Color& a, const Color& b, float t);

#endif // #ifndef GRAPHICS_COLOR_H_INCLUDED
