/**
 * @file geometry/vector2.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_VECTOR2_H_INCLUDED
#define GEOMETRY_VECTOR2_H_INCLUDED

#include <geometry/staticassert.h>

class Matrix2x2;

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

    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

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

    // the assignment operators are members to prevent implicit type
    // conversions of the left hand side object

    Vector2& operator +=(const Vector2& v);
    Vector2& operator -=(const Vector2& v);
    Vector2& operator *=(float k);
    Vector2& operator *=(const Matrix2x2& m);
    Vector2& operator /=(float k);

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
    void swap(Vector2& other);

    float x;    ///< The x-component.
    float y;    ///< The y-component.
};

/// @cond
// verify packing assumptions
GEOMETRY_STATIC_ASSERT(sizeof(Vector2[2]) == sizeof(float) * 4);
/// @endcond

const Vector2 operator +(const Vector2& a, const Vector2& b);
const Vector2 operator -(const Vector2& v);
const Vector2 operator -(const Vector2& a, const Vector2& b);
const Vector2 operator *(float k, const Vector2& v);
const Vector2 operator *(const Vector2& v, float k);
const Vector2 operator /(const Vector2& v, float k);

/**
 * Calculates the angle of a given direction vector in radians. <code>v</code>
 * does not need to be unit-length. If <code>v</code> is a zero vector, the
 * return value is zero.
 *
 * @param v The direction vector whose angle is to be calculated.
 *
 * @return Angle of direction vector <code>v</code> in radians, between
 * [-pi, pi].
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
 * Calculates a point from polar coordinates.
 *
 * @param radius Radial coordinate, distance from the origin.
 * @param angle Angular coordinate in radians.
 *
 * @return The calculated point.
 */
const Vector2 polarPoint(float radius, float angle);

/**
 * Reflects a vector.
 *
 * @param v The vector to reflect.
 * @param n Unit length reflection surface normal.
 *
 * @return Reflected <code>v</code>.
 */
const Vector2 reflect(const Vector2& v, const Vector2& n);

// TODO: const Vector2 refract(const Vector2& v, const Vector2& n, float k);

#endif // #ifndef GEOMETRY_VECTOR2_H_INCLUDED
