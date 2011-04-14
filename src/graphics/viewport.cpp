/**
 * @file graphics/viewport.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/viewport.h>

#include <geometry/math.h>

Viewport::Viewport()
:   area_(0.0f, 0.0f, 1.0f, 1.0f),
    clearColor_(0.0f, 0.0f, 0.0f, 0.0f),
    clearEnabled_(true),
    zIndex_(0),
    camera_(0),
    rootNode_(0)
{
    // ...
}

void Viewport::setArea(const RectangleF& area)
{
    area_.x = Math::clamp(area.x, 0.0f, 1.0f);
    area_.y = Math::clamp(area.y, 0.0f, 1.0f);
    area_.width = Math::clamp(area.width, 0.0f, 1.0f - area_.x);
    area_.height = Math::clamp(area.height, 0.0f, 1.0f - area_.y);
}

const RectangleF Viewport::area() const
{
    return area_;
}

void Viewport::setClearColor(const Color4& color)
{
    clearColor_ = clamp(color, 0.0f, 1.0f);
}

const Color4 Viewport::clearColor() const
{
    return clearColor_;
}

void Viewport::setClearEnabled(const bool enabled)
{
    clearEnabled_ = enabled;
}

bool Viewport::isClearEnabled() const
{
    return clearEnabled_;
}

void Viewport::setZIndex(const int zIndex)
{
    zIndex_ = zIndex;
}

int Viewport::zIndex() const
{
    return zIndex_;
}

void Viewport::setCamera(Camera* const camera)
{
    camera_ = camera;
}

Camera* Viewport::camera() const
{
    return camera_;
}

void Viewport::setRootNode(Node* const rootNode)
{
    rootNode_ = rootNode;
}

Node* Viewport::rootNode() const
{
    return rootNode_;
}
