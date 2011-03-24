/**
 * @file geometry/transform2.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_TRANSFORM2_H_INCLUDED
#define GEOMETRY_TRANSFORM2_H_INCLUDED

#include <geometry/matrix2x2.h>
#include <geometry/runtimeassert.h>
#include <geometry/vector2.h>

class Matrix4x4;

/**
 * Represents a 2D transformation. Supports translation, rotation and uniform
 * scaling, where the scaling factor is greater than zero.
 */
class Transform2
{
public:
    /**
     * Gets the identity transform.
     *
     * @return The identity transform.
     */
    static const Transform2 identity();

    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

    /**
     * Default constructor, constructs an identity transform.
     */
    Transform2();

    /**
     * Constructor.
     *
     * @param translation Translation.
     * @param rotation Rotation, this is assumed to be a valid rotation matrix.
     * @param scaling Uniform scaling factor, this is assumed to be greater
     * than zero.
     */
    Transform2(
        const Vector2& translation,
        const Matrix2x2& rotation,
        float scaling);

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(Transform2& other);

    /**
     * Translation.
     */
    Vector2 translation;

    /**
     * Rotation, this is assumed to be a valid rotation matrix.
     */
    Matrix2x2 rotation;

    /**
     * Uniform scale factor, this is assumed to be greater than zero.
     */
    float scaling;
};

/**
 * Transforms <code>q</code> by <code>t</code>. The order of application is
 * scaling first, rotation second and translation third.
 *
 * @param q The point to transform.
 * @param t The transform to apply.
 *
 * @return The transformed point.
 */
const Vector2 transform(const Vector2& q, const Transform2& t);

/**
 * Equivalent to <code>transform(q, inverse(t))</code>. This is intended as an
 * optimization. The order of application is negative translation first,
 * inverse rotation second and inverse scaling third.
 *
 * @param q The point to transform.
 * @param t The transform whose inverse is to be applied.
 *
 * @return The transformed point.
 */
const Vector2 transformByInverse(const Vector2& q, const Transform2& t);

/**
 * Transforms all items in the range [<code>first</code>, <code>last</code>) by
 * <code>t</code>.
 *
 * @param first Iterator pointing to the first item to transform.
 * @param last Iterator pointing one beyond the last item to transform.
 * @param dst Iterator pointing to the first item in the destination sequence.
 * This can be equal to <code>first</code>.
 * @param t The transform to apply.
 *
 * @return An iterator pointing to the item that follows the last item written
 * in the destination sequence.
 */
template <class In, class Out>
Out transform(In first, In last, Out dst, const Transform2& t);

/**
 * Gets a 4x4 matrix that produces a transform equivalent to <code>t</code>.
 *
 * @param t A transform.
 *
 * @return A 4x4 matrix that produces a transform equivalent to <code>t</code>.
 */
const Matrix4x4 toMatrix4x4(const Transform2& t);

/**
 * Calculates the inverse transform of a given transform.
 *
 * @param t The transform whose inverse transform is to be calculated.
 *
 * @return The inverse transform of <code>t</code>.
 */
const Transform2 inverse(const Transform2& t);

/**
 * Spherical linear interpolation between two transforms.
 *
 * @param a Transform at <code>t == 0.0f</code>.
 * @param b Transform at <code>t == 1.0f</code>.
 * @param t Weight coefficient.
 *
 * @return The interpolated transform.
 */
const Transform2 slerp(const Transform2& a, const Transform2& b, float t);

/**
 * Transforms <code>a</code> by <code>b</code>.
 *
 * @param a A transform.
 * @param b A transform.
 *
 * @return Transform <code>t</code> such as <code>transform(x, t)</code> is
 * equivalent to <code>transform(transform(x, a), b)</code>.
 */
const Transform2 transform(const Transform2& a, const Transform2& b);

/**
 * Equivalent to <code>transform(a, inverse(b))</code>. This is intended as an
 * optimization.
 *
 * @param a A transform.
 * @param b A transform.
 *
 * @return Transform <code>t</code> such as <code>transform(x, t)</code> is
 * equivalent to <code>transform(transform(x, a), inverse(b))</code>.
 */
const Transform2 transformByInverse(const Transform2& a, const Transform2& b);

/**
 * Equivalent to <code>transform(inverse(a), b)</code>. This is intended as an
 * optimization.
 *
 * @param a A transform.
 * @param b A transform.
 *
 * @return Transform <code>t</code> such as <code>transform(x, t)</code> is
 * equivalent to <code>transform(transform(x, inverse(a)), b)</code>.
 */
const Transform2 transformInverseBy(const Transform2& a, const Transform2& b);

template <class In, class Out>
Out transform(In first, const In last, Out dst, const Transform2& t)
{
    GEOMETRY_RUNTIME_ASSERT(t.scaling > 0.0f);

    while (first != last)
    {
        *dst = transform(*first, t);

        ++first;
        ++dst;
    }

    return dst;
}

#endif // #ifndef GEOMETRY_TRANSFORM2_H_INCLUDED
