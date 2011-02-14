/**
 * @file graphics/renderqueue.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/renderqueue.h>

#include <algorithm>

#include <graphics/geometrynode.h>
#include <graphics/runtimeassert.h>

RenderQueue::~RenderQueue()
{
    // ...
}

RenderQueue::RenderQueue()
:   geometryNodes_(),
    groupNodes_()
{
    // ...
}

void RenderQueue::addGeometryNode(const GeometryNode* const p)
{
    GRAPHICS_RUNTIME_ASSERT(p != 0);
    geometryNodes_.push_back(p);
}

const GeometryNode* RenderQueue::geometryNode(const int index) const
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < numGeometryNodes());
    return geometryNodes_[index];
}

int RenderQueue::numGeometryNodes() const
{
    return geometryNodes_.size();
}

void RenderQueue::addGroupNode(const GroupNode* const p)
{
    GRAPHICS_RUNTIME_ASSERT(p != 0);
    groupNodes_.push_back(p);
}

const GroupNode* RenderQueue::groupNode(const int index) const
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < numGroupNodes());
    return groupNodes_[index];
}

int RenderQueue::numGroupNodes() const
{
    return groupNodes_.size();
}

void RenderQueue::clear()
{
    // maintains capacity
    geometryNodes_.clear();
    groupNodes_.clear();
}

void RenderQueue::draw(const DrawParams& params) const
{
    for (size_t i = 0; i < geometryNodes_.size(); ++i)
    {
        geometryNodes_[i]->draw(params);
    }
}

void RenderQueue::sort()
{
    std::sort(geometryNodes_.begin(), geometryNodes_.end(), compare);
}

bool RenderQueue::compare(
    const GeometryNode* const a,
    const GeometryNode* const b)
{
    // TODO: ...

    return false;
}
