/**
 * @file graphics/stencilstate.cpp
 * @author Mika Haarahiltunen
 */

#include <graphics/stencilstate.h>

StencilState::FaceSettings::FaceSettings()
:   compareFunc(CompareFunc::Always),
    reference(0),
    mask(~0),
    writeMask(~0),
    stencilFailAction(Action::Keep),
    depthFailAction(Action::Keep),
    depthPassAction(Action::Keep)
{
    // ...
}

StencilState::StencilState()
:   backFace(),
    frontFace()
{
    // ...
}

void StencilState::setCompareFunc(const CompareFunc::Enum compareFunc)
{
    backFace.compareFunc = compareFunc;
    frontFace.compareFunc = compareFunc;
}

void StencilState::setReference(const GLint reference)
{
    backFace.reference = reference;
    frontFace.reference = reference;
}

void StencilState::setMask(const GLuint mask)
{
    backFace.mask = mask;
    frontFace.mask = mask;
}

void StencilState::setWriteMask(const GLuint mask)
{
    backFace.writeMask = mask;
    frontFace.writeMask = mask;
}

void StencilState::setStencilFailAction(const Action::Enum action)
{
    backFace.stencilFailAction = action;
    frontFace.stencilFailAction = action;
}

void StencilState::setDepthFailAction(const Action::Enum action)
{
    backFace.depthFailAction = action;
    frontFace.depthFailAction = action;
}

void StencilState::setDepthPassAction(const Action::Enum action)
{
    backFace.depthPassAction = action;
    frontFace.depthPassAction = action;
}
