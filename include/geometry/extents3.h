/**
 * @file geometry/extents3.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_EXTENTS3_H_INCLUDED
#define GEOMETRY_EXTENTS3_H_INCLUDED

#include <geometry/vector3.h>

class Interval;
class Line3;
class Sphere;
class Transform3;

/**
 * Describes 3D extents.
 */
class Extents3
{
public:
    // compiler-generated destructor, copy constructor and assignment operator
    // are fine

    /**
     * Default constructor, constructs empty extents.
     */
    Extents3();

    /**
     * Constructor.
     *
     * @param min The minimum extents.
     * @param max The maximum extents.
     */
    Extents3(const Vector3& min, const Vector3& max);

    // TODO: type of *In can be Vector3 or Extents3, document it
    /**
     * Constructor, constructs extents containing all items in the range
     * [<code>first</code>, <code>last</code>).
     *
     * @param first Iterator pointing to the first item to enclose.
     * @param last Iterator pointing one beyond the last item to enclose.
     */
    template <class In>
    Extents3(In first, In last);

    /**
     * Makes <code>*this</code> empty.
     */
    void clear();

    /**
     * Grows the extents to enclose point <code>q</code>.
     *
     * @param q The point to enclose.
     */
    void enclose(const Vector3& q);

    /**
     * Grows the extents to enclose <code>other</code>. If <code>other</code>
     * is empty, this member function does nothing.
     *
     * @param other The extents to enclose.
     */
    void enclose(const Extents3& other);

    // TODO: type of *In can be Vector3 or Extents3, document it
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
    bool contains(const Extents3& other) const;

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(Extents3& other);

    Vector3 min;    ///< The minimum extents.
    Vector3 max;    ///< The maximum extents.
};

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
bool intersect(const Extents3& a, const Extents3& b);

/**
 * Tests if <code>a</code> and <code>b</code> intersect.
 *
 * @param a Extents.
 * @param b A sphere.
 *
 * @return <code>true</code>, if <code>a</code> and <code>b</code> intersect,
 * <code>false</code> otherwise. If <code>a</code> is empty, the return value
 * is <code>false</code>.
 */
bool intersect(const Extents3& a, const Sphere& b);

// TODO: comments
bool intersect(
    const Extents3& extents,
    const Line3& line,
    float* tEnterOut,
    float* tLeaveOut);

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
const Vector3 closestPoint(const Extents3& x, const Vector3& q);

/**
 * Calculates the interval of <code>x</code> along <code>axis</code>. If
 * <code>x</code> is empty, the returned interval will be empty.
 *
 * @param x The extents whose interval is to be calculated.
 * @param axis The axis along which the interval is to be calculated.
 *
 * @return The calculated interval.
 */
const Interval interval(const Extents3& x, const Vector3& axis);

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
const Extents3 transform(const Extents3& x, const Transform3& t);

template <class In>
Extents3::Extents3(const In first, const In last)
{
    clear();
    enclose(first, last);
}

template <class In>
void Extents3::enclose(In first, const In last)
{
    while (first != last)
    {
        enclose(*first);
        ++first;
    }
}

#endif // #ifndef GEOMETRY_EXTENTS3_H_INCLUDED
