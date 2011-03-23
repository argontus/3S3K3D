/**
 * @file geometry/vector2.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_VECTOR2_H_INCLUDED
#define GEOMETRY_VECTOR2_H_INCLUDED

#include <geometry/staticassert.h>

/**
 * Represents a 2D vector.
 */
class Vector2
{
public:
    /**
     * Gets the zero vector.
     *
     * @return <code>Vector2(0.0f, 0.0f)</code>.
     */
    static const Vector2 zero();

    /**
     * Gets a unit-length direction vector.
     *
     * @param angle Direction angle, CCW about the z-axis in radians.
     *
     * @return Unit-length direction vector.
     */
    static const Vector2 direction(float angle);

    // compiler-generated destructor, copy constructor and copy assignment
    // operator are fine

    /**
     * Default constructor, constructs an uninitialized vector.
     */
    Vector2();

    /**
     * Constructor.
     *
     * @param x The x-component.
     * @param y The y-component.
     */
    Vector2(float x, float y);

    // TODO: should this be a member?
    /**
     * Gets the component array.
     *
     * @return The component array.
     */
    float* data();

    // TODO: should this be a member?
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
    void swap(Vector2& other);

    // emulates GLSL component access
    union { float x; float r; float s; };
    union { float y; float g; float t; };
};

/// @cond
// verify packing assumptions
GEOMETRY_STATIC_ASSERT(sizeof(Vector2[2]) == sizeof(float) * 4);
/// @endcond

/**
 * Vector addition.
 *
 * @param a The vector to which <code>b</code> is to be added.
 * @param b The vector to add to <code>a</code>.
 *
 * @return Reference to <code>a</code>.
 */
Vector2& operator +=(Vector2& a, const Vector2& b);

/**
 * Vector subtraction.
 *
 * @param a The vector from which <code>b</code> is to be subtracted.
 * @param b The vector to subtract from <code>a</code>.
 *
 * @return Reference to <code>a</code>.
 */
Vector2& operator -=(Vector2& a, const Vector2& b);

/**
 * Vector-scalar multiplication.
 *
 * @param v The vector to multiply.
 * @param k The multiplier.
 *
 * @return Reference to <code>v</code>.
 */
Vector2& operator *=(Vector2& v, float k);

/**
 * Component-wise vector-vector multiplication.
 *
 * @param a The vector to multiply.
 * @param b The multiplier.
 *
 * @return Reference to <code>a</code>.
 */
Vector2& operator *=(Vector2& a, const Vector2& b);

/**
 * Vector-scalar division.
 *
 * @param v The vector to divide.
 * @param k The divisor, cannot be zero.
 *
 * @return Reference to <code>v</code>.
 */
Vector2& operator /=(Vector2& v, float k);

/**
 * Component-wise vector-scalar division.
 *
 * @param a The vector to divide.
 * @param b The divisor, none of the components can be zero.
 *
 * @return Reference to <code>a</code>.
 */
Vector2& operator /=(Vector2& a, const Vector2& b);

/**
 * Vector addition.
 *
 * @param a The first vector.
 * @param b The other vector.
 *
 * @return <code>a + b</code>.
 */
const Vector2 operator +(const Vector2& a, const Vector2& b);

/**
 * Vector negation.
 *
 * @param v The vector to negate.
 *
 * @return Negated <code>v</code>.
 */
const Vector2 operator -(const Vector2& v);

/**
 * Vector subtraction.
 *
 * @param a The first vector.
 * @param b The other vector.
 *
 * @return <code>a - b</code>.
 */
const Vector2 operator -(const Vector2& a, const Vector2& b);

/**
 * Scalar-vector multiplication.
 *
 * @param k The multiplier.
 * @param v The vector to multiply.
 *
 * @return <code>k * v</code>.
 */
const Vector2 operator *(float k, const Vector2& v);

/**
 * Vector-scalar multiplication.
 *
 * @param v The vector to multiply.
 * @param k The multiplier.
 *
 * @return <code>v * k</code>.
 */
