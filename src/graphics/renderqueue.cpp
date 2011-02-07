/**
 * @file graphics/renderqueue.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/renderqueue.h>

#include <algorithm>

#include <graphics/geometrynode.h>
#include <graphics/runtimeassert.h>

RenderQueue& RenderQueue::instance()
{
    static RenderQueue singleton;
    return singleton;
}

RenderQueue::~RenderQueue()
{
    // ...
}

const GeometryNode* RenderQueue::operator [](const int index) const
{
    GRAPHICS_RUNTIME_ASSERT(index >= 0 && index < size());
    return items_[index];
}

RenderQueue::Iterator RenderQueue::begin()
{
    return items_.begin();
}

RenderQueue::ConstIterator RenderQueue::begin() const
{
    return items_.begin();
}

RenderQueue::Iterator RenderQueue::end()
{
    return items_.end();
}

RenderQueue::ConstIterator RenderQueue::end() const
{
    return items_.end();
}

void RenderQueue::draw(const DrawParams& params) const
{
    for (size_t i = 0; i < items_.size(); ++i)
    {
        items_[i]->draw(params);
    }
}

void RenderQueue::sort()
{
    std::sort(begin(), end(), compare);
}

int RenderQueue::size() const
{
    return items_.size();
}

bool RenderQueue::isEmpty() const
{
    return items_.empty();
}

void RenderQueue::clear()
{
    items_.clear();
}

void RenderQueue::append(const GeometryNode* const p)
{
    GRAPHICS_RUNTIME_ASSERT(p != 0);
    items_.push_back(p);
}

RenderQueue::RenderQueue()
:   items_()
{
    // ...
}

bool RenderQueue::compare(
    const GeometryNode* const a,
    const GeometryNode* const b)
{
    // TODO: ...
    return false;
}
