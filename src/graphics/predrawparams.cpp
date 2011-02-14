/**
 * @file graphics/predrawparams.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/predrawparams.h>

#include <algorithm>

PredrawParams::PredrawParams()
:   renderQueue_(0),
    visibilityTest_(0)
{
    // ...
}

void PredrawParams::setRenderQueue(RenderQueue* const p)
{
    renderQueue_ = p;
}

RenderQueue* PredrawParams::renderQueue() const
{
    return renderQueue_;
}

void PredrawParams::setVisibilityTest(VisibilityTest* const p)
{
    visibilityTest_ = p;
}

VisibilityTest* PredrawParams::visibilityTest() const
{
    return visibilityTest_;
}

void PredrawParams::swap(PredrawParams& other)
{
    std::swap(renderQueue_, other.renderQueue_);
    std::swap(visibilityTest_, other.visibilityTest_);
}
