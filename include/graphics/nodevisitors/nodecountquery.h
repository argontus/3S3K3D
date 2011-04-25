/**
 * @file graphics/nodevisitors/nodecountquery.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_NODEVISITORS_NODECOUNTQUERY_H_INCLUDED
#define GRAPHICS_NODEVISITORS_NODECOUNTQUERY_H_INCLUDED

#include <graphics/nodevisitors/nodevisitor.h>

class NodeCountQuery : public NodeVisitor
{
public:
    virtual ~NodeCountQuery();

    NodeCountQuery();

    void reset();

    int numCameraNodes() const;
    int numMeshNodes() const;
    int numNodes() const;
    int numPointLightNodes() const;
    int total() const;

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
    int numCameraNodes_;        ///< Number of CameraNode objects.
    int numMeshNodes_;          ///< Number of MeshNode objects.
    int numNodes_;              ///< Number of Node objects.
    int numPointLightNodes_;    ///< Number of PointLightNode objects.

    // prevent copying
    NodeCountQuery(const NodeCountQuery&);
    NodeCountQuery& operator =(const NodeCountQuery&);
};

#endif // GRAPHICS_NODEVISITORS_NODECOUNTQUERY_H_INCLUDED
