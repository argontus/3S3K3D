/**
 * @file graphics/color.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_COLOR_H_INCLUDED
#define GRAPHICS_COLOR_H_INCLUDED

#include <graphics/staticassert.h>

// TODO: rename this to Color4 and implement a Color3 class
/**
 * Represents an RGBA color. The components are stored as normalized floating
 * point values.
 */
class Color
{
public:
    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

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

    // the assignment operators are members to prevent implicit type
    // conversions of the left hand side object

    Color& operator +=(const Color& c);
    Color& operator -=(const Color& c);
    Color& operator *=(const Color& c);
    Color& operator *=(float k);
    Color& operator /=(float k);
    Color& operator /=(const Color& c);

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

const Color operator +(const Color& a, const Color& b);
const Color operator -(const Color& a, const Color& b);
const Color operator -(const Color& c);
const Color operator *(const Color& a, const Color& b);
const Color operator *(float k, const Color& c);
const Color operator *(const Color& c, float k);
const Color operator /(const Color& c, float k);
const Color operator /(const Color& a, const Color& b);

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
const Color clamp(const Color& c, float min, float max);

/**
 * Linear interpolation between two colors.
 *
 * @param a Color containing the values at <code>t == 0.0f</code>.
 * @param b Color containing the values at <code>t == 1.0f</code>.
 * @param t Weight coefficient.
 *
 * @return <code>a + t * (b - a)</code>.
 */
const Color mix(const Color& a, const Color& b, float t);

#endif // #ifndef GRAPHICS_COLOR_H_INCLUDED
