/**
 * @file graphics/nodevisitors/visibleextentsquery.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/nodevisitors/visibleextentsquery.h>

#include <graphics/runtimeassert.h>
#include <graphics/nodes/cameranode.h>
#include <graphics/nodes/meshnode.h>

VisibleExtentsQuery::~VisibleExtentsQuery()
{
    // ...
}

VisibleExtentsQuery::VisibleExtentsQuery()
:   NodeVisitor(),
    test_(),
    extents_()
{
    // ...
}

void VisibleExtentsQuery::reset()
{
    extents_.clear();
}

void VisibleExtentsQuery::init(const CameraNode& camera)
{
    test_.init(camera);
}

const Extents3 VisibleExtentsQuery::extents(const int index) const
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < numExtents());
    return extents_[index];
}

int VisibleExtentsQuery::numExtents() const
{
    return extents_.size();
}

bool VisibleExtentsQuery::visit(CameraNode* const p)
{
    return visitImpl(p);
}

bool VisibleExtentsQuery::visit(MeshNode* const p)
{
    return visitImpl(p);
}

bool VisibleExtentsQuery::visit(Node* const p)
{
    return visitImpl(p);
}

void VisibleExtentsQuery::addNonEmptyExtents(const Extents3& x)
{
    if (x.isEmpty() == false)
    {
        extents_.push_back(x);
    }
}

bool VisibleExtentsQuery::visitImpl(Node* const p)
{
    if (p->isSubtreeVisible() == false)
    {
        return false;
    }

    VisibilityState::Enum state = test_.test(p->subtreeExtents());

    if (state == VisibilityState::Invisible)
    {
        return false;
    }

    if (p->hasChildren())
    {
        addNonEmptyExtents(p->subtreeExtents());

        if (p->isVisible()
        &&  test_.test(p->extents()) != VisibilityState::Invisible)
        {
            addNonEmptyExtents(p->extents());
        }
    }
    else
    {
        if (p->isVisible())
        {
            addNonEmptyExtents(p->extents());
        }
    }

    return true;
}
