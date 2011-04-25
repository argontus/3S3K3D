/**
 * @file graphics/nodevisitors/visiblelightsquery.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/nodevisitors/visiblelightsquery.h>

#include <geometry/sphere.h>

#include <graphics/runtimeassert.h>
#include <graphics/nodes/cameranode.h>
#include <graphics/nodes/meshnode.h>
#include <graphics/nodes/pointlightnode.h>

VisibleLightsQuery::~VisibleLightsQuery()
{
    // ...
}

VisibleLightsQuery::VisibleLightsQuery()
:   NodeVisitor(),
    test_(),
    pointLightNodes_()
{
    // ...
}

void VisibleLightsQuery::reset()
{
    pointLightNodes_.clear();
}

void VisibleLightsQuery::init(const CameraNode& camera)
{
    test_.init(camera);
}

PointLightNode* VisibleLightsQuery::pointLightNode(const int index) const
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < numPointLightNodes());
    return pointLightNodes_[index];
}

int VisibleLightsQuery::numPointLightNodes() const
{
    return pointLightNodes_.size();
}

bool VisibleLightsQuery::visit(CameraNode* const p)
{
    return visitOther(p);
}

bool VisibleLightsQuery::visit(MeshNode* const p)
{
    return visitOther(p);
}

bool VisibleLightsQuery::visit(Node* const p)
{
    return visitOther(p);
}

bool VisibleLightsQuery::visit(PointLightNode* const p)
{
    if (p->isSubtreeVisible() == false)
    {
        return false;
    }

    if (p->isVisible())
    {
        // light effect sphere
        const Sphere s(p->worldTransform().translation, p->lightRange());

        if (test_.test(s) != VisibilityState::Invisible)
        {
            pointLightNodes_.push_back(p);
        }
    }

    return true;
}

bool VisibleLightsQuery::visitOther(Node* const p)
{
    return p->isSubtreeVisible();
}
