/**
 * @file graphics/rasterizerstate.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/rasterizerstate.h>

const RasterizerState* RasterizerState::cullClockwise()
{
    static const RasterizerState s(
        CullMode::CullClockwise,
        FillMode::Solid
    );

    return &s;
}

const RasterizerState* RasterizerState::cullCounterClockwise()
{
    static const RasterizerState s(
        CullMode::CullCounterClockwise,
        FillMode::Solid
    );

    return &s;
}

const RasterizerState* RasterizerState::cullNone()
{
    static const RasterizerState s(
        CullMode::CullNone,
        FillMode::Solid
    );

    return &s;
}

const RasterizerState* RasterizerState::wireFrame()
{
    static const RasterizerState s(
        CullMode::CullNone,
        FillMode::WireFrame
    );

    return &s;
}

RasterizerState::RasterizerState()
:   cullMode(CullMode::CullClockwise),
    fillMode(FillMode::Solid)
{
    // ...
}

RasterizerState::RasterizerState(
    const CullMode::Enum cullMode,
    const FillMode::Enum fillMode)
:   cullMode(cullMode),
    fillMode(fillMode)
{
    // ...
}