const Vector2 operator *(const Vector2& v, float k);

/**
 * Component-wise vector-vector multiplication.
 *
 * @param a The vector to multiply.
 * @param b The multiplier.
 *
 * @return <code>a * b</code>.
 */
const Vector2 operator *(const Vector2& a, const Vector2& b);

/**
 * Vector-scalar division.
 *
 * @param v The vector to divide.
 * @param k The divisor, cannot be zero.
 *
 * @return <code>v / k</code>.
 */
const Vector2 operator /(const Vector2& v, float k);

/**
 * Component-wise vector-vector division.
 *
 * @param a The vector to divide.
 * @param b The divisor, none of the components can be zero.
 *
 * @return <code>a / b</code>.
 */
const Vector2 operator /(const Vector2& a, const Vector2& b);

/**
 * Calculates the angle of a given direction vector in radians. <code>v</code>
 * does not need to be unit-length. If the magnitude (length) of <code>v</code>
 * is zero, <code>Vector2(1.0f, 0.0f)</code> is used in calculation in its
 * stead.
 *
 * @param v The direction vector whose angle is to be calculated.
 *
 * @return Angle of direction vector <code>v</code> in radians, between
 * [0, 2*pi). The angle of x-axis is 0, and the angle of y-axis is pi/2.
 *
 * @see normalize(const Vector2&)
 */
float angle(const Vector2& v);

/**
 * Calculates the angle between two vectors in radians. <code>a</code> and
 * <code>b</code> do not need to be unit length. If the magnitude (length) of a
 * given vector is zero, <code>Vector2(1.0f, 0.0f)</code> is used in
 * calculation in its stead.
 *
 * @param a The first vector.
 * @param b The other vector.
 *
 * @return The angle between <code>a</code> and <code>b</code> in radians,
 * between [0, pi].
 *
 * @see normalize(const Vector2&)
 */
float angleBetween(const Vector2& a, const Vector2& b);

/**
 * Calculates the distance between two points.
 *
 * @param a The first point.
 * @param b The other point.
 *
 * @return The distance between <code>a</code> and <code>b</code>.
 */
float distance(const Vector2& a, const Vector2& b);

/**
 * Vector dot product.
 *
 * @param a The first vector.
 * @param b The other vector.
 *
 * @return The dot product of <code>a</code> and <code>b</code>.
 */
float dot(const Vector2& a, const Vector2& b);

/**
 * Calculates the length of a given vector.
 *
 * @param v The vector whose length is to be calculated.
 *
 * @return Length of the given vector.
 */
float length(const Vector2& v);

/**
 * Same as <code>dot(perp(a), b)</code>.
 *
 * @param a The first vector.
 * @param b The other vector.
 *
 * @return Vector equal to <code>dot(perp(a), b)</code>.
 */
float perpDot(const Vector2& a, const Vector2& b);

/**
 * Calculates the squared distance between two points.
 *
 * @param a The first point.
 * @param b The other point.
 *
 * @return The squared distance between <code>a</code> and <code>b</code>.
 */
float sqrDistance(const Vector2& a, const Vector2& b);

/**
 * Calculates the squared length of a given vector.
 *
 * @param v The vector whose squared length is to be calculated.
 *
 * @return Squared length of the given vector.
 */
float sqrLength(const Vector2& v);

/**
 * Clamps the components of <code>v</code> between
 * [<code>min</code>, <code>max</code>]. <code>min</code> must be less than or
 * equal to <code>max</code>.
 *
 * @param v The vector to clamp.
 * @param min Minimum value.
 * @param max Maximum value.
 *
 * @return Clamped <code>v</code>.
 */
const Vector2 clamp(const Vector2& v, float min, float max);

/**
 * Clamps the components of <code>v</code> component-wise between
 * [<code>min</code>, <code>max</code>]. Each component of <code>min</code>
 * must be less than or equal to the corresponding component of
 * <code>max</code>.
 *
 * @param v The vector to clamp.
 * @param min Vector containing the component-wise minimum values.
 * @param max Vector containing the component-wise maximum values.
 *
 * @return Clamped <code>v</code>.
 */
