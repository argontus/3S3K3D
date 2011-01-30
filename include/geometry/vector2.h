/**
 * @file geometry/vector2.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_VECTOR2_H_INCLUDED
#define GEOMETRY_VECTOR2_H_INCLUDED

#include <geometry/staticassert.h>

class Plane2;

/**
 * Represents a 2D vector.
 */
class Vector2
{
public:
    /**
     * Gets the zero vector.
     *
     * @return The zero vector.
     */
    static const Vector2& zero();

    /**
     * Gets the unit length x-axis direction vector.
     *
     * @return The unit length x-axis direction vector.
     */
    static const Vector2& xAxis();

    /**
     * Gets the unit length y-axis direction vector.
     *
     * @return The unit length y-axis direction vector.
     */
    static const Vector2& yAxis();

    /**
     * Creates a unit-length direction vector.
     *
     * @param theta Direction angle, CCW about the z-axis in radians.
     *
     * @return Unit-length direction vector.
     */
    static const Vector2 direction(float theta);

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

    /**
     * Vector addition.
     *
     * @param v The vector to add to <code>*this</code>.
     *
     * @return Reference to <code>*this</code>.
     */
    Vector2& operator +=(const Vector2& v);

    /**
     * Vector subtraction.
     *
     * @param v The vector to subtract from <code>*this</code>.
     *
     * @return Reference to <code>*this</code>.
     */
    Vector2& operator -=(const Vector2& v);

    /**
     * Vector-times-scalar multiplication.
     *
     * @param k The multiplier.
     *
     * @return Reference to <code>*this</code>.
     */
    Vector2& operator *=(float k);

    /**
     * Vector-times-inverse scalar multiplication.
     *
     * @param k The divisor, cannot be zero.
     *
     * @return Reference to <code>*this</code>.
     */
    Vector2& operator /=(float k);

    /**
     * Array access operator.
     *
     * @param i Index of the component to return, between [0, 1].
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
     * Sets both components.
     *
     * @param x The x-component to set.
     * @param y The y-component to set.
     */
    void set(float x, float y);

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
 * Vector subtraction.
 *
 * @param a The first vector.
 * @param b The other vector.
 *
 * @return <code>a - b</code>.
 */
const Vector2 operator -(const Vector2& a, const Vector2& b);

/**
 * Vector negation.
 *
 * @param v The vector to negate.
 *
 * @return Negated <code>v</code>.
 */
const Vector2 operator -(const Vector2& v);

/**
 * Scalar-times-vector multiplication.
 *
 * @param k The multiplier.
 * @param v The vector to multiply.
 *
 * @return <code>v</code> scaled by <code>k</code>.
 */
const Vector2 operator *(float k, const Vector2& v);

/**
 * Vector-times-scalar multiplication.
 *
 * @param v The vector to multiply.
 * @param k The multiplier.
 *
 * @return <code>v</code> scaled by <code>k</code>.
 */
const Vector2 operator *(const Vector2& v, float k);

/**
 * Vector-times-inverse scalar multiplication.
 *
 * @param v The vector to multiply.
 * @param k The divisor, cannot be zero.
 *
 * @return <code>v</code> scaled by the inverse of <code>k</code>.
 */
const Vector2 operator /(const Vector2& v, float k);

/**
 * Calculates the angle of a given direction vector in radians. The magnitude
 * (length) of the given vector cannot be zero.
 *
 * @param v The direction vector whose angle is to be calculated.
 *
 * @return Angle of direction vector <code>v</code> in radians.
 */
float angle(const Vector2& v);

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
 * Calculates the squared distance between two points.
 *
 * @param a The first point.
 * @param b The other point.
 *
 * @return The squared distance between <code>a</code> and <code>b</code>.
 */
float sqrDistance(const Vector2& a, const Vector2& b);

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
 * Same as <code>dot(perp(a), b)</code>.
 *
 * @param a The first vector.
 * @param b The other vector.
 *
 * @return Vector equal to <code>dot(perp(a), b)</code>.
 */
float perpDot(const Vector2& a, const Vector2& b);

/**
 * Calculates the length of a given vector.
 *
 * @param v The vector whose length is to be calculated.
 *
 * @return Length of the given vector.
 */
float length(const Vector2& v);

/**
 * Calculates the squared length of a given vector.
 *
 * @param v The vector whose squared length is to be calculated.
 *
 * @return Squared length of the given vector.
 */
float sqrLength(const Vector2& v);

/**
 * Linear interpolation between two points.
 *
 * @param a Begin point.
 * @param b End point.
 * @param t Weight coefficient.
 *
 * @return <code>a + t * (b - a)</code>.
 */
const Vector2 mix(const Vector2& a, const Vector2& b, float t);

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
 * Calculates a normalized vector. The magnitude (length) of the given vector
 * cannot be zero.
 *
 * @param v The vector from which the result vector is to be calculated.
 *
 * @return Normalized <code>v</code>.
 */
const Vector2 normalize(const Vector2& v);

/**
 * Reflects a vector.
 *
 * @param v The vector to reflect.
 * @param normal Unit length reflection surface normal.
 *
 * @return Reflected <code>v</code>.
 */
const Vector2 reflect(const Vector2& v, const Vector2& normal);

// TODO: should this be called mirror instead of reflect?
/**
 * Reflects a point across a plane.
 *
 * @param q The point to reflect.
 * @param plane Reflection plane.
 *
 * @return Reflected <code>q</code>.
 */
const Vector2 reflect(const Vector2& q, const Plane2& plane);

/**
 * Calculates a point from polar coordinates. This function uses origin as the
 * reference point.
 *
 * @param direction Offset direction in radians.
 * @param distance Offset distance from the reference point.
 *
 * @return The calculated point.
 */
const Vector2 polarPoint(float direction, float distance);

/**
 * Calculates a point from polar coordinates.
 *
 * @param point Reference point.
 * @param direction Offset direction in radians.
 * @param distance Offset distance from the reference point.
 *
 * @return The calculated point.
 */
const Vector2 polarPoint(const Vector2& point, float direction, float distance);

#endif // #ifndef GEOMETRY_VECTOR2_H_INCLUDED
