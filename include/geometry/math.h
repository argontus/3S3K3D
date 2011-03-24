/**
 * @file geometry/math.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_MATH_H_INCLUDED
#define GEOMETRY_MATH_H_INCLUDED

#include <geometry/runtimeassert.h>

// TODO: wrapped in namespace Math until the whole module is wrapped within
// namespace Geometry
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
 * Gets the value of e.
 *
 * @return Value of e.
 */
float e();

// TODO: currently returns the maximum positive value, not infinity
/**
 * Gets a floating point value representing positive infinity. To get a
 * floating point value representing negative infinity, use
 * <code>-infinity()</code>.
 *
 * @return Floating point value representing positive infinity.
 */
float infinity();

/**
 * Gets the value of pi.
 *
 * @return Value of pi.
 */
float pi();
//@}

/**
 * @name Angle Conversion Functions
 */
//@{
/**
 * Converts radians to degrees.
 *
 * @param radians Angle in radians.
 *
 * @return The given angle in degrees.
 */
float degrees(float radians);

/**
 * Converts degrees to radians.
 *
 * @param degrees Angle in degrees.
 *
 * @return The given angle in radians.
 */
float radians(float degrees);
//@}

/**
 * @name Trigonometry Functions
 */
//@{
/**
 * Arc cosine. Returns an angle whose cosine is <code>x</code>.
 *
 * @param x Value whose arc cosine is to be calculated, this is silently
 * clamped between [-1, 1].
 *
 * @return An angle whose cosine is <code>x</code>, between [0, pi].
 */
float acos(float x);

/**
 * Arc sine. Returns an angle whose sine is <code>x</code>.
 *
 * @param x Value whose arc sine is to be calculated, this is silently clamped
 * between [-1, 1].
 *
 * @return An angle whose sine is <code>x</code>, between [-pi/2, pi/2].
 */
float asin(float x);

/**
 * Arc tangent. Returns an angle whose tangent is <code>x</code>.
 *
 * @param x Value whose arc tangent is to be calculated.
 *
 * @return Arc tangent of <code>x</code>, between [-pi/2, pi/2].
 */
float atan(float x);

/**
 * Arc tangent. Returns an angle whose tangent is <code>y/x</code>. To compute
 * the value, this function uses the sign of both arguments to determine the
 * quadrant.
 *
 * @param y Floating point value representing a y-coordinate.
 * @param x Floating point value representing an x-coordinate.
 *
 * @return Arc tangent of <code>y/x</code>, between [-pi, pi]. If both
 * parameters are zero, the return value is <code>0.0f</code>.
 */
float atan(float y, float x);

/**
 * Calculates the cosine of a given angle.
 *
 * @param angle Angle in radians.
 *
 * @return Cosine of the given angle.
 */
float cos(float angle);

/**
 * Calculates the sine of a given angle.
 *
 * @param angle Angle in radians.
 *
 * @return Sine of the given angle.
 */
float sin(float angle);

/**
 * Calculates the tangent of a given angle.
 *
 * @param angle Angle in radians. The cosine of this angle cannot be 0.
 *
 * @return Tangent of the given angle.
 */
float tan(float angle);
//@}

/**
 * @name Exponential Functions
 */
//@{
/**
 * Returns the natural exponentiation of <code>x</code>, i.e.,
 * e^<code>x</code>.
 *
 * @param x Exponent.
 *
 * @return The natural exponentiation of <code>x</code>.
 */
float exp(float x);

/**
 * Returns the natural logarithm of <code>x</code>, i.e., returns the value of
 * y, which satisfies the equation <code>x</code>=e^y.
 *
 * @param x Value whose natural logarithm is to be calculated, must be greater
 * than zero.
 *
 * @return The natural logarithm of <code>x</code>.
 */
float log(float x);

