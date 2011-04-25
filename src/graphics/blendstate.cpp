/**
 * @file graphics/blendstate.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/blendstate.h>

const BlendState* BlendState::additive()
{
    static bool initialized = false;
    static BlendState state;

    if (initialized == false)
    {
        state.setEquation(Equation::Add);
        state.setSrcFactor(SrcFactor::One);
        state.setDstFactor(DstFactor::One);
        state.enabled = true;
        state.blendColor = Color4(0.0f, 0.0f, 0.0f, 0.0f);

        initialized = true;
    }

    return &state;
}

const BlendState* BlendState::additiveBlend()
{
    static bool initialized = false;
    static BlendState state;

    if (initialized == false)
    {
        state.setEquation(Equation::Add);
        state.setSrcFactor(SrcFactor::SrcAlpha);
        state.setDstFactor(DstFactor::One);
        state.enabled = true;
        state.blendColor = Color4(0.0f, 0.0f, 0.0f, 0.0f);

        initialized = true;
    }

    return &state;
}

const BlendState* BlendState::disabled()
{
    static bool initialized = false;
    static BlendState state;

    if (initialized == false)
    {
        state.setEquation(Equation::Add);
        state.setSrcFactor(SrcFactor::One);
        state.setDstFactor(DstFactor::Zero);
        state.enabled = false;
        state.blendColor = Color4(0.0f, 0.0f, 0.0f, 0.0f);

        initialized = true;
    }

    return &state;
}

const BlendState* BlendState::translucent()
{
    static bool initialized = false;
    static BlendState state;

    if (initialized == false)
    {
        state.setEquation(Equation::Add);
        state.setSrcFactor(SrcFactor::SrcAlpha);
        state.setDstFactor(DstFactor::OneMinusSrcAlpha);
        state.enabled = true;
        state.blendColor = Color4(0.0f, 0.0f, 0.0f, 0.0f);

        initialized = true;
    }

    return &state;
}

BlendState::BlendState()
:   enabled(false),
    colorEquation(Equation::Add),
    alphaEquation(Equation::Add),
    srcColorFactor(SrcFactor::One),
    srcAlphaFactor(SrcFactor::One),
    dstColorFactor(DstFactor::Zero),
    dstAlphaFactor(DstFactor::Zero),
    blendColor(0.0f, 0.0f, 0.0f, 0.0f)
{
    // ...
}

void BlendState::setEquation(const Equation::Enum equation)
{
    colorEquation = equation;
    alphaEquation = equation;
}

void BlendState::setSrcFactor(const SrcFactor::Enum factor)
{
    srcColorFactor = factor;
    srcAlphaFactor = factor;
}

void BlendState::setDstFactor(const DstFactor::Enum factor)
{
    dstColorFactor = factor;
    dstAlphaFactor = factor;
}
