/**
 * @file graphics/stenciltestsettings.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/stenciltestsettings.h>

#include <algorithm>

// StencilTestFaceSettings implementation

StencilTestFaceSettings::StencilTestFaceSettings()
:   compareFunc(StencilTestCompareFunc::Always),
    reference(0),
    mask(0xFFFFFFFF),
    stencilFailAction(StencilTestAction::Keep),
    depthFailAction(StencilTestAction::Keep),
    depthPassAction(StencilTestAction::Keep)
{
    // ...
}

void StencilTestFaceSettings::swap(StencilTestFaceSettings& other)
{
    std::swap(compareFunc, other.compareFunc);
    std::swap(reference, other.reference);
    std::swap(mask, other.mask);
    std::swap(stencilFailAction, other.stencilFailAction);
    std::swap(depthFailAction, other.depthFailAction);
    std::swap(depthPassAction, other.depthPassAction);
}

// StencilTestSettings implementation

StencilTestSettings::StencilTestSettings()
:   enabled(false),
    backFaceSettings(),
    frontFaceSettings()
{
    // ...
}

void StencilTestSettings::setCompareFunc(const StencilTestCompareFunc::Enum compareFunc)
{
    backFaceSettings.compareFunc = compareFunc;
    frontFaceSettings.compareFunc = compareFunc;
}

void StencilTestSettings::setReference(const int32_t reference)
{
    backFaceSettings.reference = reference;
    frontFaceSettings.reference = reference;
}

void StencilTestSettings::setMask(const uint32_t mask)
{
    backFaceSettings.mask = mask;
    frontFaceSettings.mask = mask;
}

void StencilTestSettings::setStencilFailAction(const StencilTestAction::Enum action)
{
    backFaceSettings.stencilFailAction = action;
    frontFaceSettings.stencilFailAction = action;
}

void StencilTestSettings::setDepthFailAction(const StencilTestAction::Enum action)
{
    backFaceSettings.depthFailAction = action;
    frontFaceSettings.depthFailAction = action;
}

void StencilTestSettings::setDepthPassAction(const StencilTestAction::Enum action)
{
    backFaceSettings.depthPassAction = action;
    frontFaceSettings.depthPassAction = action;
}

void StencilTestSettings::swap(StencilTestSettings& other)
{
    std::swap(enabled, other.enabled);
    backFaceSettings.swap(other.backFaceSettings);
    frontFaceSettings.swap(other.frontFaceSettings);
}
