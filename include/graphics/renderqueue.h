/**
 * @file graphics/renderqueue.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_RENDERQUEUE_H_INCLUDED
#define GRAPHICS_RENDERQUEUE_H_INCLUDED

#include <vector>

class DrawParams;
class GeometryNode;

// TODO: no need to make this a singleton
/**
 * Represents a sorted render queue. This class is a singleton for maintaining
 * the render queue capacity.
 */
class RenderQueue
{
public:
    /**
     * Gets a reference to the <code>RenderQueue</code> singleton instance.
     *
     * @return Reference to the <code>RenderQueue</code> singleton instance.
     */
    static RenderQueue& instance();

    /**
     * A random access iterator.
     */
    typedef std::vector<const GeometryNode*>::iterator Iterator;

    /**
     * A random access constant iterator.
     */
    typedef std::vector<const GeometryNode*>::const_iterator ConstIterator;

    /**
     * Destructor.
     */
    ~RenderQueue();

    /**
     * Array access operator.
     *
     * @param i Index of the render queue item object to return, between
     * [0, <code>size()</code>).
     *
     * @return The specified render queue item.
     */
    const GeometryNode* operator [](int index) const;

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
     * Draws this render queue.
     *
     * @param params Draw parameters.
     *
     * @see sort()
     */
    void draw(const DrawParams& params) const;

    /**
     * Sorts the render queue contents. This member function should be called
     * once after the predraw step is complete, that is, before the render
     * queue contents are drawn.
     */
    void sort();

    /**
     * Gets the number of items in this render queue.
     *
     * @return The number of items in this render queue.
     *
     * @see isEmpty() const
     */
    int size() const;

    /**
     * Gets a boolean value indicating whether or not this render queue is
     * empty.
     *
     * @return <code>true</code>, if this render queue is empty,
     * <code>false</code> otherwise.
     */
    bool isEmpty() const;

    /**
     * Removes all items from this render queue.
     */
    void clear();

    /**
     * Appends a given geometry node to this render queue.
     *
     * @param p The geometry node to append, cannot be a null pointer.
     */
    void append(const GeometryNode* p);

private:
    /**
     * Default constructor.
     */
    RenderQueue();

    /**
     * Comparison function used for sorting the render queue.
     *
     * @param A render queue item.
     * @param A render queue item.
     *
     * @return <code>true</code>, if <code></code> is strictly 'less' than
     * <code>b</code>, <code>false</code> otherwise.
     */
    static bool compare(const GeometryNode* a, const GeometryNode* b);

    typedef std::vector<const GeometryNode*> GeometryNodeVector;

    GeometryNodeVector items_;  ///< Render queue items.

    // prevent copying
    RenderQueue(const RenderQueue&);
    RenderQueue& operator =(const RenderQueue&);
};

#endif // #ifndef GRAPHICS_RENDERQUEUE_H_INCLUDED