const Vector2 clamp(const Vector2& v, const Vector2& min, const Vector2& max);

/**
 * Returns a vector containing the component-wise maximum values of
 * <code>v</code> and <code>k</code>.
 *
 * @param v The vector to compare.
 * @param k The scalar value to compare.
 *
 * @param Vector containing the component-wise maximum values of <code>v</code>
 * and <code>k</code>.
 */
const Vector2 max(const Vector2& v, float k);

/**
 * Returns a vector containing the component-wise maximum values of
 * <code>a</code> and <code>b</code>.
 *
 * @param a The first vector to compare.
 * @param b The second vector to compare.
 *
 * @param Vector containing the component-wise maximum values of <code>a</code>
 * and <code>b</code>.
 */
const Vector2 max(const Vector2& a, const Vector2& b);

/**
 * Returns a vector containing the component-wise minimum values of
 * <code>v</code> and <code>k</code>.
 *
 * @param v The vector to compare.
 * @param k The scalar value to compare.
 *
 * @param Vector containing the component-wise minimum values of <code>v</code>
 * and <code>k</code>.
 */
const Vector2 min(const Vector2& v, float k);

/**
 * Returns a vector containing the component-wise minimum values of
 * <code>a</code> and <code>b</code>.
 *
 * @param a The first vector to compare.
 * @param b The second vector to compare.
 *
 * @param Vector containing the component-wise minimum values of <code>a</code>
 * and <code>b</code>.
 */
const Vector2 min(const Vector2& a, const Vector2& b);

/**
 * Linear interpolation between two vectors.
 *
 * @param a Vector containing the values at <code>t == 0.0f</code>.
 * @param b Vector containing the values at <code>t == 1.0f</code>.
 * @param t Weight coefficient.
 *
 * @return <code>a + t * (b - a)</code>.
 */
const Vector2 mix(const Vector2& a, const Vector2& b, float t);

/**
 * Component-wise linear interpolation between two vectors.
 *
 * @param a Vector containing the values at
 * <code>t == Vector2(0.0f, 0.0f)</code>.
 * @param b Vector containing the values at
 * <code>t == Vector2(1.0f, 1.0f)</code>.
 * @param t Vector containing the component-wise weight coefficients.
 *
 * @return <code>a + t * (b - a)</code>.
 */
const Vector2 mix(const Vector2& a, const Vector2& b, const Vector2& t);

/**
 * Calculates a normalized vector. If the magnitude (length) of <code>v</code>
 * is zero, the returned vector is equal to <code>Vector2(1.0f, 0.0f)</code>.
 *
 * @param v The vector from which the result vector is to be calculated.
 *
 * @return Normalized <code>v</code>.
 */
const Vector2 normalize(const Vector2& v);

/**
 * Calculates a vector perpendicular (rotated 90 degrees CCW) to a given
 * vector.
 *
 * @param v The vector from which the result vector is to be calculated.
 *
 * @return <code>Vector2(-v.y, v.x)</code>.
 */
const Vector2 perp(const Vector2& v);

/**
 * Calculates a point from polar coordinates. This function uses origin as the
 * reference point.
 *
 * @param angle Angular coordinate in radians.
 * @param radius Radial coordinate, distance from the reference point.
 *
 * @return The calculated point.
 */
const Vector2 polarPoint(float angle, float radius);

/**
 * Calculates a point from polar coordinates.
 *
 * @param origin Reference point.
 * @param angle Angular coordinate in radians.
 * @param radius Radial coordinate, distance from the reference point.
 *
 * @return The calculated point.
 */
const Vector2 polarPoint(const Vector2& origin, float angle, float radius);

/**
 * Reflects a vector.
 *
 * @param v The vector to reflect.
 * @param normal Unit length reflection surface normal.
 *
 * @return Reflected <code>v</code>.
 */
const Vector2 reflect(const Vector2& v, const Vector2& normal);

#endif // #ifndef GEOMETRY_VECTOR2_H_INCLUDED
