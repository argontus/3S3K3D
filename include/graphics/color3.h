/**
 * @file graphics/color3.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_COLOR3_H_INCLUDED
#define GRAPHICS_COLOR3_H_INCLUDED

#include <graphics/staticassert.h>

/**
 * Represents an RGB color. The components are stored as normalized floating
 * point values.
 */
class Color3
{
public:
    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

    /**
     * Default constructor, constructs an uninitialized color.
     */
    Color3();

    /**
     * Constructor.
     *
     * @param r The red component.
     * @param g The green component.
     * @param b The blue component.
     */
    Color3(float r, float g, float b);

    // the assignment operators are members to prevent implicit type
    // conversions of the left hand side object

    Color3& operator +=(const Color3& c);
    Color3& operator -=(const Color3& c);
    Color3& operator *=(const Color3& c);
    Color3& operator *=(float k);
    Color3& operator /=(float k);
    Color3& operator /=(const Color3& c);

    /**
     * Gets the component array.
     *
     * @return The component array.
     */
    float* data();

    /**
     * Provided for const correctness.
     *
     * @see data()
     */
    const float* data() const;

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(Color3& other);

    float r;    ///< The red component.
    float g;    ///< The green component.
    float b;    ///< The blue component.
};

/// @cond
// verify packing assumptions
GRAPHICS_STATIC_ASSERT(sizeof(Color3[2]) == sizeof(float) * 6);
/// @endcond

const Color3 operator +(const Color3& a, const Color3& b);
const Color3 operator -(const Color3& a, const Color3& b);
const Color3 operator -(const Color3& c);
const Color3 operator *(const Color3& a, const Color3& b);
const Color3 operator *(float k, const Color3& c);
const Color3 operator *(const Color3& c, float k);
const Color3 operator /(const Color3& c, float k);
const Color3 operator /(const Color3& a, const Color3& b);

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
const Color3 clamp(const Color3& c, float min, float max);

/**
 * Linear interpolation between two colors.
 *
 * @param a Color containing the values at <code>t == 0.0f</code>.
 * @param b Color containing the values at <code>t == 1.0f</code>.
 * @param t Weight coefficient.
 *
 * @return <code>a + t * (b - a)</code>.
 */
const Color3 mix(const Color3& a, const Color3& b, float t);

#endif // #ifndef GRAPHICS_COLOR3_H_INCLUDED
