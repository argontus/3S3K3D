/**
 * @file geometry/extents2.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_EXTENTS2_H_INCLUDED
#define GEOMETRY_EXTENTS2_H_INCLUDED

#include <geometry/vector2.h>

class Circle;
class Interval;
class Transform2;

/**
 * Describes 2D extents.
 */
class Extents2
{
public:
    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

    /**
     * Default constructor, constructs empty extents.
     */
    Extents2();

    /**
     * Constructor.
     *
     * @param min The minimum extents.
     * @param max The maximum extents.
     */
    Extents2(const Vector2& min, const Vector2& max);

    // TODO: type of *In can be Vector2 or Extents2, document it
    /**
     * Constructor, constructs extents containing all items in the range
     * [<code>first</code>, <code>last</code>).
     *
     * @param first Iterator pointing to the first item to enclose.
     * @param last Iterator pointing one beyond the last item to enclose.
     */
    template <class In>
    Extents2(In first, In last);

    /**
     * Makes <code>*this</code> empty.
     */
    void clear();

    /**
     * Grows the extents to enclose point <code>q</code>.
     *
     * @param q The point to enclose.
     */
    void enclose(const Vector2& q);

    /**
     * Grows the extents to enclose <code>other</code>. If <code>other</code>
     * is empty, this member function does nothing.
     *
     * @param other The extents to enclose.
     */
    void enclose(const Extents2& other);

    // TODO: type of *In can be Vector2 or Extents2, document it
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
     * empty if the maximum extent is less than the minimum extent on at least
     * one axis.
     *
     * @return <code>true</code>, if <code>*this</code> is empty,
     * <code>false</code> otherwise.
     */
    bool isEmpty() const;

    /**
     * Tests if <code>*this</code> contains <code>other</code>.
     *
     * @param other The extents to test.
     *
     * @return <code>true</code>, if <code>*this</code> contains
     * <code>other</code>, <code>false</code> otherwise.
     */
    bool contains(const Extents2& other) const;

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(Extents2& other);

    Vector2 min;    ///< The minimum extents.
    Vector2 max;    ///< The maximum extents.
};

/**
 * Tests if <code>a</code> and <code>b</code> intersect.
 *
 * @param a Extents.
 * @param b A circle.
 *
 * @return <code>true</code>, if <code>a</code> and <code>b</code> intersect,
 * <code>false</code> otherwise. If <code>a</code> is empty, the return value
 * is <code>false</code>.
 */
bool intersect(const Extents2& a, const Circle& b);

/**
 * Tests if <code>a</code> and <code>b</code> intersect.
 *
 * @param a Extents.
 * @param b Extents.
 *
 * @return <code>true</code>, if <code>a</code> and <code>b</code> intersect,
 * <code>false</code> otherwise. If <code>a</code>, <code>b</code> or both are
 * empty, the return value is <code>false</code>.
 */
bool intersect(const Extents2& a, const Extents2& b);

/**
 * Calculates the point on or in extents <code>x</code> that is closest to
 * point <code>q</code>.
 *
 * @param x Extents, cannot be empty.
 * @param q A point.
 *
 * @return The point on or in extents <code>x</code> that is closest to point
 * <code>q</code>.
 */
const Vector2 closestPoint(const Extents2& x, const Vector2& q);

/**
 * Calculates the interval of <code>x</code> along <code>axis</code>. If
 * <code>x</code> is empty, the returned interval will be empty.
 *
 * @param x The extents whose interval is to be calculated.
 * @param axis The axis along which the interval is to be calculated.
 *
 * @return The calculated interval.
 */
const Interval interval(const Extents2& x, const Vector2& axis);

/**
 * Transforms <code>x</code> by <code>t</code>. The returned extents wraps the
 * transformed <code>x</code>. If <code>x</code> is empty, the return value is
 * equivalent to <code>x</code>.
 *
 * @param x The extents to transform.
 * @param t The transform to apply.
 *
 * @return The transformed extents.
 */
const Extents2 transform(const Extents2& x, const Transform2& t);

template <class In>
Extents2::Extents2(const In first, const In last)
{
    clear();
    enclose(first, last);
}

template <class In>
void Extents2::enclose(In first, const In last)
{
    while (first != last)
    {
        enclose(*first);
        ++first;
    }
}

#endif // #ifndef GEOMETRY_EXTENTS2_H_INCLUDED
