/**
 * @file geometry/vector3.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_VECTOR3_H_INCLUDED
#define GEOMETRY_VECTOR3_H_INCLUDED

#include <geometry/staticassert.h>

/**
 * Represents a 3D vector.
 */
class Vector3
{
public:
    /**
     * Gets the zero vector.
     *
     * @return <code>Vector3(0.0f, 0.0f, 0.0f)</code>.
     */
    static const Vector3 zero();

    // compiler-generated destructor, copy constructor and copy assignment
    // operator are fine

    /**
     * Default constructor, constructs an uninitialized vector.
     */
    Vector3();

    /**
     * Constructor.
     *
     * @param x The x-component.
     * @param y The y-component.
     * @param z The z-component.
     */
    Vector3(float x, float y, float z);

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
    void swap(Vector3& other);

    // emulates GLSL component access
    union { float x; float r; float s; };
    union { float y; float g; float t; };
    union { float z; float b; float p; };
};

/// @cond
// verify packing assumptions
GEOMETRY_STATIC_ASSERT(sizeof(Vector3[2]) == sizeof(float) * 6);
/// @endcond

/**
 * Vector addition.
 *
 * @param a The vector to which <code>b</code> is to be added.
 * @param b The vector to add to <code>a</code>.
 *
 * @return Reference to <code>a</code>.
 */
Vector3& operator +=(Vector3& a, const Vector3& b);

/**
 * Vector subtraction.
 *
 * @param a The vector from which <code>b</code> is to be subtracted.
 * @param b The vector to subtract from <code>a</code>.
 *
 * @return Reference to <code>a</code>.
 */
Vector3& operator -=(Vector3& a, const Vector3& b);

/**
 * Vector-scalar multiplication.
 *
 * @param v The vector to multiply.
 * @param k The multiplier.
 *
 * @return Reference to <code>v</code>.
 */
Vector3& operator *=(Vector3& v, float k);

/**
 * Component-wise vector-vector multiplication.
 *
 * @param a The vector to multiply.
 * @param b The multiplier.
 *
 * @return Reference to <code>a</code>.
 */
Vector3& operator *=(Vector3& a, const Vector3& b);

/**
 * Vector-scalar division.
 *
 * @param v The vector to divide.
 * @param k The divisor, cannot be zero.
 *
 * @return Reference to <code>v</code>.
 */
Vector3& operator /=(Vector3& v, float k);

/**
 * Component-wise vector-scalar division.
 *
 * @param a The vector to divide.
 * @param b The divisor, none of the components can be zero.
 *
 * @return Reference to <code>a</code>.
 */
Vector3& operator /=(Vector3& a, const Vector3& b);

/**
 * Vector addition.
 *
 * @param a The first vector.
 * @param b The other vector.
 *
 * @return <code>a + b</code>.
 */
const Vector3 operator +(const Vector3& a, const Vector3& b);

/**
 * Vector negation.
 *
 * @param v The vector to negate.
 *
 * @return Negated <code>v</code>.
 */
const Vector3 operator -(const Vector3& v);

/**
 * Vector subtraction.
 *
 * @param a The first vector.
 * @param b The other vector.
 *
 * @return <code>a - b</code>.
 */
const Vector3 operator -(const Vector3& a, const Vector3& b);

/**
 * Scalar-vector multiplication.
 *
 * @param k The multiplier.
 * @param v The vector to multiply.
 *
 * @return <code>k * v</code>.
 */
const Vector3 operator *(float k, const Vector3& v);

/**
 * Vector-scalar multiplication.
 *
 * @param v The vector to multiply.
 * @param k The multiplier.
 *
 * @return <code>v * k</code>.
 */
const Vector3 operator *(const Vector3& v, float k);

/**
 * Component-wise vector-vector multiplication.
 *
 * @param a The vector to multiply.
 * @param b The multiplier.
 *
 * @return <code>a * b</code>.
 */
const Vector3 operator *(const Vector3& a, const Vector3& b);

/**
 * Vector-scalar division.
 *
 * @param v The vector to divide.
 * @param k The divisor, cannot be zero.
 *
 * @return <code>v / k</code>.
 */
const Vector3 operator /(const Vector3& v, float k);

