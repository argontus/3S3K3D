/**
 * @file graphics/nodecontrollers/lightfadeoutcontroller.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/nodecontrollers/lightfadeoutcontroller.h>

#include <graphics/runtimeassert.h>
#include <graphics/nodes/pointlightnode.h>

LightFadeOutController::~LightFadeOutController()
{
    // ...
}

LightFadeOutController::LightFadeOutController(
    const float life,
    const Vector3& color)
:   NodeController(),
    life_(life),
    lifeMax_(life),
    color_(color)
{
    // ...
}

LightFadeOutController* LightFadeOutController::clone() const
{
    return new LightFadeOutController(*this);
}

NodeController::UpdateMessage::Enum LightFadeOutController::update(
    Node* const node,
    const float dt)
{
    life_ -= dt;

    if (life_ <= 0.0f)
    {
        return UpdateMessage::Die;
    }
    else
    {
        // use a power function for a smooth fade out effect, runs from 0 to 1
        const float t = 1.0f - (life_ * life_) / (lifeMax_ * lifeMax_);

        const Vector3 color = mix(color_, Vector3::zero(), t);
        static_cast<PointLightNode*>(node)->setLightColor(color);

        return UpdateMessage::None;
    }
}

LightFadeOutController::LightFadeOutController(const LightFadeOutController& other)
:   NodeController(other),
    life_(other.life_),
    lifeMax_(other.lifeMax_),
    color_(other.color_)
{
    // ...
}
