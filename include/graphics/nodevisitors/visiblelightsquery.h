/**
 * @file graphics/nodevisitors/visiblelightsquery.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_NODEVISITORS_VISIBLELIGHTSQUERY_H_INCLUDED
#define GRAPHICS_NODEVISITORS_VISIBLELIGHTSQUERY_H_INCLUDED

#include <vector>

#include <graphics/visibilitytest.h>
#include <graphics/nodevisitors/nodevisitor.h>

class VisibleLightsQuery : public NodeVisitor
{
public:
    virtual ~VisibleLightsQuery();

    VisibleLightsQuery();

    void reset();
    void init(const CameraNode& camera);

    // TODO: ...

    /**
     * @name NodeVisitor Interface
     */
    //@{
    virtual bool visit(CameraNode*);
    virtual bool visit(MeshNode*);
    virtual bool visit(Node*);
    //@}

private:
    // TODO: ...

    // prevent copying
    VisibleLightsQuery(const VisibleLightsQuery&);
    VisibleLightsQuery& operator =(const VisibleLightsQuery&);
};

#endif // #ifndef GRAPHICS_NODEVISITORS_VISIBLELIGHTSQUERY_H_INCLUDED
