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

    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

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
    Matrix2x2(float m00, float m01, float m10, float m11);

    /**
     * Constructor.
     *
     * @param row0 Vector containing the elements of row 0.
     * @param row1 Vector containing the elements of row 1.
     */
    Matrix2x2(const Vector2& row0, const Vector2& row1);

    // the assignment operators are members to prevent implicit type
    // conversions of the left hand side object

    Matrix2x2& operator +=(const Matrix2x2& m);
    Matrix2x2& operator -=(const Matrix2x2& m);
    Matrix2x2& operator *=(float k);
    Matrix2x2& operator *=(const Matrix2x2& m);
    Matrix2x2& operator /=(float k);

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
     * @param index Index of the row to return, between [0, 1].
     *
     * @return The specified row as a vector.
     */
    const Vector2 row(int index) const;

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

const Vector2 operator *(const Vector2& v, const Matrix2x2& m);

const Matrix2x2 operator +(const Matrix2x2& a, const Matrix2x2& b);
const Matrix2x2 operator -(const Matrix2x2& m);
const Matrix2x2 operator -(const Matrix2x2& a, const Matrix2x2& b);
const Matrix2x2 operator *(float k, const Matrix2x2& m);
const Matrix2x2 operator *(const Matrix2x2& m, float k);
const Matrix2x2 operator *(const Matrix2x2& a, const Matrix2x2& b);
const Matrix2x2 operator /(const Matrix2x2& m, float k);

// TODO: float determinant(const Matrix2x2& m);

/**
 * Gets the rotation angle of <code>m</code>. <code>m</code> is assumed to be a
 * valid rotation matrix.
 *
 * @param m The rotation matrix whose rotation angle is to be calculated.
 *
 * @return The rotation angle of <code>m</code>, in radians, between [-pi, pi].
 */
float rotationAngle(const Matrix2x2& m);

// TODO: is this needed?
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
const Vector2 timesTranspose(const Vector2& v, const Matrix2x2& m);

// TODO: const Matrix2x2 adjoint(const Matrix2x2& m);
// TODO: const Matrix2x2 inverse(const Matrix2x2& m);

/**
 * Orthogonalizes a matrix by applying a Gram-Schmidt process to its rows.
 *
 * @param m The matrix to orthogonalize.
 *
 * @return Orthogonalized <code>m</code>.
 */
const Matrix2x2 orthogonalize(const Matrix2x2& m);

/**
 * Spherical linear interpolation between two rotation matrices. <code>a</code>
 * and <code>b</code> are assumed to be valid rotation matrices.
 *
 * @param a Matrix describing the rotation at <code>t == 0.0f</code>.
 * @param b Matrix describing the rotation at <code>t == 1.0f</code>.
 * @param t Weight coefficient.
 *
 * @return The interpolated rotation matrix.
 */
const Matrix2x2 slerp(const Matrix2x2& a, const Matrix2x2& b, float t);

// TODO: is this needed?
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
const Matrix2x2 timesTranspose(const Matrix2x2& a, const Matrix2x2& b);

/**
 * Calculates the transpose of a given matrix.
 *
 * @param m Matrix whose transpose is to be calculated.
 *
 * @return The transpose of <code>m</code>.
 */
const Matrix2x2 transpose(const Matrix2x2& m);

// TODO: is this needed?
/**
 * Equivalent to <code>transpose(a) * b</code>. This is intended as an
 * optimization.
 *
 * @param a The matrix whose transpose is to be multiplied.
 * @param b The matrix by which matrix <code>a</code> is to be multiplied with.
 *
 * @return Transpose of <code>a</code> multiplied by <code>b</code>.
 */
const Matrix2x2 transposeTimes(const Matrix2x2& a, const Matrix2x2& b);

#endif // #ifndef GEOMETRY_MATRIX2X2_H_INCLUDED
