/**
 * @file geometry/interval.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_INTERVAL_H_INCLUDED
#define GEOMETRY_INTERVAL_H_INCLUDED

/**
 * Represents a bounded interval.
 */
class Interval
{
public:
    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

    /**
     * Default constructor, constructs an empty interval.
     */
    Interval();

    /**
     * Constructor.
     *
     * @param min The minimum extent.
     * @param max The maximum extent.
     */
    Interval(float min, float max);

    // TODO: type of *In can be float or Interval, document it
    /**
     * Constructor, constructs an interval containing all items in the range
     * [<code>first</code>, <code>last</code>).
     *
     * @param first Iterator pointing to the first item to enclose.
     * @param last Iterator pointing one beyond the last item to enclose.
     */
    template <class In>
    Interval(In first, In last);

    /**
     * Makes <code>*this</code> empty.
     */
    void clear();

    /**
     * Grows the extents to enclose <code>k</code>.
     *
     * @param k The value to enclose.
     */
    void enclose(float k);

    /**
     * Grows the extents to enclose <code>other</code>. If <code>other</code>
     * is empty, this member function does nothing.
     *
     * @param other The interval to enclose.
     */
    void enclose(const Interval& other);

    // TODO: type of *In can be float or Interval, document it
    /**
     * Grows the extents to enclose all items in the range [<code>first</code>,
     * <code>last</code>).
     *
     * @param first Iterator pointing to the first item to enclose.
     * @param last Iterator pointing one beyond the last item to enclose.
     */
    template <class In>
    void enclose(In first, In last);

    /**
     * Tests if <code>*this</code> is empty. <code>*this</code> is considered
     * empty if the maximum extent is less than the minimum extent.
     *
     * @return <code>true</code>, if <code>*this</code> is empty,
     * <code>false</code> otherwise.
     */
    bool isEmpty() const;

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(Interval& other);

    float min;  ///< The minimum extent.
    float max;  ///< The maximum extent.
};

template <class In>
Interval::Interval(const In first, const In last)
{
    clear();
    enclose(first, last);
}

template <class In>
void Interval::enclose(In first, const In last)
{
    while (first != last)
    {
        enclose(*first);
        ++first;
    }
}

#endif // #ifndef GEOMETRY_INTERVAL_H_INCLUDED
