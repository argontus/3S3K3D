/**
 * @file graphics/blendsettings.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/blendsettings.h>

#include <algorithm>

BlendSettings::BlendSettings()
:   enabled(false),
    blendColor(0.0f, 0.0f, 0.0f, 0.0f),
    colorEquation(BlendEquation::Add),
    alphaEquation(BlendEquation::Add),
    srcColorFactor(SrcBlendFactor::One),
    srcAlphaFactor(SrcBlendFactor::One),
    dstColorFactor(DstBlendFactor::Zero),
    dstAlphaFactor(DstBlendFactor::Zero)
{
    // ...
}

void BlendSettings::setEquation(const BlendEquation::Enum equation)
{
    colorEquation = equation;
    alphaEquation = equation;
}

void BlendSettings::setSrcFactor(const SrcBlendFactor::Enum factor)
{
    srcColorFactor = factor;
    srcAlphaFactor = factor;
}

void BlendSettings::setDstFactor(const DstBlendFactor::Enum factor)
{
    dstColorFactor = factor;
    dstAlphaFactor = factor;
}

void BlendSettings::swap(BlendSettings& other)
{
    std::swap(enabled, other.enabled);
    blendColor.swap(other.blendColor);
    std::swap(colorEquation, other.colorEquation);
    std::swap(alphaEquation, other.alphaEquation);
    std::swap(srcColorFactor, other.srcColorFactor);
    std::swap(srcAlphaFactor, other.srcAlphaFactor);
    std::swap(dstColorFactor, other.dstColorFactor);
    std::swap(dstAlphaFactor, other.dstAlphaFactor);
}
