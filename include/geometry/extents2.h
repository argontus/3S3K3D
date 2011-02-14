/**
 * @file geometry/extents2.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_EXTENTS2_H_INCLUDED
#define GEOMETRY_EXTENTS2_H_INCLUDED

#include <geometry/vector2.h>

class Interval;
class Matrix2x2;
class Transform2;

// TODO: better encapsulation?
/**
 * Describes a 2D axis-aligned bounding rectangle (AABR).
 */
class Extents2
{
public:
    // compiler-generated destructor, copy constructor and copy assignment
    // operator are fine

    /**
     * Default constructor, constructs an empty AABR. The minimum extents are
     * set to <code>std::numeric_limits<float>::max()</code> and the maximum
     * extents are set to <code>-std::numeric_limits<float>::max()</code>.
     */
    Extents2();

    /**
     * Constructor.
     *
     * @param xMin Minimum x-coordinate extent.
     * @param yMin Minimum y-coordinate extent.
     * @param xMax Maximum x-coordinate extent.
     * @param yMax Maximum y-coordinate extent.
     */
    Extents2(float xMin, float yMin, float xMax, float yMax);

    /**
     * Constructor.
     *
     * @param min The minimum extents.
     * @param max The maximum extents.
     */
    Extents2(const Vector2& min, const Vector2& max);

    /**
     * Makes <code>*this</code> empty. The minimum extents are set to
     * <code>std::numeric_limits<float>::max()</code> and the maximum extents
     * are set to <code>-std::numeric_limits<float>::max()</code>.
     */
    void clear();

    /**
     * Tests if <code>*this</code> is empty. An AABR is considered empty if its
     * maximum extents are less than its minimum extents on one or both axes.
     *
     * @return <code>true</code>, if <code>*this</code> is empty,
     * <code>false</code> otherwise.
     */
    bool isEmpty() const;

    /**
     * Gets the AABR length along x-axis. The return value is equivalent to
     * <code>max.x - min.x</code>.
     *
     * @return AABR length along x-axis.
     */
    float xLength() const;

    /**
     * Gets the AABR length along y-axis. The return value is equivalent to
     * <code>max.y - min.y</code>.
     *
     * @return AABR length along y-axis.
     */
    float yLength() const;

    /**
     * Tests if this AABR contains a given point.
     *
     * @param point The point to test.
     *
     * @return <code>true</code>, if <code>*this</code> contains the given
     * point, <code>false</code> otherwise. If this AABR is empty, the return
     * value is <code>false</code>.
     */
    bool contains(const Vector2& point) const;

    /**
     * Tests if this AABR contains a given AABR.
     *
     * @param other The AABR to test.
     *
     * @return <code>true</code>, if <code>*this</code> contains
     * <code>other</code>, <code>false</code> otherwise. If one or both AABRs
     * are empty, the return value is <code>false</code>.
     */
    bool contains(const Extents2& other) const;

    /**
     * Tests if this AABR intersects a given AABR. Two AABRs are considered
     * intersecting when their penetration depth is greater than zero.
     *
     * @param other The AABR to test.
     *
     * @return <code>true</code>, if <code>*this</code> intersects
     * <code>other</code>, <code>false</code> otherwise. If one or both AABRs
     * are empty, the return value is <code>false</code>.
     */
    bool intersects(const Extents2& other) const;

    /**
     * Grows the extents of this AABR to enclose a given point.
     *
     * @param point The point to enclose.
     */
    void growToContain(const Vector2& point);

    /**
     * Grows the extents of this AABR to enclose a given AABR. If the given
     * AABR is empty, this member function does nothing.
     *
     * @param other The AABR to enclose.
     */
    void growToContain(const Extents2& other);

    /**
     * Calculates the interval of this AABR along a given axis. If this AABR is
     * empty, the returned interval will be empty.
     *
     * @param axis The axis along which the interval is to be calculated.
     *
     * @return The calculated interval.
     */
    const Interval intervalAlong(const Vector2& axis) const;

    /**
     * Applies a tranform to this AABR. <code>*this</code> is set to an AABR
     * that wraps the transformed original AABR. If this AABR is empty, this
     * member function does nothing.
     *
     * @param transform The transform to apply.
     */
    void transformBy(const Transform2& transform);

    /**
     * Applies a translation to this AABR. <code>*this</code> is set to an AABR
     * that wraps the translated original AABR. If this AABR is empty, this
     * member function does nothing.
     *
     * @param translation The translation to apply.
     */
    void translateBy(const Vector2& translation);

    /**
     * Applies a rotation to this AABR. <code>*this</code> is set to an AABR
     * that wraps the rotated original AABR. If this AABR is empty, this member
     * function does nothing.
     *
     * @param rotation The rotation to apply, must be a valid rotation matrix.
     */
    void rotateBy(const Matrix2x2& rotation);

    /**
     * Applies a scaling to this AABR. <code>*this</code> is set to an AABR
     * that wraps the scaled original AABR. If this AABR is empty, this member
     * function does nothing.
     *
     * @param scaling The scaling to apply, must be > 0.
     */
    void scaleBy(float scaling);

    /**
     * Exchanges the contents of <code>*this</code> and <code>other</code>.
     *
     * @param other The object to swap contents with.
     */
    void swap(Extents2& other);

    Vector2 min;    ///< The minimum extents.
    Vector2 max;    ///< The maximum extents.
};

#endif // #ifndef GEOMETRY_EXTENTS2_H_INCLUDED
