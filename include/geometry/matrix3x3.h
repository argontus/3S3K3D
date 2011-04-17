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
     * Gets a matrix that produces a rotation about an arbitrary axis.
     *
     * @param axis The axis to rotate about, must be unit length.
     * @param angle Rotation, CCW about the given axis in radians.
     *
     * @return Matrix that produces a rotation about the given axis.
     */
    static const Matrix3x3 rotation(const Vector3& axis, float angle);

    /**
     * Gets a matrix that produces a rotation about the x-axis.
     *
     * @param angle Rotation, CCW about the x-axis, in radians.
     *
     * @return Matrix that produces a rotation about the x-axis.
     */
    static const Matrix3x3 xRotation(float angle);

    /**
     * Gets a matrix that produces a rotation about the y-axis.
     *
     * @param angle Rotation, CCW about the y-axis, in radians.
     *
     * @return Matrix that produces a rotation about the y-axis.
     */
    static const Matrix3x3 yRotation(float angle);

    /**
     * Gets a matrix that produces a rotation about the z-axis.
     *
     * @param angle Rotation, CCW about the z-axis, in radians.
     *
     * @return Matrix that produces a rotation about the z-axis.
     */
    static const Matrix3x3 zRotation(float angle);

    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

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

    // the assignment operators are members to prevent implicit type
    // conversions of the left hand side object

    Matrix3x3& operator +=(const Matrix3x3& m);
    Matrix3x3& operator -=(const Matrix3x3& m);
    Matrix3x3& operator *=(float k);
    Matrix3x3& operator *=(const Matrix3x3& m);
    Matrix3x3& operator /=(float k);

    /**
     * Gets the element array.
     *
     * @return The element array.
     */
    float* data();

    /**
     * Provided for const correctness.
     *
     * @see data()
     */
    const float* data() const;

    /**
     * Gets the specified row as a vector.
     *
     * @param index Index of the row to return, between [0, 2].
     *
     * @return The specified row as a vector.
     */
    const Vector3 row(int index) const;

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

const Vector3 operator *(const Vector3& v, const Matrix3x3& m);

const Matrix3x3 operator +(const Matrix3x3& a, const Matrix3x3& b);
const Matrix3x3 operator -(const Matrix3x3& m);
const Matrix3x3 operator -(const Matrix3x3& a, const Matrix3x3& b);
const Matrix3x3 operator *(float k, const Matrix3x3& m);
const Matrix3x3 operator *(const Matrix3x3& m, float k);
const Matrix3x3 operator *(const Matrix3x3& a, const Matrix3x3& b);
const Matrix3x3 operator /(const Matrix3x3& m, float k);

/**
 * Extracts the axis and angle of rotation of <code>m</code>. <code>m</code> is
 * assumed to be a valid rotation matrix.
 *
 * @param m The rotation matrix from which the axis and angle of rotation are
 * to be extracted.
 * @param axis Variable to which the extracted axis is stored, cannot be a null
 * pointer.
 * @param angle Variable to which the extracted angle is stored, cannot be a
 * null pointer.
 */
void extractAxisAngle(const Matrix3x3& m, Vector3* axis, float* angle);

/**
 * Gets the determinant of <code>m</code>.
 *
 * @param m The matrix whose determinant is to be calculated.
 *
 * @return The determinant of <code>m</code>.
 */
float determinant(const Matrix3x3& m);

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
const Vector3 timesTranspose(const Vector3& v, const Matrix3x3& m);

/**
 * Gets the adjoint matrix of <code>m</code>.
 *
 * @param m The matrix whose adjoint matrix is to be calculated.
 *
 * @return The adjoint matrix of <code>m</code>.
 */
const Matrix3x3 adjoint(const Matrix3x3& m);

/**
 * Gets the inverse matrix of <code>m</code>. The return value is equivalent to
 * <code>1.0f / determinant(m) * adjoint(m)</code>. <code>m</code> cannot be
 * singular, i.e., the determinant of <code>m</code> cannot zero.
 *
 * @param m The matrix whose inverse matrix is to be calculated.
 *
 * @return The inverse matrix of <code>m</code>.
 */
const Matrix3x3 inverse(const Matrix3x3& m);

/**
 * Orthogonalizes a matrix by applying a Gram-Schmidt process to its rows.
 *
 * @param m The matrix to orthogonalize.
 *
 * @return Orthogonalized <code>m</code>.
 */
const Matrix3x3 orthogonalize(const Matrix3x3& m);

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
const Matrix3x3 slerp(const Matrix3x3& a, const Matrix3x3& b, float t);

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
const Matrix3x3 timesTranspose(const Matrix3x3& a, const Matrix3x3& b);

/**
 * Calculates the transpose of a given matrix.
 *
 * @param m Matrix whose transpose is to be calculated.
 *
 * @return The transpose of <code>m</code>.
 */
const Matrix3x3 transpose(const Matrix3x3& m);

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
const Matrix3x3 transposeTimes(const Matrix3x3& a, const Matrix3x3& b);

// TODO: const Matrix3x3 transposeTimesTranspose(const Matrix3x3& a, const Matrix3x3& b);

#endif // #ifndef GEOMETRY_MATRIX3X3_H_INCLUDED
