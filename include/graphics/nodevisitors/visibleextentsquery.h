/**
 * @file graphics/nodevisitors/visibleextentsquery.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_NODEVISITORS_VISIBLEEXTENTSQUERY_H_INCLUDED
#define GRAPHICS_NODEVISITORS_VISIBLEEXTENTSQUERY_H_INCLUDED

#include <vector>

#include <geometry/extents3.h>

#include <graphics/visibilitytest.h>
#include <graphics/nodevisitors/nodevisitor.h>

class VisibleExtentsQuery : public NodeVisitor
{
public:
    virtual ~VisibleExtentsQuery();

    VisibleExtentsQuery();

    void reset();
    void init(const CameraNode& camera);

    const Extents3 extents(int index) const;
    int numExtents() const;

    /**
     * @name NodeVisitor Interface
     */
    //@{
    virtual bool visit(CameraNode*);
    virtual bool visit(MeshNode*);
    virtual bool visit(Node*);
    //@}

private:
    void addNonEmptyExtents(const Extents3& x);
    bool visitImpl(Node* p);

    VisibilityTest test_;
    std::vector<Extents3> extents_;

    // prevent copying
    VisibleExtentsQuery(const VisibleExtentsQuery&);
    VisibleExtentsQuery& operator =(const VisibleExtentsQuery&);
};

#endif // #ifndef GRAPHICS_NODEVISITORS_VISIBLEEXTENTSQUERY_H_INCLUDED
