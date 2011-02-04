/**
 * @file graphics/colorarray.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_COLORARRAY_H_INCLUDED
#define GRAPHICS_COLORARRAY_H_INCLUDED

class Color;

/**
 * Represents a fixed size array of <code>Color</code> objects.
 */
class ColorArray
{
public:
    /**
     * A random access iterator.
     */
    typedef Color* Iterator;

    /**
     * A random access constant iterator.
     */
    typedef const Color* ConstIterator;

    /**
     * Destructor.
     */
    ~ColorArray();

    /**
     * Constructor, does not initialize the constructed colors.
     *
     * @param size Number of <code>Color</code> objects to allocate, must be >
     * 0.
     */
    explicit ColorArray(int size);

    /**
     * Copy constructor.
     *
     * @param other The object to copy.
     */
    ColorArray(const ColorArray& other);

    /**
     * Copy assignment operator. Uses a fast block copy if
     * <code>size() == other.size()</code>.
     *
     * @param other The object to assign to <code>*this</code>.
     *
     * @return Reference to <code>*this</code>.
     */
    ColorArray& operator=(const ColorArray& other);

    /**
     * Array access operator.
     *
     * @param i Index of the <code>Color</code> object to return, between
     * [0, <code>size()</code>).
     *
     * @return Reference to the specified <code>Color</code> object.
     */
    Color& operator [](int index);

    /**
     * Provided for const-correctness.
     *
     * @see operator [](int)
     */
    const Color operator [](int index) const;

    /**
     * Gets a pointer to stored element data. The stored <code>Color</code>
     * objects and their components are guaranteed to be tightly packed,
     * without any padding bytes between.
     *
     * @return Pointer to stored element data.
     */
    Color* data();

    /**
     * Provided for const-correctness.
     *
     * @see data()
     */
    const Color* data() const;

    /**
     * Gets a pointer to stored component data. The stored <code>Color</code>
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
     * Gets the number of stored <code>Color</code> objects.
     *
     * @return The number of stored <code>Color</code> objects.
     */
    int size() const;

    /**
     * Sets all stored <code>Color</code> objects.
     *
     * @param c The <code>Color</code> object to fill this array with.
     */
    void fill(const Color& c);

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(ColorArray& other);

private:
    Color* colors_; ///< The stored <code>Color</code> objects.
    int size_;      ///< Number of stored <code>Color</code> objects.

};

#endif // #ifndef GRAPHICS_COLORARRAY_H_INCLUDED
