/**
 * @file geometry/vector4.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_VECTOR4_H_INCLUDED
#define GEOMETRY_VECTOR4_H_INCLUDED

#include <geometry/staticassert.h>

class Matrix4x4;

/**
 * Represents a 4D vector.
 */
class Vector4
{
public:
    /**
     * Gets the zero vector.
     *
     * @return <code>Vector4(0.0f, 0.0f, 0.0f, 0.0f)</code>.
     */
    static const Vector4 zero();

    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

    /**
     * Default constructor, constructs an uninitialized vector.
     */
    Vector4();

    /**
     * Constructor.
     *
     * @param x The x-component.
     * @param y The y-component.
     * @param z The z-component.
     * @param w The w-component.
     */
    Vector4(float x, float y, float z, float w);

    // the assignment operators are members to prevent implicit type
    // conversions of the left hand side object

    Vector4& operator +=(const Vector4& v);
    Vector4& operator -=(const Vector4& v);
    Vector4& operator *=(float k);
    Vector4& operator *=(const Matrix4x4& m);
    Vector4& operator /=(float k);

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
    void swap(Vector4& other);

    float x;    ///< The x-component.
    float y;    ///< The y-component.
    float z;    ///< The z-component.
    float w;    ///< The w-component.
};

/// @cond
// verify packing assumptions
GEOMETRY_STATIC_ASSERT(sizeof(Vector4[2]) == sizeof(float) * 8);
/// @endcond

const Vector4 operator +(const Vector4& a, const Vector4& b);
const Vector4 operator -(const Vector4& v);
const Vector4 operator -(const Vector4& a, const Vector4& b);
const Vector4 operator *(float k, const Vector4& v);
const Vector4 operator *(const Vector4& v, float k);
const Vector4 operator /(const Vector4& v, float k);

/**
 * Calculates the angle between two vectors in radians. <code>a</code> and
 * <code>b</code> do not need to be unit length. If the magnitude (length) of a
 * given vector is zero, <code>Vector4(1.0f, 0.0f, 0.0f, 0.0f)</code> is used
 * in calculation in its stead.
 *
 * @param a The first vector.
 * @param b The other vector.
 *
 * @return The angle between <code>a</code> and <code>b</code> in radians,
 * between [0, pi].
 *
 * @see normalize(const Vector4&)
 */
float angleBetween(const Vector4& a, const Vector4& b);

/**
 * Calculates the distance between two points.
 *
 * @param a The first point.
 * @param b The other point.
 *
 * @return The distance between <code>a</code> and <code>b</code>.
 */
float distance(const Vector4& a, const Vector4& b);

/**
 * Vector dot product.
 *
 * @param a The first vector.
 * @param b The other vector.
 *
 * @return The dot product of <code>a</code> and <code>b</code>.
 */
float dot(const Vector4& a, const Vector4& b);

/**
 * Calculates the length of a given vector.
 *
 * @param v The vector whose length is to be calculated.
 *
 * @return Length of the given vector.
 */
float length(const Vector4& v);

/**
 * Calculates the squared distance between two points.
 *
 * @param a The first point.
 * @param b The other point.
 *
 * @return The squared distance between <code>a</code> and <code>b</code>.
 */
float sqrDistance(const Vector4& a, const Vector4& b);

/**
 * Calculates the squared length of a given vector.
 *
 * @param v The vector whose squared length is to be calculated.
 *
 * @return Squared length of the given vector.
 */
float sqrLength(const Vector4& v);

/**
 * Linear interpolation between two vectors.
 *
 * @param a Vector containing the values at <code>t == 0.0f</code>.
 * @param b Vector containing the values at <code>t == 1.0f</code>.
 * @param t Weight coefficient.
 *
 * @return <code>a + t * (b - a)</code>.
 */
const Vector4 mix(const Vector4& a, const Vector4& b, float t);

/**
 * Calculates a normalized vector. If the magnitude (length) of <code>v</code>
 * is zero, the returned vector is equal to
 * <code>Vector4(1.0f, 0.0f, 0.0f, 0.0f)</code>.
 *
 * @param v The vector from which the result vector is to be calculated.
 *
 * @return Normalized <code>v</code>.
 */
const Vector4 normalize(const Vector4& v);

/**
 * Reflects a vector.
 *
 * @param v The vector to reflect.
 * @param n Unit length reflection surface normal.
 *
 * @return Reflected <code>v</code>.
 */
const Vector4 reflect(const Vector4& v, const Vector4& n);

// TODO: const Vector4 refract(const Vector4& v, const Vector4& n, float k);

#endif // #ifndef GEOMETRY_VECTOR4_H_INCLUDED
