/**
 * @file geometry/matrix4x4.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_MATRIX4X4_H_INCLUDED
#define GEOMETRY_MATRIX4X4_H_INCLUDED

#include <geometry/staticassert.h>

class Vector3;
class Vector4;

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
    static const Matrix4x4 identity();

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
     * Constructor.
     *
     * @param row0 Vector containing the elements of row 0.
     * @param row1 Vector containing the elements of row 1.
     * @param row2 Vector containing the elements of row 2.
     * @param row3 Vector containing the elements of row 3.
     */
    Matrix4x4(
        const Vector4& row0,
        const Vector4& row1,
        const Vector4& row2,
        const Vector4& row3);

    // TODO: is this needed?
    /**
     * Gets the first row as a vector.
     *
     * @return The first row as a vector.
     */
    const Vector4 row0() const;

    // TODO: is this needed?
    /**
     * Gets the second row as a vector.
     *
     * @return The second row as a vector.
     */
    const Vector4 row1() const;

    // TODO: is this needed?
    /**
     * Gets the third row as a vector.
     *
     * @return The third row as a vector.
     */
    const Vector4 row2() const;

    // TODO: is this needed?
    /**
     * Gets the fourth row as a vector.
     *
     * @return The fourth row as a vector.
     */
    const Vector4 row3() const;

    // TODO: should this be a member?
    /**
     * Gets the element array.
     *
     * @return The element array.
     */
    float* data();

    // TODO: should this be a member?
    /**
     * Provided for const-correctness.
     *
     * @see data()
     */
    const float* data() const;

    // TODO: should this be a member?
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
 * Vector-matrix product.
 *
 * @param v Vector to transform by matrix <code>m</code>.
 * @param m Matrix by which vector <code>v</code> is to be transformed.
 *
 * @return <code>v</code> transformed by <code>m</code>.
 */
const Vector4 product(const Vector4& v, const Matrix4x4& m);

/**
 * Equal to <code>product(v, transpose(m))</code>.
 *
 * @param v Vector to transform by the transpose of matrix <code>m</code>.
 * @param m Matrix by whose transpose vector <code>v</code> is to be
 * transformed.
 *
 * @return <code>v</code> transformed by the transpose of <code>m</code>.
 */
const Vector4 productT(const Vector4& v, const Matrix4x4& m);

/**
 * Orthogonalizes a matrix by applying a Gram-Schmidt process to its rows.
 *
 * @param m The matrix to orthogonalize.
 *
 * @return Orthogonalized <code>m</code>.
 */
const Matrix4x4 orthogonalize(const Matrix4x4& m);

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
 * Equal to <code>product(a, transpose(b))</code>.
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
