/**
 * @file geometry/matrix4x4.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_MATRIX4X4_H_INCLUDED
#define GEOMETRY_MATRIX4X4_H_INCLUDED

#include <geometry/staticassert.h>

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

    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

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

    // the assignment operators are members to prevent implicit type
    // conversions of the left hand side object

    Matrix4x4& operator +=(const Matrix4x4& m);
    Matrix4x4& operator -=(const Matrix4x4& m);
    Matrix4x4& operator *=(float k);
    Matrix4x4& operator *=(const Matrix4x4& m);
    Matrix4x4& operator /=(float k);

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
     * Gets the specified row as a vector.
     *
     * @param index Index of the row to return, between [0, 3].
     *
     * @return The specified row as a vector.
     */
    const Vector4 row(int index) const;

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

const Vector4 operator *(const Vector4& v, const Matrix4x4& m);

const Matrix4x4 operator +(const Matrix4x4& a, const Matrix4x4& b);
const Matrix4x4 operator -(const Matrix4x4& m);
const Matrix4x4 operator -(const Matrix4x4& a, const Matrix4x4& b);
const Matrix4x4 operator *(float k, const Matrix4x4& m);
const Matrix4x4 operator *(const Matrix4x4& m, float k);
const Matrix4x4 operator *(const Matrix4x4& a, const Matrix4x4& b);
const Matrix4x4 operator /(const Matrix4x4& m, float k);

// TODO: float determinant(const Matrix4x4& m);

/**
 * Equivalent to <code>v * transpose(m)</code>. This is intended as an
 * optimization.
 *
 * @param v The vector to multiply.
 * @param m The matrix by whose transpose vector <code>v</code> is to be
 * multiplied with.
 *
 * @return <code>v</code> multiplied by the transpose of <code>m</code>.
 */
const Vector4 timesTranspose(const Vector4& v, const Matrix4x4& m);

// TODO: const Matrix4x4 adjoint(const Matrix4x4& m);
// TODO: const Matrix4x4 inverse(const Matrix4x4& m);

/**
 * Orthogonalizes a matrix by applying a Gram-Schmidt process to its rows.
 *
 * @param m The matrix to orthogonalize.
 *
 * @return Orthogonalized <code>m</code>.
 */
const Matrix4x4 orthogonalize(const Matrix4x4& m);

/**
 * Equivalent to <code>a * transpose(b)</code>. This is intended as an
 * optimization.
 *
 * @param a The matrix to multiply.
 * @param b The matrix by whose transpose matrix <code>a</code> is to be
 * multiplied with.
 *
 * @return <code>a</code> multiplied by the transpose of <code>b</code>.
 */
const Matrix4x4 timesTranspose(const Matrix4x4& a, const Matrix4x4& b);

/**
 * Calculates the transpose of a given matrix.
 *
 * @param m Matrix whose transpose is to be calculated.
 *
 * @return The transpose of <code>m</code>.
 */
const Matrix4x4 transpose(const Matrix4x4& m);

/**
 * Equivalent to <code>transpose(a) * b</code>. This is intended as an
 * optimization.
 *
 * @param a The matrix whose transpose is to be multiplied.
 * @param b The matrix by which matrix <code>a</code> is to be multiplied with.
 *
 * @return Transpose of <code>a</code> multiplied by <code>b</code>.
 */
const Matrix4x4 transposeTimes(const Matrix4x4& a, const Matrix4x4& b);

#endif // #ifndef GEOMETRY_MATRIX4X4_H_INCLUDED
