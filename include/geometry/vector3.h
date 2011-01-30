/**
 * @file geometry/vector3.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_VECTOR3_H_INCLUDED
#define GEOMETRY_VECTOR3_H_INCLUDED

#include <geometry/staticassert.h>

class Plane3;

/**
 * Represents a 3D vector.
 */
class Vector3
{
public:
    /**
     * Gets the zero vector.
     *
     * @return The zero vector.
     */
    static const Vector3& zero();

    /**
     * Gets the unit length x-axis direction vector.
     *
     * @return The unit length x-axis direction vector.
     */
    static const Vector3& xAxis();

    /**
     * Gets the unit length y-axis direction vector.
     *
     * @return The unit length y-axis direction vector.
     */
    static const Vector3& yAxis();

    /**
     * Gets the unit length z-axis direction vector.
     *
     * @return The unit length z-axis direction vector.
     */
    static const Vector3& zAxis();

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

    /**
     * Vector addition.
     *
     * @param v The vector to add to <code>*this</code>.
     *
     * @return Reference to <code>*this</code>.
     */
    Vector3& operator +=(const Vector3& v);

    /**
     * Vector subtraction.
     *
     * @param v The vector to subtract from <code>*this</code>.
     *
     * @return Reference to <code>*this</code>.
     */
    Vector3& operator -=(const Vector3& v);

    /**
     * Vector-times-scalar multiplication.
     *
     * @param k The multiplier.
     *
     * @return Reference to <code>*this</code>.
     */
    Vector3& operator *=(float k);

    /**
     * Vector-times-inverse scalar multiplication.
     *
     * @param k The divisor, cannot be zero.
     *
     * @return Reference to <code>*this</code>.
     */
    Vector3& operator /=(float k);

    /**
     * Array access operator.
     *
     * @param i Index of the component to return, between [0, 2].
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
     * Negates this vector.
     */
    void negate();

    /**
     * Normalizes this vector. The magnitude (length) of this vector cannot be
     * zero.
     */
    void normalize();

    /**
     * Sets all components.
     *
     * @param x The x-component to set.
     * @param y The y-component to set.
     * @param z The z-component to set.
     */
    void set(float x, float y, float z);

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(Vector3& other);

    float x;    ///< The x-component.
    float y;    ///< The y-component.
    float z;    ///< The z-component.
};

/// @cond
// verify packing assumptions
GEOMETRY_STATIC_ASSERT(sizeof(Vector3[2]) == sizeof(float) * 6);
/// @endcond

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
 * Vector subtraction.
 *
 * @param a The first vector.
 * @param b The other vector.
 *
 * @return <code>a - b</code>.
 */
const Vector3 operator -(const Vector3& a, const Vector3& b);

/**
 * Vector negation.
 *
 * @param v The vector to negate.
 *
 * @return Negated <code>v</code>.
 */
const Vector3 operator -(const Vector3& v);

/**
 * Scalar-times-vector multiplication.
 *
 * @param k The multiplier.
 * @param v The vector to multiply.
 *
 * @return <code>v</code> scaled by <code>k</code>.
 */
const Vector3 operator *(float k, const Vector3& v);

/**
 * Vector-times-scalar multiplication.
 *
 * @param v The vector to multiply.
 * @param k The multiplier.
 *
 * @return <code>v</code> scaled by <code>k</code>.
 */
const Vector3 operator *(const Vector3& v, float k);

/**
 * Vector-times-inverse scalar multiplication.
 *
 * @param v The vector to multiply.
 * @param k The divisor, cannot be zero.
 *
 * @return <code>v</code> scaled by the inverse of <code>k</code>.
 */
const Vector3 operator /(const Vector3& v, float k);

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
 * Calculates the squared distance between two points.
 *
 * @param a The first point.
 * @param b The other point.
 *
 * @return The squared distance between <code>a</code> and <code>b</code>.
 */
float sqrDistance(const Vector3& a, const Vector3& b);

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
 * Vector cross product.
 *
 * @param a The first vector.
 * @param b The other vector.
 *
 * @return The cross product of <code>a</code> and <code>b</code>.
 */
const Vector3 cross(const Vector3& a, const Vector3& b);

/**
 * Calculates the length of a given vector.
 *
 * @param v The vector whose length is to be calculated.
 *
 * @return Length of the given vector.
 */
float length(const Vector3& v);

/**
 * Calculates the squared length of a given vector.
 *
 * @param v The vector whose squared length is to be calculated.
 *
 * @return Squared length of the given vector.
 */
float sqrLength(const Vector3& v);

/**
 * Linear interpolation between two points.
 *
 * @param a Begin point.
 * @param b End point.
 * @param t Weight coefficient.
 *
 * @return <code>a + t * (b - a)</code>.
 */
const Vector3 mix(const Vector3& a, const Vector3& b, float t);

/**
 * Calculates a normalized vector. The magnitude (length) of the given vector
 * cannot be zero.
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

// TODO: should this be called mirror instead of reflect?
/**
 * Reflects a point across a plane.
 *
 * @param q The point to reflect.
 * @param plane Reflection plane.
 *
 * @return Reflected <code>q</code>.
 */
const Vector3 reflect(const Vector3& q, const Plane3& plane);

#endif // #ifndef GEOMETRY_VECTOR3_H_INCLUDED
