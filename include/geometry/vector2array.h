/**
 * @file geometry/vector2array.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_VECTOR2ARRAY_H_INCLUDED
#define GEOMETRY_VECTOR2ARRAY_H_INCLUDED

#include <geometry/extents2.h>

/**
 * Represents a fixed size array of <code>Vector2</code> objects.
 */
class Vector2Array
{
public:
    /**
     * A random access iterator.
     */
    typedef Vector2* Iterator;

    /**
     * A random access constant iterator.
     */
    typedef const Vector2* ConstIterator;

    /**
     * Destructor.
     */
    ~Vector2Array();

    /**
     * Constructor, does not initialize the constructed vectors.
     *
     * @param size Number of <code>Vector2</code> objects to allocate, must be
     * > 0.
     */
    explicit Vector2Array(int size);

    /**
     * Copy constructor.
     *
     * @param other The object to copy.
     */
    Vector2Array(const Vector2Array& other);

    /**
     * Copy assignment operator. Uses a fast block copy if
     * <code>size() == other.size()</code>.
     *
     * @param other The object to assign to <code>*this</code>.
     *
     * @return Reference to <code>*this</code>.
     */
    Vector2Array& operator =(const Vector2Array& other);

    /**
     * Array access operator.
     *
     * @param i Index of the <code>Vector2</code> object to return, between
     * [0, <code>size()</code>).
     *
     * @return Reference to the specified <code>Vector2</code> object.
     */
    Vector2& operator [](int index);

    /**
     * Provided for const-correctness.
     *
     * @see operator [](int)
     */
    const Vector2 operator [](int index) const;

    /**
     * Gets a pointer to stored element data. The stored <code>Vector2</code>
     * objects and their components are guaranteed to be tightly packed,
     * without any padding bytes between.
     *
     * @return Pointer to stored element data.
     */
    Vector2* data();

    /**
     * Provided for const-correctness.
     *
     * @see data()
     */
    const Vector2* data() const;

    /**
     * Gets a pointer to stored component data. The stored <code>Vector2</code>
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
     * Gets the number of stored <code>Vector2</code> objects.
     *
     * @return The number of stored <code>Vector2</code> objects.
     */
    int size() const;

    /**
     * Calculates the smallest axis-aligned bounding rectangle that contains
     * all stored points.
     *
     * @return The smallest axis-aligned bounding rectangle that contains all
     * stored points.
     */
    const Extents2 extents() const;

    /**
     * Calculates the smallest axis-aligned bounding rectangle that contains
     * all stored points transformed by a given transform. The extents are
     * calculated from transformed point data, producing the tightest possible
     * axis-aligned bounding rectangle.
     *
     * @param transform The transform to use in calculating the extents.
     *
     * @return The smallest axis-aligned bounding rectangle that contains all
     * stored points transformed by the given transform.
     */
    const Extents2 extents(const Transform2& transform) const;

    /**
     * Applies a given transform to all <code>Vector2</code> objects in this
     * array.
     *
     * @param transform The transform to apply.
     */
    void transformBy(const Transform2& transform);

    /**
     * Applies a given translation to all <code>Vector2</code> objects in this
     * array.
     *
     * @param translation The translation to apply.
     */
    void translateBy(const Vector2& translation);

    /**
     * Applies a given rotation to all <code>Vector2</code> objects in this
     * array.
     *
     * @param rotation The rotation to apply, must be a valid rotation matrix.
     */
    void rotateBy(const Matrix2x2& rotation);

    /**
     * Applies a given scaling to all <code>Vector2</code> objects in this
     * array.
     *
     * @param scaling The scaling to apply.
     */
    void scaleBy(float scaling);

    /**
     * Sets all stored <code>Vector2</code> objects.
     *
     * @param v The <code>Vector2</code> object to fill this array with.
     */
    void fill(const Vector2& v);

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(Vector2Array& other);

private:
    Vector2* vertices_; ///< The stored <code>Vector2</code> objects.
    int size_;          ///< Number of stored <code>Vector2</code> objects.
};

#endif // #ifndef GEOMETRY_VECTOR2ARRAY_H_INCLUDED
