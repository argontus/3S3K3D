/**
 * @file graphics/rendertarget.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/rendertarget.h>

RenderTarget::~RenderTarget()
{
    // ...
}

void RenderTarget::setDrawOrder(const int drawOrder)
{
    drawOrder_ = drawOrder;
}

int RenderTarget::drawOrder() const
{
    return drawOrder_;
}

RenderTarget::RenderTarget()
:   drawOrder_(0)
{
    // ...
}
