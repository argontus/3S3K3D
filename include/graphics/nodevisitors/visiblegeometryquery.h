/**
 * @file graphics/nodevisitors/visiblegeometryquery.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_NODEVISITORS_VISIBLEGEOMETRYQUERY_H_INCLUDED
#define GRAPHICS_NODEVISITORS_VISIBLEGEOMETRYQUERY_H_INCLUDED

#include <vector>

#include <graphics/visibilitytest.h>
#include <graphics/nodevisitors/nodevisitor.h>

class VisibleGeometryQuery : public NodeVisitor
{
public:
    virtual ~VisibleGeometryQuery();

    VisibleGeometryQuery();

    // clears the result vectors, maintains capacity
    void clear();

    /**
     * @name NodeVisitor Interface
     */
    //@{
    // TODO: try these as an optimization when FSP can be compared
    //virtual void pushState();
    //virtual void popState();
    virtual bool visit(CameraNode*);
    virtual bool visit(MeshNode*);
    virtual bool visit(Node*);
    //@}

    // TODO: use a separate class for querying debug info such as nodes that
    // are used only in rendering extents, e.g., VisibleExtentsQuery

    VisibilityTest test;
    std::vector<MeshNode*> meshNodes;
    std::vector<Node*> otherNodes;

private:
    bool visitOther(Node* p);

    // TODO: try these as an optimization when FSP can be compared

    /**
     * Is the visibility test used? The visibility test is disabled for all
     * descendant nodes of a node whose subtree extents are completely within
     * the view frustum.
     */
    //bool testVisibility_;

    /**
     * Depth from the first node that was completely inside the view frustum.
     */
    //int depth_;

    // prevent copying
    VisibleGeometryQuery(const VisibleGeometryQuery&);
    VisibleGeometryQuery& operator =(const VisibleGeometryQuery&);
};

#endif // #ifndef GRAPHICS_NODEVISITORS_VISIBLEGEOMETRYQUERY_H_INCLUDED
