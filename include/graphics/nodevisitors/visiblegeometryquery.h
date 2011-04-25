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

    void reset();
    void init(const CameraNode& camera);

    MeshNode* meshNode(int index) const;
    int numMeshNodes() const;

    /**
     * @name NodeVisitor Interface
     */
    //@{
    virtual bool visit(CameraNode*);
    virtual bool visit(MeshNode*);
    virtual bool visit(Node*);
    virtual bool visit(PointLightNode*);
    //@}

private:
    bool visitOther(Node* p);

    VisibilityTest test_;
    std::vector<MeshNode*> meshNodes_;

    // prevent copying
    VisibleGeometryQuery(const VisibleGeometryQuery&);
    VisibleGeometryQuery& operator =(const VisibleGeometryQuery&);
};

#endif // #ifndef GRAPHICS_NODEVISITORS_VISIBLEGEOMETRYQUERY_H_INCLUDED
