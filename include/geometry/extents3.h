/**
 * @file geometry/extents3.h
 * @author Mika Haarahiltunen
 */

#ifndef GEOMETRY_EXTENTS3_H_INCLUDED
#define GEOMETRY_EXTENTS3_H_INCLUDED

#include <geometry/vector3.h>

class Interval;
class Matrix3x3;
class Transform3;

// TODO: better encapsulation?
/**
 * Describes a 3D axis-aligned bounding box (AABB).
 */
class Extents3
{
public:
    // compiler-generated destructor, copy constructor and copy assignment
    // operator are fine

    /**
     * Default constructor, constructs an empty AABB. The minimum extents are
     * set to <code>std::numeric_limits<float>::max()</code> and the maximum
     * extents are set to <code>-std::numeric_limits<float>::max()</code>.
     */
    Extents3();

    /**
     * Constructor.
     *
     * @param xMin Minimum x-coordinate extent.
     * @param yMin Minimum y-coordinate extent.
     * @param zMin Minimum z-coordinate extent.
     * @param xMax Maximum x-coordinate extent.
     * @param yMax Maximum y-coordinate extent.
     * @param zMax Maximum z-coordinate extent.
     */
    Extents3(
        float xMin, float yMin, float zMin,
        float xMax, float yMax, float zMax);

    /**
     * Constructor.
     *
     * @param min The minimum extents.
     * @param max The maximum extents.
     */
    Extents3(const Vector3& min, const Vector3& max);

    /**
     * Makes <code>*this</code> empty. The minimum extents are set to
     * <code>std::numeric_limits<float>::max()</code> and the maximum extents
     * are set to <code>-std::numeric_limits<float>::max()</code>.
     */
    void clear();

    /**
     * Tests if <code>*this</code> is empty. An AABB is considered empty if its
     * maximum extents are less than its minimum extents on one or more axes.
     *
     * @return <code>true</code>, if <code>*this</code> is empty,
     * <code>false</code> otherwise.
     */
    bool isEmpty() const;

    /**
     * Gets the AABB length along x-axis. The return value is equivalent to
     * <code>max.x - min.x</code>.
     *
     * @return AABB length along x-axis.
     */
    float xLength() const;

    /**
     * Gets the AABB length along y-axis. The return value is equivalent to
     * <code>max.y - min.y</code>.
     *
     * @return AABB length along y-axis.
     */
    float yLength() const;

    /**
     * Gets the AABB length along z-axis. The return value is equivalent to
     * <code>max.z - min.z</code>.
     *
     * @return AABB length along z-axis.
     */
    float zLength() const;

    /**
     * Tests if this AABB contains a given point.
     *
     * @param point The point to test.
     *
     * @return <code>true</code>, if <code>*this</code> contains the given
     * point, <code>false</code> otherwise. If this AABB is empty, the return
     * value is <code>false</code>.
     */
    bool contains(const Vector3& point) const;

    /**
     * Tests if this AABB contains a given AABB.
     *
     * @param other The AABB to test.
     *
     * @return <code>true</code>, if <code>*this</code> contains
     * <code>other</code>, <code>false</code> otherwise. If one or both AABBs
     * are empty, the return value is <code>false</code>.
     */
    bool contains(const Extents3& other) const;

    /**
     * Tests if this AABB intersects a given AABB. Two AABBs are considered
     * intersecting when their penetration depth is greater than zero.
     *
     * @param other The AABB to test.
     *
     * @return <code>true</code>, if <code>*this</code> intersects
     * <code>other</code>, <code>false</code> otherwise. If one or both AABBs
     * are empty, the return value is <code>false</code>.
     */
    bool intersects(const Extents3& other) const;

    /**
     * Grows the extents of this AABB to enclose a given point.
     *
     * @param point The point to enclose.
     */
    void growToContain(const Vector3& point);

    /**
     * Grows the extents of this AABB to enclose a given AABB. If the given
     * AABB is empty, this member function does nothing.
     *
     * @param other The AABB to enclose.
     */
    void growToContain(const Extents3& other);

    /**
     * Calculates the interval of this AABB along a given axis. If this AABB is
     * empty, the returned interval will be empty.
     *
     * @param axis The axis along which the interval is to be calculated.
     *
     * @return The calculated interval.
     */
    const Interval intervalAlong(const Vector3& axis) const;

    /**
     * Applies a tranform to this AABB. <code>*this</code> is set to an AABB
     * that wraps the transformed original AABB. If this AABB is empty, this
     * member function does nothing.
     *
     * @param transform The transform to apply.
     */
    void transformBy(const Transform3& transform);

    /**
     * Applies a translation to this AABB. <code>*this</code> is set to an AABB
     * that wraps the translated original AABB. If this AABB is empty, this
     * member function does nothing.
     *
     * @param translation The translation to apply.
     */
    void translateBy(const Vector3& translation);

    /**
     * Applies a rotation to this AABB. <code>*this</code> is set to an AABB
     * that wraps the rotated original AABB. If this AABB is empty, this member
     * function does nothing.
     *
     * @param rotation The rotation to apply, must be a valid rotation matrix.
     */
    void rotateBy(const Matrix3x3& rotation);

    /**
     * Applies a scaling to this AABB. <code>*this</code> is set to an AABB
     * that wraps the scaled original AABB. If this AABB is empty, this member
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
    void swap(Extents3& other);

    Vector3 min;    ///< The minimum extents.
    Vector3 max;    ///< The maximum extents.
};

#endif // #ifndef GEOMETRY_EXTENTS3_H_INCLUDED
