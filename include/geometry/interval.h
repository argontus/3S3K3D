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
    // compiler-generated destructor, copy constructor and copy assignment
    // operator are fine

    /**
     * Default constructor, constructs an empty interval. The minimum extent is
     * set to <code>std::numeric_limits<float>::max()</code> and the maximum
     * extent is set to <code>-std::numeric_limits<float>::max()</code>.
     */
    Interval();

    /**
     * Constructor.
     *
     * @param min The minimum extent.
     * @param max The maximum extent.
     */
    Interval(float min, float max);

    /**
     * Makes this interval an empty interval. The minimum extent is set to
     * <code>std::numeric_limits<float>::max()</code> and the maximum extent is
     * set to <code>-std::numeric_limits<float>::max()</code>.
     */
    void clear();

    /**
     * Tests if this interval is empty. An interval is considered empty if its
     * maximum extent is less than its minimum extent.
     *
     * @return <code>true</code>, if this interval is empty, <code>false</code>
     * otherwise.
     */
    bool isEmpty() const;

    /**
     * Gets the interval length.
     *
     * @return Interval length. The return value is equivalent to
     * <code>max - min</code>.
     */
    float length() const;

    /**
     * Tests if this interval contains a given value. A value is considered
     * contained if it is between [<code>min</code>, <code>max</code>].
     *
     * @param value The value to test.
     *
     * @return <code>true</code>, if <code>*this</code> contains the given
     * value, <code>false</code> otherwise. If this interval is empty, the
     * return value is <code>false</code>.
     */
    bool contains(float value) const;

    /**
     * Tests if this interval contains a given interval. An interval is
     * considered contained if the its minimum extent is greater than or equal
     * to the minimum extent of this interval and its maximum extent is less
     * than or equal to the maximum extent of this interval.
     *
     * @param other The interval to test.
     *
     * @return <code>true</code>, if <code>*this</code> contains
     * <code>other</code>, <code>false</code> otherwise. If one or both
     * intervals are empty, the return value is <code>false</code>.
     */
    bool contains(const Interval& other) const;

    /**
     * Tests if this interval intersects a given interval. An interval is
     * considered intersecting if its minimum extent is less than the maximum
     * extent of this interval and its maximum extent is greater than the
     * minimum extent of this interval.
     *
     * @param other The interval to test.
     *
     * @return <code>true</code>, if <code>*this</code> intersects
     * <code>other</code>, <code>false</code> otherwise. If one or both
     * intervals are empty, the return value is <code>false</code>.
     */
    bool intersects(const Interval& other) const;

    /**
     * Grows the extents of this interval to enclose a given value.
     *
     * @param value The value to enclose.
     */
    void growToContain(float value);

    /**
     * Grows the extents of this interval to enclose a given interval. If the
     * given interval is empty, this member function does nothing.
     *
     * @param other The interval to enclose.
     */
    void growToContain(const Interval& other);

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(Interval& other);

    float min;  ///< The minimum extent.
    float max;  ///< The maximum extent.
};

#endif // #ifndef GEOMETRY_INTERVAL_H_INCLUDED
