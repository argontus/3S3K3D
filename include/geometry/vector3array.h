/**
 * @file geometry/vector3array.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_VECTOR3ARRAY_H_INCLUDED
#define GEOMETRY_VECTOR3ARRAY_H_INCLUDED

#include <geometry/extents3.h>

/**
 * Represents a fixed size array of <code>Vector3</code> objects.
 */
class Vector3Array
{
public:
    /**
     * A random access iterator.
     */
    typedef Vector3* Iterator;

    /**
     * A random access constant iterator.
     */
    typedef const Vector3* ConstIterator;

    /**
     * Destructor.
     */
    ~Vector3Array();

    /**
     * Constructor, does not initialize the constructed vectors.
     *
     * @param size Number of <code>Vector3</code> objects to allocate, must be
     * > 0.
     */
    explicit Vector3Array(int size);

    /**
     * Copy constructor.
     *
     * @param other The object to copy.
     */
    Vector3Array(const Vector3Array& other);

    /**
     * Copy assignment operator. Uses a fast block copy if
     * <code>size() == other.size()</code>.
     *
     * @param other The object to assign to <code>*this</code>.
     *
     * @return Reference to <code>*this</code>.
     */
    Vector3Array& operator =(const Vector3Array& other);

    /**
     * Array access operator.
     *
     * @param i Index of the <code>Vector3</code> object to return, between
     * [0, <code>size()</code>).
     *
     * @return Reference to the specified <code>Vector3</code> object.
     */
    Vector3& operator [](int index);

    /**
     * Provided for const-correctness.
     *
     * @see operator [](int)
     */
    const Vector3 operator [](int index) const;

    /**
     * Gets a pointer to stored element data. The stored <code>Vector3</code>
     * objects and their components are guaranteed to be tightly packed,
     * without any padding bytes between.
     *
     * @return Pointer to stored element data.
     */
    Vector3* data();

    /**
     * Provided for const-correctness.
     *
     * @see data()
     */
    const Vector3* data() const;

    /**
     * Gets a pointer to stored component data. The stored <code>Vector3</code>
     * objects and their components are guaranteed to be tightly packed,
     * without any padding bytes between.
     *
     * @return Pointer to stored component data.
     */
    float* componentData();

    /**
     * Provided for const-correctness.
     *
     * @see componentData()
     */
    const float* componentData() const;

    /**
     * Gets an iterator pointing to the first element.
     *
     * @return An iterator pointing to the first element.
     */
    Iterator begin();

    /**
     * Provided for const-correctness.
     *
     * @see begin()
     */
    ConstIterator begin() const;

    /**
     * Gets an iterator pointing one element beyond the the last element.
     *
     * @return An iterator pointing one element beyond the the last element.
     */
    Iterator end();

    /**
     * Provided for const-correctness.
     *
     * @see end()
     */
    ConstIterator end() const;

    /**
     * Gets the number of stored <code>Vector3</code> objects.
     *
     * @return The number of stored <code>Vector3</code> objects.
     */
    int size() const;

    /**
     * Calculates the smallest axis-aligned bounding box that contains all
     * stored points.
     *
     * @return The smallest axis-aligned bounding box that contains all stored
     * points.
     */
    const Extents3 extents() const;

    /**
     * Calculates the smallest axis-aligned bounding box that contains all
     * stored points transformed by a given transform. The extents are
     * calculated from transformed point data, producing the tightest possible
     * axis-aligned bounding box.
     *
     * @param transform The transform to use in calculating the extents.
     *
     * @return The smallest axis-aligned bounding box that contains all stored
     * points transformed by the given transform.
     */
    const Extents3 extents(const Transform3& transform) const;

    /**
     * Applies a given transform to all <code>Vector3</code> objects in this
     * array.
     *
     * @param transform The transform to apply.
     */
    void transformBy(const Transform3& transform);

    /**
     * Applies a given translation to all <code>Vector3</code> objects in this
     * array.
     *
     * @param translation The translation to apply.
     */
    void translateBy(const Vector3& translation);

    /**
     * Applies a given rotation to all <code>Vector3</code> objects in this
     * array.
     *
     * @param rotation The rotation to apply, must be a valid rotation matrix.
     */
    void rotateBy(const Matrix3x3& rotation);

    /**
     * Applies a given scaling to all <code>Vector3</code> objects in this
     * array.
     *
     * @param scaling The scaling to apply, must be > 0.
     */
    void scaleBy(float scaling);

    /**
     * Sets all stored <code>Vector3</code> objects.
     *
     * @param v The <code>Vector3</code> object to fill this array with.
     */
    void fill(const Vector3& v);

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(Vector3Array& other);

private:
    Vector3* vertices_; ///< The stored <code>Vector3</code> objects.
    int size_;          ///< Number of stored <code>Vector3</code> objects.
};

#endif // #ifndef GEOMETRY_VECTOR3ARRAY_H_INCLUDED
