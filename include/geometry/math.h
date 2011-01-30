/**
 * @file geometry/math.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_MATH_H_INCLUDED
#define GEOMETRY_MATH_H_INCLUDED

#include <geometry/runtimeassert.h>

/**
 * Contains mathematical constants and functions.
 */
namespace Math {

/**
 * @name Mathematical Constants
 *
 * @details Each of these constants is wrapped within a function call to ensure
 * that they are initialized before use. C++ guarantees that local static
 * objects are initialized when the object's definition is first encountered
 * during a call to that function. The initialization order of namespace-level
 * objects in different compilation units is undefined.
 *
 * @see Effective C++, Third Edition, Item 4 by Scott Meyers
 * @see C++ Coding Standards, Chapter 21 by Herb Sutter and Andrei Alexandrescu
 */
//@{
/**
 * Gets the value of pi.
 *
 * @return Value of pi.
 */
float pi();

/**
 * Gets the value of pi/2.
 *
 * @return Value of pi/2.
 */
float halfPi();

/**
 * Gets the value of 2*pi.
 *
 * @return Value of 2*pi.
 */
float twoPi();

// TODO: minimum and maximum floating point values
//@}

/**
 * @name Angle Conversion Functions
 */
//@{
/**
 * Converts degrees to radians.
 *
 * @param value Angle in degrees.
 *
 * @return The given angle in radians.
 */
float degToRad(float value);

/**
 * Converts radians to degrees.
 *
 * @param value Angle in radians.
 *
 * @return The given angle in degrees.
 */
float radToDeg(float value);
//@}

/**
 * @name Trigonometric Functions
 */
//@{
/**
 * Calculates the cosine of a given angle.
 *
 * @param value Angle in radians.
 *
 * @return Cosine of the given angle.
 */
float cos(float value);

/**
 * Calculates the sine of a given angle.
 *
 * @param value Angle in radians.
 *
 * @return Sine of the given angle.
 */
float sin(float value);

/**
 * Calculates the tangent of a given angle.
 *
 * @param value Angle in radians. The cosine of this angle cannot be 0.
 *
 * @return Tangent of the given angle.
 */
float tan(float value);

/**
 * Calculates the arccosine of a given value.
 *
 * @param value Value whose arccosine is to be calculated, this is silently
 * clamped between [-1, 1].
 *
 * @return Arccosine of the given value.
 */
float acos(float value);

/**
 * Calculates the arcsine of a given value.
 *
 * @param value Value whose arcsine is to be calculated, this is silently
 * clamped between [-1, 1].
 *
 * @return Arcsine of the given value.
 */
float asin(float value);

/**
 * Calculates the arctangent of a given value.
 *
 * @param value Value whose arctangent is to be calculated.
 *
 * @return Arctangent of the given value, between [-pi/2, pi/2]. If the given
 * value is <code>0</code>, the return value is <code>0</code>.
 */
float atan(float value);

/**
 * Calculates the arctangent of <code>y/x</code>. To compute the value, this
 * function uses the sign of both arguments to determine the quadrant.
 *
 * @param y Floating point value representing an y-coordinate.
 * @param x Floating point value representing an x-coordinate.
 *
 * @return Arctangent of <code>y/x</code>, between [-pi, pi]. If both
 * parameters are <code>0</code>, the return value is <code>0</code>.
 */
float atan2(float y, float x);
//@}

/**
 * @name Power Functions
 */
//@{
/**
 * Calculates the square of a given value.
 *
 * @param value Value whose square is to be calculated.
 *
 * @return The given value squared.
 */
float sqr(float value);

/**
 * Calculates the square root of a given value.
 *
 * @param value Value whose square root is to be calculated, cannot be
 * negative.
 *
 * @return Square root of the given value.
 */
float sqrt(float value);

/**
 * Calculates the inverse square root of a given value.
 *
 * @param value Value whose inverse square root is to be calculated, must be
 * greater than zero.
 *
 * @return Inverse square root of the given value.
 */
float invSqrt(float value);
//@}

/**
 * @name Absolute Value and Rounding Functions
 */
//@{
/**
 * Calculates the absolute value of a given value.
 *
 * @param value Value whose absolute value is to be calculated.
 *
 * @return Absolute value of the given value.
 */
float abs(float value);

/**
 * Calculates the ceiling of a given value.
 *
 * @param value Value whose ceiling is to be calculated.
 *
 * @return A value representing the smallest integer that is greater than or
 * equal to the given value.
 */
float ceil(float value);

/**
 * Calculates the floor of a given value.
 *
 * @param value Value whose floor is to be calculated.
 *
 * @return A value representing the largest integer that is less than or equal
 * to the given value.
 */
float floor(float value);
//@}

/**
 * @name Utility Functions
 */
//@{
/**
 * Linear interpolation between two floating point values.
 *
 * @param a Begin value.
 * @param b End value.
 * @param t Weight coefficient.
 *
 * @return <code>a + t * (b - a)</code>.
 */
float mix(float a, float b, float t);

/**
 * Wraps a given value between [0, 2*pi).
 *
 * @param value The value to wrap.
 *
 * @return The given value wrapped between [0, 2*pi).
 */
float wrapTo2Pi(float value);
//@}

/**
 * @name Utility Function Templates
 */
//@{
/**
 * Clamps a given value between a specified interval. Objects of type
 * <code>T</code> must meet the following requirements: Where <code>a</code>
 * and <code>b</code> are of type <code>T</code>, the expression
 * <code>a < b</code> shall be convertible to a boolean value, shall be
 * well-formed and shall have well-defined behavior.
 *
 * @param value Value to clamp.
 * @param min Minimum value of the clamp interval.
 * @param max Maximum value of the clamp interval.
 *
 * @return <code>value</code> clamped between [<code>min</code>,
 * <code>max</code>].
 */
template <class T>
const T& clamp(const T& value, const T& min, const T& max);

/**
 * Gets the greater of given values. Objects of type <code>T</code> must meet
 * the following requirements: Where <code>a</code> and <code>b</code> are of
 * type <code>T</code>, the expression <code>a < b</code> shall be convertible
 * to a boolean value, shall be well-formed and shall have well-defined
 * behavior.
 *
 * @param a First value.
 * @param b Second value.
 *
 * @return The greater of the given values.
 */
template <class T>
const T& max(const T& a, const T& b);

/**
 * Gets the smaller of given values. Objects of type <code>T</code> must meet
 * the following requirements: Where <code>a</code> and <code>b</code> are of
 * type <code>T</code>, the expression <code>a < b</code> shall be convertible
 * to a boolean value, shall be well-formed and shall have well-defined
 * behavior.
 *
 * @param a First value.
 * @param b Second value.
 *
 * @return The smaller of the given values.
 */
template <class T>
const T& min(const T& a, const T& b);
//@}

} // namespace Math

template <class T>
inline const T& Math::clamp(const T& value, const T& min, const T& max)
{
    // intentionally relies only on the '<' comparison operator
    GEOMETRY_RUNTIME_ASSERT(!(max < min));
    return value < min ? min : max < value ? max : value;
}

template <class T>
inline const T& Math::max(const T& a, const T& b)
{
    // intentionally relies only on the '<' comparison operator
    return b < a ? a : b;
}

template <class T>
inline const T& Math::min(const T& a, const T& b)
{
    // intentionally relies only on the '<' comparison operator
    return b < a ? b : a;
}

#endif // #ifndef GEOMETRY_MATH_H_INCLUDED
