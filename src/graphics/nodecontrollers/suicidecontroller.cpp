/**
 * @file graphics/nodecontrollers/suicidecontroller.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/nodecontrollers/suicidecontroller.h>

#include <graphics/runtimeassert.h>

SuicideController::~SuicideController()
{
    // ...
}

SuicideController::SuicideController(const float life)
:   NodeController(),
    life_(life)
{
    // ...
}

SuicideController* SuicideController::clone() const
{
    return new SuicideController(*this);
}

NodeController::UpdateMessage::Enum SuicideController::update(
    Node* const,
    const float dt)
{
    life_ -= dt;

    if (life_ <= 0.0f)
    {
        return UpdateMessage::Die;
    }
    else
    {
        return UpdateMessage::None;
    }
}

SuicideController::SuicideController(const SuicideController& other)
:   NodeController(other),
    life_(other.life_)
{
    // ...
}
