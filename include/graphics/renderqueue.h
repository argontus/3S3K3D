/**
 * @file graphics/renderqueue.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_RENDERQUEUE_H_INCLUDED
#define GRAPHICS_RENDERQUEUE_H_INCLUDED

#include <vector>

class DrawParams;
class GeometryNode;
class GroupNode;

/**
 * Represents a sorted render queue.
 */
class RenderQueue
{
public:
    /**
     * Destructor.
     */
    ~RenderQueue();

    // TODO: initial capacity
    /**
     * Default constructor.
     */
    RenderQueue();

    /**
     * Adds a given geometry node to this render queue.
     *
     * @param p The geometry node to add, cannot be a null pointer.
     */
    void addGeometryNode(const GeometryNode* p);

    /**
     * Gets a geometry node by index.
     *
     * @param index Index of the geometry node to return, must be between
     * [<code>0</code>, numGeometryNodes()<code></code>).
     *
     * @return The specified geometry node.
     *
     * @see numGeometryNodes() const
     */
    const GeometryNode* geometryNode(int index) const;

    /**
     * Gets the number of geometry nodes in this render queue.
     *
     * @return The number of geometry nodes in this render queue.
     */
    int numGeometryNodes() const;

    /**
     * Adds a given group node to this render queue. Visible group node
     * tracking is needed for drawing the visible group node extents.
     *
     * @param p The group node to add, cannot be a null pointer.
     */
    void addGroupNode(const GroupNode* p);

    /**
     * Gets a group node by index.
     *
     * @param index Index of the group node to return, must be between
     * [<code>0</code>, numGroupNodes()<code></code>).
     *
     * @return The specified group node.
     *
     * @see numGroupNodes() const
     */
    const GroupNode* groupNode(int index) const;

    /**
     * Gets the number of group nodes in this render queue.
     *
     * @return The number of group nodes in this render queue.
     */
    int numGroupNodes() const;

    /**
     * Clears the geometry node and group node lists of this render queue.
     */
    void clear();

    /**
     * Draws all geometry nodes in this render queue. The caller is responsible
     * ensuring that this render queue has been sorted before this member
     * function is called. Drawing an unsorted render queue may result in loss
     * of performance and produce incorrect visual results.
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

private:
    /**
     * Comparison function used for sorting the render queue geometry nodes.
     *
     * @param a Pointer to a geometry node.
     * @param b Pointer to a geometry node.
     *
     * @return <code>true</code>, if <code></code> is strictly 'less' than
     * <code>b</code>, <code>false</code> otherwise.
     */
    static bool compare(const GeometryNode* a, const GeometryNode* b);

    typedef std::vector<const GeometryNode*> GeometryNodeVector;
    typedef std::vector<const GroupNode*> GroupNodeVector;

    GeometryNodeVector geometryNodes_;  ///< Geometry nodes.
    GroupNodeVector groupNodes_;        ///< Group nodes.

    // prevent copying
    RenderQueue(const RenderQueue&);
    RenderQueue& operator =(const RenderQueue&);
};

#endif // #ifndef GRAPHICS_RENDERQUEUE_H_INCLUDED
