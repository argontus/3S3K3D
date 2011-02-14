/**
 * @file graphics/indexarray.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_INDEXARRAY_H_INCLUDED
#define GRAPHICS_INDEXARRAY_H_INCLUDED

#include <stdint.h>

// TODO: is is not used anywhere
/**
 * Represents a fixed size array of <code>uint32_t</code> values.
 */
class IndexArray
{
public:
    /**
     * A random access iterator.
     */
    typedef uint32_t* Iterator;

    /**
     * A random access constant iterator.
     */
    typedef const uint32_t* ConstIterator;

    /**
     * Destructor.
     */
    ~IndexArray();

    /**
     * Constructor, does not initialize the constructed indices.
     *
     * @param size Number of indices to allocate, must be > 0.
     */
    explicit IndexArray(int size);

    /**
     * Copy constructor.
     *
     * @param other The object to copy.
     */
    IndexArray(const IndexArray& other);

    /**
     * Copy assignment operator. Uses a fast block copy if
     * <code>size() == other.size()</code>.
     *
     * @param other The object to assign to <code>*this</code>.
     *
     * @return Reference to <code>*this</code>.
     */
    IndexArray& operator=(const IndexArray& other);

    /**
     * Array access operator.
     *
     * @param i Index of the <code>uint32_t</code> value to return, between
     * [0, <code>size()</code>).
     *
     * @return Reference to the specified <code>uint32_t</code> value.
     */
    uint32_t& operator [](int index);

    /**
     * Provided for const-correctness.
     *
     * @see operator [](int)
     */
    uint32_t operator [](int index) const;

    /**
     * Gets a pointer to stored index array. The stored indices are guaranteed
     * to be tightly packed, without any padding bytes between.
     *
     * @return Pointer to stored index array.
     */
    uint32_t* data();

    /**
     * Provided for const-correctness.
     *
     * @see data()
     */
    const uint32_t* data() const;

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
     * Gets the number of stored indices.
     *
     * @return The number of stored indices.
     */
    int size() const;

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(IndexArray& other);

private:
    uint32_t* indices_; ///< Stored indices.
    int size_;          ///< Number of stored indices.
};

#endif // #ifndef GRAPHICS_INDEXARRAY_H_INCLUDED
