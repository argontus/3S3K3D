/**
 * @file geometry/matrix4x4.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_MATRIX4X4_H_INCLUDED
#define GEOMETRY_MATRIX4X4_H_INCLUDED

#include <geometry/staticassert.h>

class Transform2;
class Transform3;
class Vector3;

/**
 * Represents a row-major 4x4 matrix.
 */
class Matrix4x4
{
public:
    /**
     * Gets the identity matrix.
     *
     * @return The identity matrix.
     */
    static const Matrix4x4& identity();

    /**
     * Gets a matrix that produces a 2D transform.
     *
     * @param transform 2D transform describing the transform matrix to
     * construct.
     *
     * @return Matrix that produces a 2D transform.
     */
    static const Matrix4x4 transform(const Transform2& transform);

    /**
     * Gets a matrix that produces a 3D transform.
     *
     * @param transform 3D transform describing the transform matrix to
     * construct.
     *
     * @return Matrix that produces a 3D transform.
     */
    static const Matrix4x4 transform(const Transform3& transform);

    /**
     * Gets a matrix that produces a translation.
     *
     * @param translation Translation.
     *
     * @return Matrix that produces a translation.
     */
    static const Matrix4x4 translation(const Vector3& translation);

    /**
     * Gets a matrix that produces a rotation about the x-axis.
     *
     * @param rotation Rotation, CCW about the x-axis, in radians.
     *
     * @return Matrix that produces a rotation about the x-axis.
     */
    static const Matrix4x4 xRotation(float rotation);

    /**
     * Gets a matrix that produces a rotation about the y-axis.
     *
     * @param rotation Rotation, CCW about the y-axis, in radians.
     *
     * @return Matrix that produces a rotation about the y-axis.
     */
    static const Matrix4x4 yRotation(float rotation);

    /**
     * Gets a matrix that produces a rotation about the z-axis.
     *
     * @param rotation Rotation, CCW about the z-axis, in radians.
     *
     * @return Matrix that produces a rotation about the z-axis.
     */
    static const Matrix4x4 zRotation(float rotation);

    /**
     * Gets a matrix that produces a rotation about an arbitrary axis.
     *
     * @param axis The axis to rotate about, must be unit length.
     * @param rotation Rotation, CCW about the given axis in radians.
     *
     * @return Matrix that produces a rotation about the given axis.
     */
    static const Matrix4x4 rotation(const Vector3& axis, float rotation);

    /**
     * Gets a matrix that produces a uniform scaling.
     *
     * @param scaling Uniform scale factor.
     *
     * @return Matrix that produces a uniform scaling.
     */
    static const Matrix4x4 scaling(float scaling);

    /**
     * Gets a matrix that produces a uniform or non-uniform scaling.
     *
     * @param sx Scaling along x-axis.
     * @param sy Scaling along y-axis.
     * @param sz Scaling along z-axis.
     *
     * @return Matrix that produces a uniform or non-uniform scaling.
     */
    static const Matrix4x4 scaling(float sx, float sy, float sz);

    // compiler-generated destructor, copy constructor and copy assignment
    // operator are fine

    /**
     * Default constructor, constructs an uninitialized matrix.
     */
    Matrix4x4();

    /**
     * Constructor.
     *
     * @param m00 Element at row 0, column 0.
     * @param m01 Element at row 0, column 1.
     * @param m02 Element at row 0, column 2.
     * @param m03 Element at row 0, column 3.
     * @param m10 Element at row 1, column 0.
     * @param m11 Element at row 1, column 1.
     * @param m12 Element at row 1, column 2.
     * @param m13 Element at row 1, column 3.
     * @param m20 Element at row 2, column 0.
     * @param m21 Element at row 2, column 1.
     * @param m22 Element at row 2, column 2.
     * @param m23 Element at row 2, column 3.
     * @param m30 Element at row 3, column 0.
     * @param m31 Element at row 3, column 1.
     * @param m32 Element at row 3, column 2.
     * @param m33 Element at row 3, column 3.
     */
    Matrix4x4(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33);

    /**
     * Array access operator. Allows matrices to be accessed like 2D
     * arrays of <code>float</code>.
     *
     * @param row Index of the row to return, between [0, 3].
     *
     * @return Pointer to the first element of the specified row.
     */
    float* operator [](int row);

    /**
     * Provided for const-correctness.
     *
     * @see operator [](int)
     */
    const float* operator [](int row) const;

    /**
     * Gets the element array.
     *
     * @return The element array.
     */
    float* data();

    /**
     * Provided for const-correctness.
     *
     * @see data()
     */
    const float* data() const;

    /**
     * Sets <code>*this</code> to the product of <code>*this</code> and
     * <code>m</code>.
     *
     * @param m The matrix to multiply this matrix with.
     */
    void multiplyBy(const Matrix4x4& m);

    /**
     * Sets <code>*this</code> to the product of <code>*this</code> and the
     * transpose of <code>m</code>.
     *
     * @param m The matrix by whose transpose this matrix is multiplied with.
     */
    void multiplyByT(const Matrix4x4& m);

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(Matrix4x4& other);

    float m00;  ///< Element at row 0, column 0.
    float m01;  ///< Element at row 0, column 1.
    float m02;  ///< Element at row 0, column 2.
    float m03;  ///< Element at row 0, column 3.

    float m10;  ///< Element at row 1, column 0.
    float m11;  ///< Element at row 1, column 1.
    float m12;  ///< Element at row 1, column 2.
    float m13;  ///< Element at row 1, column 3.

    float m20;  ///< Element at row 2, column 0.
    float m21;  ///< Element at row 2, column 1.
    float m22;  ///< Element at row 2, column 2.
    float m23;  ///< Element at row 2, column 3.

    float m30;  ///< Element at row 3, column 0.
    float m31;  ///< Element at row 3, column 1.
    float m32;  ///< Element at row 3, column 2.
    float m33;  ///< Element at row 3, column 3.
};

/// @cond
// verify packing assumptions
GEOMETRY_STATIC_ASSERT(sizeof(Matrix4x4[2]) == sizeof(float) * 32);
/// @endcond

/**
 * Matrix-matrix product.
 *
 * @param a Matrix to transform by matrix <code>b</code>.
 * @param b Matrix by which matrix <code>a</code> is to be transformed.
 *
 * @return <code>a</code> transformed by <code>b</code>.
 */
const Matrix4x4 product(const Matrix4x4& a, const Matrix4x4& b);

/**
 * Same as <code>product(a, transpose(b))</code>.
 *
 * @param a Matrix to transform by the transpose of matrix <code>b</code>.
 * @param b Matrix by whose transpose matrix <code>a</code> is to be
 * transformed.
 *
 * @return <code>a</code> transformed by the transpose of <code>b</code>.
 */
const Matrix4x4 productT(const Matrix4x4& a, const Matrix4x4& b);

/**
 * Calculates the transpose of a given matrix.
 *
 * @param m Matrix whose transpose is to be calculated.
 *
 * @return The transpose of <code>m</code>.
 */
const Matrix4x4 transpose(const Matrix4x4& m);

#endif // #ifndef GEOMETRY_MATRIX4X4_H_INCLUDED