// TODO: find out when results are undefined
/**
 * Returns <code>base</code> raised to the <code>exponent</code> power, i.e.
 * <code>base</code>^<code>exponent</code>.
 *
 * @param base Base, cannot be negative.
 * @param exponent Exponent.
 *
 * @return <code>base</code> raised to the <code>exponent</code> power.
 */
float pow(float base, float exponent);

/**
 * Calculates the square of <code>x</code>, i.e., <code>x</code>^2.
 *
 * @param x Value whose square is to be calculated.
 *
 * @return The square of <code>x</code>.
 */
float sqr(float x);

/**
 * Calculates the square root of <code>x</code>.
 *
 * @param x Value whose square root is to be calculated, cannot be negative.
 *
 * @return Square root of <code>x</code>.
 */
float sqrt(float x);
//@}

/**
 * @name Common Functions
 */
//@{
/**
 * Returns a value equal to the nearest integer that is greater than or equal
 * to <code>x</code>.
 *
 * @param x Value whose ceiling is to be calculated.
 *
 * @return A value equal to the nearest integer that is greater than or equal
 * to <code>x</code>.
 */
float ceil(float x);

/**
 * Returns a value equal to the nearest integer that is less than or equal to
 * <code>x</code>.
 *
 * @param x Value whose floor is to be calculated.
 *
 * @return A value equal to the nearest integer that is less than or equal to
 * <code>x</code>.
 */
float floor(float x);

/**
 * Linear interpolation between two floating point values.
 *
 * @param a Value at <code>t == 0.0f</code>.
 * @param b Value at <code>t == 1.0f</code>.
 * @param t Weight coefficient.
 *
 * @return <code>a + t * (b - a)</code>.
 */
float mix(float a, float b, float t);

/**
 * Returns the modulus of <code>dividend</code>/<code>divisor</code>, i.e.,
 * returns <code>dividend - divisor * floor(dividend / divisor)</code>.
 *
 * @param dividend Dividend.
 * @param divisor Divisor, cannot be zero.
 *
 * @return The modulus of <code>dividend</code>/<code>divisor</code>.
 */
float mod(float dividend, float divisor);

/**
 * Returns the absolute value of <code>x</code>. Objects of type <code>T</code>
 * must meet the following requirements: Where <code>x</code> is of type
 * <code>T</code>, the expression <code>x < 0</code> shall be convertible to a
 * boolean value, shall be well-formed and shall have well-defined behavior.
 *
 * @param x Value whose absolute value is to be calculated.
 *
 * @return Absolute value of <code>x</code>.
 */
template <class T>
const T abs(const T& x);

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

/**
 * @name Utility Functions
 */
//@{
/**
 * Swaps the contents of <code>x</code> and <code>y</code>. Type <code>T</code>
 * must have a public copy constructor and a public copy assignment operator.
 *
 * @param x First variable.
 * @param y Second variable.
 */
template <class T>
void swap(T& x, T& y);
//@}

} // namespace Math

template <class T>
inline const T Math::abs(const T& x)
{
    // intentionally relies only on the '<' comparison operator

    if (x < 0)
    {
        return -x;
    }

    return x;
}

template <class T>
inline const T& Math::clamp(const T& value, const T& min, const T& max)
{
    // intentionally relies only on the '<' comparison operator

    GEOMETRY_RUNTIME_ASSERT(!(max < min));

    if (value < min)
    {
        return min;
    }

    if (max < value)
    {
        return max;
    }

    return value;
}

template <class T>
inline const T& Math::max(const T& a, const T& b)
{
    // intentionally relies only on the '<' comparison operator

    if (b < a)
    {
        return a;
    }

    return b;
}

template <class T>
inline const T& Math::min(const T& a, const T& b)
{
    // intentionally relies only on the '<' comparison operator

    if (b < a)
    {
        return b;
    }

    return a;
}

template <class T>
inline void Math::swap(T& x, T& y)
{
    const T t(x);
    x = y;
    y = t;
}

#endif // #ifndef GEOMETRY_MATH_H_INCLUDED
