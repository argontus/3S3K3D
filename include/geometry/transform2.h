/**
 * @file geometry/transform2.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_TRANSFORM2_H_INCLUDED
#define GEOMETRY_TRANSFORM2_H_INCLUDED

#include <geometry/matrix2x2.h>
#include <geometry/runtimeassert.h>
#include <geometry/vector2.h>

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
    static const Transform2& identity();

    /**
     * Gets a transform that produces a translation.
     *
     * @param translation Translation.
     *
     * @return Transform that produces a translation.
     */
    static const Transform2 translation(const Vector2& translation);

    /**
     * Gets a transform that produces a rotation about the z-axis.
     *
     * @param rotation Rotation, CCW about the z-axis, in radians.
     *
     * @return Transform that produces a rotation about the z-axis.
     */
    static const Transform2 rotation(float rotation);

    /**
     * Gets a transform that produces a uniform scaling.
     *
     * @param scaling Uniform scale factor, must be > 0.
     *
     * @return Transform that produces a uniform scaling.
     */
    static const Transform2 scaling(float scaling);

    // compiler-generated destructor, copy constructor and copy assignment
    // operator are fine

    /**
     * Default constructor, constructs an identity transform.
     */
    Transform2();

    /**
     * Constructor.
     *
     * @param translation Translation.
     * @param rotation Rotation, CCW about the z-axis in radians.
     * @param scaling Uniform scaling factor, must be > 0.
     */
    Transform2(const Vector2& translation, float rotation, float scaling);

    /**
     * Applies a given transform to this transform.
     *
     * @param transform The transform to apply.
     */
    void transformBy(const Transform2& transform);

    /**
     * Sets the translation.
     *
     * @param translation The translation to set.
     */
    void setTranslation(const Vector2& translation);

    /**
     * Applies a translation to this transform.
     *
     * @param translation The translation to apply.
     */
    void translateBy(const Vector2& translation);

    /**
     * Gets the translation.
     *
     * @return Translation.
     */
    const Vector2 translation() const;

    /**
     * Sets the rotation.
     *
     * @param rotation The rotation to set, CCW about the z-axis in radians.
     */
    void setRotation(float rotation);

    /**
     * Applies a rotation to this transform.
     *
     * @param rotation The rotation to apply, CCW about the z-axis in radians.
     */
    void rotateBy(float rotation);

    /**
     * Gets the rotation.
     *
     * @return Rotation, CCW about the z-axis in radians, always between
     * [0, 2*pi).
     */
    float rotation() const;

    /**
     * Sets the scaling.
     *
     * @param scaling The scaling to set, must be > 0.
     */
    void setScaling(float scaling);

    /**
     * Applies a scaling to this transform.
     *
     * @param scaling The scaling to apply, must be > 0.
     */
    void scaleBy(float scaling);

    /**
     * Gets the scaling.
     *
     * @return Scaling.
     */
    float scaling() const;

    /**
     * Applies this transform to a single point. The order of application is
     * scaling first, rotation second and translation third.
     *
     * @param q The point to transform.
     *
     * @return The transformed point.
     */
    const Vector2 applyForward(const Vector2& q) const;

    /**
     * Applies the inverse of this transform to a single point. The order of
     * application is negative translation first, inverse rotation second and
     * inverse scaling third.
     *
     * @param q The point to transform.
     *
     * @return The transformed point.
     */
    const Vector2 applyInverse(const Vector2& q) const;

    /**
     * Applies this transform to a set of points. This transform is applied to
     * all points in range [<code>first</code>, <code>last</code>). Each
     * transformed point is stored in the range beginning at
     * <code>result</code>. The order of application is scaling first, rotation
     * second and translation third.
     *
     * @param first Input iterator, the first in source range.
     * @param last Input iterator, one beyond the last in source range.
     * @param result Output iterator, the first in destination range.
     */
    template <class In, class Out>
    void applyForward(In first, In last, Out result) const;

    /**
     * Applies the inverse of this transform to a set of points. The inverse of
     * this transform is applied to all points in range [<code>first</code>,
     * <code>last</code>). Each transformed point is stored in the range
     * beginning at <code>result</code>. The order of application is negative
     * translation first, inverse rotation second and inverse scaling third.
     *
     * @param first Input iterator, the first in source range.
     * @param last Input iterator, one beyond the last in source range.
     * @param result Output iterator, the first in destination range.
     */
    template <class In, class Out>
    void applyInverse(In first, In last, Out result) const;

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(Transform2& other);

private:
    Vector2 translation_;   ///< Translation.
    float rotation_;        ///< Rotation, CCW about the z-axis in radians.
    float scaling_;         ///< Uniform scale factor, must be > 0.
};

// TODO: is the documentation for this function understandable?
/**
 * Calculates a conversion between local spaces of two transforms.
 *
 * @param src Source space transformation.
 * @param dst Destination space transformation.
 *
 * @return Transform that produces a conversion from local space of
 * <code>src</code> to local space of <code>dst</code>, that is, transform
 * <code>t</code> such as <code>t.applyForward(v)</code> is equal to
 * <code>dst.applyInverse(src.applyForward(v))</code>.
 */
const Transform2 conversion(const Transform2& src, const Transform2& dst);

/**
 * Calculates a combined transform of two transforms.
 *
 * @param a The first transformation to apply.
 * @param b The second transformation to apply.
 *
 * @return Transform <code>t</code> such as <code>t.applyForward(v)</code> is
 * equal to <code>b.applyForward(a.applyForward(v))</code>.
 */
const Transform2 product(const Transform2& a, const Transform2& b);

/**
 * Calculates the inverse transform of a given transform.
 *
 * @param t The transform whose inverse transform is to be calculated.
 *
 * @return The inverse transform of <code>t</code>.
 */
const Transform2 invert(const Transform2& t);

template <class In, class Out>
void Transform2::applyForward(In first, const In last, Out result) const
{
    GEOMETRY_RUNTIME_ASSERT(scaling_ > 0.0f);

    const Matrix2x2 rotation = Matrix2x2::rotation(rotation_);

    while (first != last)
    {
        *result = product(scaling_ * *first, rotation) + translation_;

        ++first;
        ++result;
    }
}

template <class In, class Out>
void Transform2::applyInverse(In first, const In last, Out result) const
{
    GEOMETRY_RUNTIME_ASSERT(scaling_ > 0.0f);

    const Matrix2x2 rotation = Matrix2x2::rotation(rotation_);

    while (first != last)
    {
        *result = productT(*first - translation_, rotation) / scaling_;

        ++first;
        ++result;
    }
}

#endif // #ifndef GEOMETRY_TRANSFORM2_H_INCLUDED
