/**
 * @file graphics/blendstate.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/blendstate.h>

BlendState::BlendState()
:   colorEquation(Equation::Add),
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
