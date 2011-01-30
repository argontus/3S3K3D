/**
 * @file geometry/transform3.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_TRANSFORM3_H_INCLUDED
#define GEOMETRY_TRANSFORM3_H_INCLUDED

#include <geometry/matrix3x3.h>
#include <geometry/runtimeassert.h>
#include <geometry/vector3.h>

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
    static const Transform3& identity();

    /**
     * Gets a transform that produces a translation.
     *
     * @param translation Translation.
     *
     * @return Transform that produces a translation.
     */
    static const Transform3 translation(const Vector3& translation);

    /**
     * Gets a transform that produces a rotation about the x-axis.
     *
     * @param rotation Rotation, CCW about the x-axis, in radians.
     *
     * @return Transform that produces a rotation about the x-axis.
     */
    static const Transform3 xRotation(float rotation);

    /**
     * Gets a transform that produces a rotation about the y-axis.
     *
     * @param rotation Rotation, CCW about the y-axis, in radians.
     *
     * @return Transform that produces a rotation about the y-axis.
     */
    static const Transform3 yRotation(float rotation);

    /**
     * Gets a transform that produces a rotation about the z-axis.
     *
     * @param rotation Rotation, CCW about the z-axis, in radians.
     *
     * @return Transform that produces a rotation about the z-axis.
     */
    static const Transform3 zRotation(float rotation);

    /**
     * Gets a transform that produces a rotation about an arbitrary axis.
     *
     * @param axis The axis to rotate about, must be unit length.
     * @param rotation Rotation, CCW about the given axis in radians.
     *
     * @return Transform that produces a rotation about the given axis.
     */
    static const Transform3 rotation(const Vector3& axis, float rotation);

    /**
     * Gets a transform that produces a uniform scaling.
     *
     * @param scaling Uniform scale factor.
     *
     * @return Transform that produces a uniform scaling.
     */
    static const Transform3 scaling(float scaling);

    // compiler-generated destructor, copy constructor and copy assignment
    // operator are fine

    /**
     * Default constructor, constructs an identity transform.
     */
    Transform3();

    /**
     * Constructor.
     *
     * @param translation Translation.
     * @param rotation Rotation, must be a valid rotation matrix.
     * @param scaling Uniform scaling factor, must be > 0.
     */
    Transform3(
        const Vector3& translation,
        const Matrix3x3& rotation,
        float scaling);

    /**
     * Applies a given transform to this transform.
     *
     * @param transform The transform to apply.
     */
    void transformBy(const Transform3& transform);

    /**
     * Sets the translation.
     *
     * @param translation The translation to set.
     */
    void setTranslation(const Vector3& translation);

    /**
     * Applies a translation to this transform.
     *
     * @param translation The translation to apply.
     */
    void translateBy(const Vector3& translation);

    /**
     * Gets the translation.
     *
     * @return Translation.
     */
    const Vector3 translation() const;

    /**
     * Sets the rotation.
     *
     * @param rotation The rotation to set, must be a valid rotation matrix.
     */
    void setRotation(const Matrix3x3& rotation);

    /**
     * Applies a rotation to this transform.
     *
     * @param rotation The rotation to apply, must be a valid rotation matrix.
     */
    void rotateBy(const Matrix3x3& rotation);

    /**
     * Gets the rotation.
     *
     * @return Rotation.
     */
    const Matrix3x3 rotation() const;

    /**
     * Sets the scaling.
     *
     * @param scaling The scaling to set.
     */
    void setScaling(float scaling);

    /**
     * Applies a scaling to this transform.
     *
     * @param scaling The scaling to apply.
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
    const Vector3 applyForward(const Vector3& q) const;

    /**
     * Applies the inverse of this transform to a single point. The order of
     * application is negative translation first, inverse scaling second and
     * inverse rotation third.
     *
     * @param q The point to transform.
     *
     * @return The transformed point.
     */
    const Vector3 applyInverse(const Vector3& q) const;

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
     * translation first, inverse scaling second and inverse rotation third.
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
    void swap(Transform3& other);

private:
    Vector3 translation_;   ///< Translation.
    Matrix3x3 rotation_;    ///< Rotation.
    float scaling_;         ///< Uniform scale factor, must be > 0.
};

/**
 * Calculates a conversion between local spaces of two transforms.
 *
 * @param src Source space transformation.
 * @param dst Destination space transformation.
 *
 * @return Transform that produces a conversion from local space of
 * <code>src</code> to local space of <code>dst</code>.
 */
const Transform3 conversion(const Transform3& src, const Transform3& dst);

/**
 * Calculates the inverse transform of a given transform.
 *
 * @param t The transform whose inverse transform is to be calculated.
 *
 * @return The inverse transform of the given transform.
 */
const Transform3 invert(const Transform3& t);

/**
 * Calculates a combined transform of two transforms.
 *
 * @param a The first transformation to apply.
 * @param b The second transformation to apply.
 *
 * @return Transform <code>t</code> such as <code>t.applyForward(v)</code> is
 * equal to <code>b.applyForward(a.applyForward(v))</code>.
 */
const Transform3 product(const Transform3& a, const Transform3& b);

/**
 * Calculates a combined transform of two transforms.
 *
 * @param a The first transformation to apply.
 * @param b The transformation whose inverse is to be applied.
 *
 * @return Transform <code>t</code> such as <code>t.applyForward(v)</code> is
 * equal to <code>b.applyInverse(a.applyForward(v))</code>.
 */
const Transform3 productI(const Transform3& a, const Transform3& b);

template <class In, class Out>
void Transform3::applyForward(In first, const In last, Out result) const
{
    GEOMETRY_RUNTIME_ASSERT(scaling_ > 0.0f);

    while (first != last)
    {
        *result = product(scaling_ * *first, rotation_) + translation_;

        ++first;
        ++result;
    }
}

template <class In, class Out>
void Transform3::applyInverse(In first, const In last, Out result) const
{
    GEOMETRY_RUNTIME_ASSERT(scaling_ > 0.0f);

    while (first != last)
    {
        *result = productT((*first - translation_) / scaling_, rotation_);

        ++first;
        ++result;
    }
}

#endif // #ifndef GEOMETRY_TRANSFORM3_H_INCLUDED