/**
 * Component-wise vector-vector division.
 *
 * @param a The vector to divide.
 * @param b The divisor, none of the components can be zero.
 *
 * @return <code>a / b</code>.
 */
const Vector3 operator /(const Vector3& a, const Vector3& b);

/**
 * Calculates the angle between two vectors in radians. <code>a</code> and
 * <code>b</code> do not need to be unit length. If the magnitude (length) of a
 * given vector is zero, <code>Vector3(1.0f, 0.0f, 0.0f)</code> is used in
 * calculation in its stead.
 *
 * @param a The first vector.
 * @param b The other vector.
 *
 * @return The angle between <code>a</code> and <code>b</code> in radians,
 * between [0, pi].
 *
 * @see normalize(const Vector3&)
 */
float angleBetween(const Vector3& a, const Vector3& b);

/**
 * Calculates the distance between two points.
 *
 * @param a The first point.
 * @param b The other point.
 *
 * @return The distance between <code>a</code> and <code>b</code>.
 */
float distance(const Vector3& a, const Vector3& b);

/**
 * Vector dot product.
 *
 * @param a The first vector.
 * @param b The other vector.
 *
 * @return The dot product of <code>a</code> and <code>b</code>.
 */
float dot(const Vector3& a, const Vector3& b);

/**
 * Calculates the length of a given vector.
 *
 * @param v The vector whose length is to be calculated.
 *
 * @return Length of the given vector.
 */
float length(const Vector3& v);

/**
 * Calculates the squared distance between two points.
 *
 * @param a The first point.
 * @param b The other point.
 *
 * @return The squared distance between <code>a</code> and <code>b</code>.
 */
float sqrDistance(const Vector3& a, const Vector3& b);

/**
 * Calculates the squared length of a given vector.
 *
 * @param v The vector whose squared length is to be calculated.
 *
 * @return Squared length of the given vector.
 */
float sqrLength(const Vector3& v);

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
const Vector3 clamp(const Vector3& v, float min, float max);

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
const Vector3 clamp(const Vector3& v, const Vector3& min, const Vector3& max);

/**
 * Vector cross product.
 *
 * @param a The first vector.
 * @param b The other vector.
 *
 * @return The cross product of <code>a</code> and <code>b</code>.
 */
const Vector3 cross(const Vector3& a, const Vector3& b);

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
const Vector3 max(const Vector3& v, float k);

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
const Vector3 max(const Vector3& a, const Vector3& b);

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
const Vector3 min(const Vector3& v, float k);

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
const Vector3 min(const Vector3& a, const Vector3& b);

/**
 * Linear interpolation between two vectors.
 *
 * @param a Vector containing the values at <code>t == 0.0f</code>.
 * @param b Vector containing the values at <code>t == 1.0f</code>.
 * @param t Weight coefficient.
 *
 * @return <code>a + t * (b - a)</code>.
 */
const Vector3 mix(const Vector3& a, const Vector3& b, float t);

/**
 * Component-wise linear interpolation between two vectors.
 *
 * @param a Vector containing the values at
 * <code>t == Vector3(0.0f, 0.0f, 0.0f)</code>.
 * @param b Vector containing the values at
 * <code>t == Vector3(1.0f, 1.0f, 1.0f)</code>.
 * @param t Vector containing the component-wise weight coefficients.
 *
 * @return <code>a + t * (b - a)</code>.
 */
const Vector3 mix(const Vector3& a, const Vector3& b, const Vector3& t);

/**
 * Calculates a normalized vector. If the magnitude (length) of <code>v</code>
 * is zero, the returned vector is equal to
 * <code>Vector3(1.0f, 0.0f, 0.0f)</code>.
 *
 * @param v The vector from which the result vector is to be calculated.
 *
 * @return Normalized <code>v</code>.
 */
const Vector3 normalize(const Vector3& v);

/**
 * Reflects a vector.
 *
 * @param v The vector to reflect.
 * @param normal Unit length reflection surface normal.
 *
 * @return Reflected <code>v</code>.
 */
const Vector3 reflect(const Vector3& v, const Vector3& normal);

#endif // #ifndef GEOMETRY_VECTOR3_H_INCLUDED
