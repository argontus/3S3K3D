/**
 * @file graphics/color4.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_COLOR4_H_INCLUDED
#define GRAPHICS_COLOR4_H_INCLUDED

#include <graphics/staticassert.h>

/**
 * Represents an RGBA color. The components are stored as normalized floating
 * point values.
 */
class Color4
{
public:
    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

    /**
     * Default constructor, constructs an uninitialized color.
     */
    Color4();

    /**
     * Constructor.
     *
     * @param r The red component.
     * @param g The green component.
     * @param b The blue component.
     * @param a The alpha component.
     */
    Color4(float r, float g, float b, float a);

    // the assignment operators are members to prevent implicit type
    // conversions of the left hand side object

    Color4& operator +=(const Color4& c);
    Color4& operator -=(const Color4& c);
    Color4& operator *=(const Color4& c);
    Color4& operator *=(float k);
    Color4& operator /=(float k);
    Color4& operator /=(const Color4& c);

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
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(Color4& other);

    float r;    ///< The red component.
    float g;    ///< The green component.
    float b;    ///< The blue component.
    float a;    ///< The alpha component.
};

/// @cond
// verify packing assumptions
GRAPHICS_STATIC_ASSERT(sizeof(Color4[2]) == sizeof(float) * 8);
/// @endcond

const Color4 operator +(const Color4& a, const Color4& b);
const Color4 operator -(const Color4& a, const Color4& b);
const Color4 operator -(const Color4& c);
const Color4 operator *(const Color4& a, const Color4& b);
const Color4 operator *(float k, const Color4& c);
const Color4 operator *(const Color4& c, float k);
const Color4 operator /(const Color4& c, float k);
const Color4 operator /(const Color4& a, const Color4& b);

/**
 * Clamps the components of <code>c</code> between [<code>min</code>,
 * <code>max</code>].
 *
 * @param c The color to clamp.
 * @param min Minimum value.
 * @param max Maximum value.
 *
 * @return Clamped <code>c</code>.
 */
const Color4 clamp(const Color4& c, float min, float max);

/**
 * Linear interpolation between two colors.
 *
 * @param a Color containing the values at <code>t == 0.0f</code>.
 * @param b Color containing the values at <code>t == 1.0f</code>.
 * @param t Weight coefficient.
 *
 * @return <code>a + t * (b - a)</code>.
 */
const Color4 mix(const Color4& a, const Color4& b, float t);

#endif // #ifndef GRAPHICS_COLOR4_H_INCLUDED
