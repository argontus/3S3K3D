/**
 * @file graphics/nodevisitors/nodevisitor.h
 * @author Mika Haarahiltunen
 */

#ifndef GRAPHICS_NODEVISITORS_NODEVISITOR_H_INCLUDED
#define GRAPHICS_NODEVISITORS_NODEVISITOR_H_INCLUDED

class CameraNode;
class MeshNode;
class Node;
// TODO: add more node types when they are implemented

// TODO: rename this to Visitor?
class NodeVisitor
{
public:
    virtual ~NodeVisitor() {}

    // TODO: try these as an optimization when FSP can be compared
    //virtual void pushState() {}
    //virtual void popState() {}

    // parameter cannot be a null pointer, returns true if child nodes should
    // be visited
    virtual bool visit(CameraNode*) { return true; }
    virtual bool visit(MeshNode*) { return true; }
    virtual bool visit(Node*) { return true; }
    // TODO: add more node types when they are implemented

protected:
    NodeVisitor() {}

private:
    // prevent copying
    NodeVisitor(const NodeVisitor&);
    NodeVisitor& operator =(const NodeVisitor&);
};

#endif // #ifndef GRAPHICS_NODEVISITORS_NODEVISITOR_H_INCLUDED
