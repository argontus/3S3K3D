/**
 * @file geometry/matrix3x3.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_MATRIX3X3_H_INCLUDED
#define GEOMETRY_MATRIX3X3_H_INCLUDED

#include <geometry/staticassert.h>

class Vector3;

/**
 * Represents a row-major 3x3 matrix.
 */
class Matrix3x3
{
public:
    /**
     * Gets the identity matrix.
     *
     * @return The identity matrix.
     */
    static const Matrix3x3 identity();

    /**
     * Gets a matrix that produces a rotation about the x-axis.
     *
     * @param rotation Rotation, CCW about the x-axis, in radians.
     *
     * @return Matrix that produces a rotation about the x-axis.
     */
    static const Matrix3x3 xRotation(float rotation);

    /**
     * Gets a matrix that produces a rotation about the y-axis.
     *
     * @param rotation Rotation, CCW about the y-axis, in radians.
     *
     * @return Matrix that produces a rotation about the y-axis.
     */
    static const Matrix3x3 yRotation(float rotation);

    /**
     * Gets a matrix that produces a rotation about the z-axis.
     *
     * @param rotation Rotation, CCW about the z-axis, in radians.
     *
     * @return Matrix that produces a rotation about the z-axis.
     */
    static const Matrix3x3 zRotation(float rotation);

    /**
     * Gets a matrix that produces a rotation about an arbitrary axis.
     *
     * @param axis The axis to rotate about, must be unit length.
     * @param rotation Rotation, CCW about the given axis in radians.
     *
     * @return Matrix that produces a rotation about the given axis.
     */
    static const Matrix3x3 rotation(const Vector3& axis, float rotation);

    // compiler-generated destructor, copy constructor and copy assignment
    // operator are fine

    /**
     * Default constructor, constructs an uninitialized matrix.
     */
    Matrix3x3();

    /**
     * Constructor.
     *
     * @param m00 Element at row 0, column 0.
     * @param m01 Element at row 0, column 1.
     * @param m02 Element at row 0, column 2.
     * @param m10 Element at row 1, column 0.
     * @param m11 Element at row 1, column 1.
     * @param m12 Element at row 1, column 2.
     * @param m20 Element at row 2, column 0.
     * @param m21 Element at row 2, column 1.
     * @param m22 Element at row 2, column 2.
     */
    Matrix3x3(
        float m00, float m01, float m02,
        float m10, float m11, float m12,
        float m20, float m21, float m22);

    /**
     * Constructor.
     *
     * @param row0 Vector containing the elements of row 0.
     * @param row1 Vector containing the elements of row 1.
     * @param row2 Vector containing the elements of row 2.
     */
    Matrix3x3(const Vector3& row0, const Vector3& row1, const Vector3& row2);

    // TODO: is this needed?
    /**
     * Gets the first row as a vector.
     *
     * @return The first row as a vector.
     */
    const Vector3 row0() const;

    // TODO: is this needed?
    /**
     * Gets the second row as a vector.
     *
     * @return The second row as a vector.
     */
    const Vector3 row1() const;

    // TODO: is this needed?
    /**
     * Gets the third row as a vector.
     *
     * @return The third row as a vector.
     */
    const Vector3 row2() const;

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
    void swap(Matrix3x3& other);

    float m00;  ///< Element at row 0, column 0.
    float m01;  ///< Element at row 0, column 1.
    float m02;  ///< Element at row 0, column 2.

    float m10;  ///< Element at row 1, column 0.
    float m11;  ///< Element at row 1, column 1.
    float m12;  ///< Element at row 1, column 2.

    float m20;  ///< Element at row 2, column 0.
    float m21;  ///< Element at row 2, column 1.
    float m22;  ///< Element at row 2, column 2.
};

/// @cond
// verify packing assumptions
GEOMETRY_STATIC_ASSERT(sizeof(Matrix3x3[2]) == sizeof(float) * 18);
/// @endcond

/**
 * Vector-matrix product.
 *
 * @param v Vector to transform by matrix <code>m</code>.
 * @param m Matrix by which vector <code>v</code> is to be transformed.
 *
 * @return <code>v</code> transformed by <code>m</code>.
 */
const Vector3 product(const Vector3& v, const Matrix3x3& m);

/**
 * Equal to <code>product(v, transpose(m))</code>.
 *
 * @param v Vector to transform by the transpose of matrix <code>m</code>.
 * @param m Matrix by whose transpose vector <code>v</code> is to be
 * transformed.
 *
 * @return <code>v</code> transformed by the transpose of <code>m</code>.
 */
const Vector3 productT(const Vector3& v, const Matrix3x3& m);

/**
 * Orthogonalizes a matrix by applying a Gram-Schmidt process to its rows.
 *
 * @param m The matrix to orthogonalize.
 *
 * @return Orthogonalized <code>m</code>.
 */
const Matrix3x3 orthogonalize(const Matrix3x3& m);

/**
 * Matrix-matrix product.
 *
 * @param a Matrix to transform by matrix <code>b</code>.
 * @param b Matrix by which matrix <code>a</code> is to be transformed.
 *
 * @return <code>a</code> transformed by <code>b</code>.
 */
const Matrix3x3 product(const Matrix3x3& a, const Matrix3x3& b);

/**
 * Equal to <code>product(a, transpose(b))</code>.
 *
 * @param a Matrix to transform by the transpose of matrix <code>b</code>.
 * @param b Matrix by whose transpose matrix <code>a</code> is to be
 * transformed.
 *
 * @return <code>a</code> transformed by the transpose of <code>b</code>.
 */
const Matrix3x3 productT(const Matrix3x3& a, const Matrix3x3& b);

/**
 * Calculates the transpose of a given matrix.
 *
 * @param m Matrix whose transpose is to be calculated.
 *
 * @return The transpose of <code>m</code>.
 */
const Matrix3x3 transpose(const Matrix3x3& m);

#endif // #ifndef GEOMETRY_MATRIX3X3_H_INCLUDED
