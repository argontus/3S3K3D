/**
 * @file graphics/nodevisitors/pointlitgeometryquery.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_NODEVISITORS_POINTLITGEOMETRYQUERY_H_INCLUDED
#define GRAPHICS_NODEVISITORS_POINTLITGEOMETRYQUERY_H_INCLUDED

#include <vector>

#include <geometry/sphere.h>

#include <graphics/nodevisitors/nodevisitor.h>

class PointLitGeometryQuery : public NodeVisitor
{
public:
    virtual ~PointLitGeometryQuery();

    PointLitGeometryQuery();

    void reset();
    void init(const Sphere& effectSphere);

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

    Sphere effectSphere_;
    std::vector<MeshNode*> meshNodes_;

    // prevent copying
    PointLitGeometryQuery(const PointLitGeometryQuery&);
    PointLitGeometryQuery& operator =(const PointLitGeometryQuery&);
};

#endif // #ifndef GRAPHICS_NODEVISITORS_POINTLITGEOMETRYQUERY_H_INCLUDED
