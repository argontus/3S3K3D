/**
 * @file geometry/matrix2x2.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_MATRIX2X2_H_INCLUDED
#define GEOMETRY_MATRIX2X2_H_INCLUDED

#include <geometry/staticassert.h>

class Vector2;

/**
 * Represents a row-major 2x2 matrix.
 */
class Matrix2x2
{
public:
    /**
     * Gets the identity matrix.
     *
     * @return The identity matrix.
     */
    static const Matrix2x2 identity();

    /**
     * Gets a matrix that produces a rotation about the z-axis.
     *
     * @param rotation Rotation, CCW about the z-axis, in radians.
     *
     * @return Matrix that produces a rotation about the z-axis.
     */
    static const Matrix2x2 rotation(float rotation);

    // compiler-generated destructor, copy constructor and copy assignment
    // operator are fine

    /**
     * Default constructor, constructs an uninitialized matrix.
     */
    Matrix2x2();

    /**
     * Constructor.
     *
     * @param m00 Element at row 0, column 0.
     * @param m01 Element at row 0, column 1.
     * @param m10 Element at row 1, column 0.
     * @param m11 Element at row 1, column 1.
     */
    Matrix2x2(
        float m00, float m01,
        float m10, float m11);

    /**
     * Constructor.
     *
     * @param row0 Vector containing the elements of row 0.
     * @param row1 Vector containing the elements of row 1.
     */
    Matrix2x2(const Vector2& row0, const Vector2& row1);

    // TODO: is this needed?
    /**
     * Gets the first row as a vector.
     *
     * @return The first row as a vector.
     */
    const Vector2 row0() const;

    // TODO: is this needed?
    /**
     * Gets the second row as a vector.
     *
     * @return The second row as a vector.
     */
    const Vector2 row1() const;

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
    void swap(Matrix2x2& other);

    float m00;  ///< Element at row 0, column 0.
    float m01;  ///< Element at row 0, column 1.

    float m10;  ///< Element at row 1, column 0.
    float m11;  ///< Element at row 1, column 1.
};

/// @cond
// verify packing assumptions
GEOMETRY_STATIC_ASSERT(sizeof(Matrix2x2[2]) == sizeof(float) * 8);
/// @endcond

/**
 * Vector-matrix product.
 *
 * @param v Vector to transform by matrix <code>m</code>.
 * @param m Matrix by which vector <code>v</code> is to be transformed.
 *
 * @return <code>v</code> transformed by <code>m</code>.
 */
const Vector2 product(const Vector2& v, const Matrix2x2& m);

/**
 * Equal to <code>product(v, transpose(m))</code>.
 *
 * @param v Vector to transform by the transpose of matrix <code>m</code>.
 * @param m Matrix by whose transpose vector <code>v</code> is to be
 * transformed.
 *
 * @return <code>v</code> transformed by the transpose of <code>m</code>.
 */
const Vector2 productT(const Vector2& v, const Matrix2x2& m);

/**
 * Orthogonalizes a matrix by applying a Gram-Schmidt process to its rows.
 *
 * @param m The matrix to orthogonalize.
 *
 * @return Orthogonalized <code>m</code>.
 */
const Matrix2x2 orthogonalize(const Matrix2x2& m);

/**
 * Matrix-matrix product.
 *
 * @param a Matrix to transform by matrix <code>b</code>.
 * @param b Matrix by which matrix <code>a</code> is to be transformed.
 *
 * @return <code>a</code> transformed by <code>b</code>.
 */
const Matrix2x2 product(const Matrix2x2& a, const Matrix2x2& b);

/**
 * Equal to <code>product(a, transpose(b))</code>.
 *
 * @param a Matrix to transform by the transpose of matrix <code>b</code>.
 * @param b Matrix by whose transpose matrix <code>a</code> is to be
 * transformed.
 *
 * @return <code>a</code> transformed by the transpose of <code>b</code>.
 */
const Matrix2x2 productT(const Matrix2x2& a, const Matrix2x2& b);

/**
 * Calculates the transpose of a given matrix.
 *
 * @param m Matrix whose transpose is to be calculated.
 *
 * @return The transpose of <code>m</code>.
 */
const Matrix2x2 transpose(const Matrix2x2& m);

#endif // #ifndef GEOMETRY_MATRIX2X2_H_INCLUDED
