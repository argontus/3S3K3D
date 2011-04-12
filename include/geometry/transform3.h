/**
 * @file geometry/transform3.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_TRANSFORM3_H_INCLUDED
#define GEOMETRY_TRANSFORM3_H_INCLUDED

#include <geometry/matrix3x3.h>
#include <geometry/runtimeassert.h>
#include <geometry/vector3.h>

class Matrix4x4;
class Transform2;

/**
 * Represents a 3D transformation. Supports translation, rotation and uniform
 * scaling, where the scaling factor is greater than zero.
 */
class Transform3
{
public:
    /**
     * Gets the identity transform.
     *
     * @return The identity transform.
     */
    static const Transform3 identity();

    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

    /**
     * Default constructor, constructs an identity transform.
     */
    Transform3();

    /**
     * Constructor.
     *
     * @param translation Translation.
     * @param rotation Rotation, this is assumed to be a valid rotation matrix.
     * @param scaling Uniform scaling factor, this is assumed to be greater
     * than zero.
     */
    Transform3(
        const Vector3& translation,
        const Matrix3x3& rotation,
        float scaling);

    // TODO: is this needed?
    /**
     * Constructor, constructs a transform equivalent to
     * <code>transform</code>.
     *
     * @param transform A 2D transform.
     */
    explicit Transform3(const Transform2& transform);

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(Transform3& other);

    /**
     * Translation.
     */
    Vector3 translation;

    /**
     * Rotation, this is assumed to be a valid rotation matrix.
     */
    Matrix3x3 rotation;

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
const Vector3 transform(const Vector3& q, const Transform3& t);

// TODO: is this needed?
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
const Vector3 transformByInverse(const Vector3& q, const Transform3& t);

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
Out transform(In first, In last, Out dst, const Transform3& t);

/**
 * Gets a 4x4 matrix that produces a transform equivalent to <code>t</code>.
 *
 * @param t A transform.
 *
 * @return A 4x4 matrix that produces a transform equivalent to <code>t</code>.
 */
const Matrix4x4 toMatrix4x4(const Transform3& t);

/**
 * Calculates the inverse transform of a given transform.
 *
 * @param t The transform whose inverse transform is to be calculated.
 *
 * @return The inverse transform of <code>t</code>.
 */
const Transform3 inverse(const Transform3& t);

/**
 * Spherical linear interpolation between two transforms.
 *
 * @param a Transform at <code>t == 0.0f</code>.
 * @param b Transform at <code>t == 1.0f</code>.
 * @param t Weight coefficient.
 *
 * @return The interpolated transform.
 */
const Transform3 slerp(const Transform3& a, const Transform3& b, float t);

/**
 * Transforms <code>a</code> by <code>b</code>.
 *
 * @param a A transform.
 * @param b A transform.
 *
 * @return Transform <code>t</code> such as <code>transform(x, t)</code> is
 * equivalent to <code>transform(transform(x, a), b)</code>.
 */
const Transform3 transform(const Transform3& a, const Transform3& b);

// TODO: is this needed?
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
const Transform3 transformByInverse(const Transform3& a, const Transform3& b);

// TODO: is this needed?
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
const Transform3 transformInverseBy(const Transform3& a, const Transform3& b);

template <class In, class Out>
Out transform(In first, const In last, Out dst, const Transform3& t)
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

#endif // #ifndef GEOMETRY_TRANSFORM3_H_INCLUDED
