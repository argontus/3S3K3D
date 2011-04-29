/**
 * @file graphics/nodevisitors/segmentmeshintersectionquery.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_NODEVISITORS_SEGMENTMESHINTERSECTIONQUERY_H_INCLUDED
#define GRAPHICS_NODEVISITORS_SEGMENTMESHINTERSECTIONQUERY_H_INCLUDED

#include <geometry/line3.h>

#include <graphics/nodevisitors/nodevisitor.h>

class LineSegment3;

class SegmentMeshIntersectionQuery : public NodeVisitor
{
public:
    virtual ~SegmentMeshIntersectionQuery();

    SegmentMeshIntersectionQuery();

    void init(const LineSegment3& segment);

    MeshNode* meshNode() const;
    float tEnter() const;

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

    Line3 line_;
    MeshNode* meshNode_;
    float tEnter_;

    // prevent copying
    SegmentMeshIntersectionQuery(const SegmentMeshIntersectionQuery&);
    SegmentMeshIntersectionQuery& operator =(const SegmentMeshIntersectionQuery&);
};

#endif // #ifndef GRAPHICS_NODEVISITORS_SEGMENTMESHINTERSECTIONQUERY_H_INCLUDED
