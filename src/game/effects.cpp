/**
 * @file game/effects.cpp
 * @author Mika Haarahiltunen
 */

#include "effects.h"

#include <graphics/blendstate.h>
#include <graphics/depthstate.h>
#include <graphics/effect.h>
#include <graphics/pass.h>
#include <graphics/programmanager.h>
#include <graphics/rasterizerstate.h>
#include <graphics/runtimeassert.h>
#include <graphics/stencilstate.h>
#include <graphics/technique.h>
#include <graphics/parameters/floatparameter.h>
#include <graphics/parameters/mat3parameter.h>
#include <graphics/parameters/mat4parameter.h>
#include <graphics/parameters/sampler2dparameter.h>
#include <graphics/parameters/vec3parameter.h>

Effect* createExtentsEffect(ProgramManager* const programMgr)
{
    GRAPHICS_RUNTIME_ASSERT(programMgr != 0);

    // TODO: needs rasterizer state

    Effect* const effect = new Effect("extentsEffect", 1);

    Technique* const technique = new Technique("default", 1);
    effect->setTechnique(0, technique);

    Pass* pass = new Pass("pass0", 2);
    technique->setPass(0, pass);
    pass->setBlendState(BlendState::disabled());
    pass->setDepthState(DepthState::lessEqual());
    pass->setRasterizerState(RasterizerState::wireFrame());
    pass->setStencilState(StencilState::disabled());
    pass->setProgram(programMgr->load("data/shaders/extents.vs", "data/shaders/extents.fs"));
    pass->setParameter(0, new Mat4Parameter("modelViewMatrix", Matrix4x4::identity()));
    pass->setParameter(1, new Mat4Parameter("projectionMatrix", Matrix4x4::identity()));

    return effect;
}

Effect* createShadowEffect(ProgramManager* const programMgr)
{
    GRAPHICS_RUNTIME_ASSERT(programMgr != 0);

    // TODO: needs rasterizer state

    // workaround in the absence of color masks
    static BlendState blendState;
    blendState.setEquation(BlendState::Equation::Add);
    blendState.setSrcFactor(BlendState::SrcFactor::Zero);
    blendState.setDstFactor(BlendState::DstFactor::One);
    blendState.enabled = true;

    // stencil test settings for the depth fail shadow volume algorithm
    static StencilState stencilState;
    stencilState.setCompareFunc(StencilState::CompareFunc::Always);
    stencilState.setReference(0);
    stencilState.setMask(~0);
    stencilState.setWriteMask(~0);
    stencilState.setStencilFailAction(StencilState::Action::Keep);
    stencilState.setDepthPassAction(StencilState::Action::Keep);
    stencilState.enabled = true;
    stencilState.backFace.depthFailAction = StencilState::Action::IncrementWrap;
    stencilState.frontFace.depthFailAction = StencilState::Action::DecrementWrap;

    Effect* const effect = new Effect("shadowEffect", 2);

    Technique* const singlePassTechnique = new Technique("singlePass", 1);
    effect->setTechnique(0, singlePassTechnique);

    Pass* pass = new Pass("pass0", 2);
    singlePassTechnique->setPass(0, pass);
    //pass->setBlendState(BlendState::disabled());
    pass->setBlendState(&blendState);
    pass->setDepthState(DepthState::lessEqualReadOnly());
    pass->setRasterizerState(RasterizerState::cullNone());
    pass->setStencilState(&stencilState);
    pass->setProgram(programMgr->load("data/shaders/shadow.vs", "data/shaders/shadow.fs"));
    pass->setParameter(0, new Mat4Parameter("modelViewMatrix", Matrix4x4::identity()));
    pass->setParameter(1, new Mat4Parameter("projectionMatrix", Matrix4x4::identity()));

    Technique* const wireframeTechnique = new Technique("wireframe", 1);
    effect->setTechnique(1, wireframeTechnique);

    pass = new Pass("pass0", 2);
    wireframeTechnique->setPass(0, pass);
    pass->setBlendState(BlendState::disabled());
    pass->setDepthState(DepthState::lessEqualReadOnly());
    pass->setRasterizerState(RasterizerState::wireFrame());
    pass->setStencilState(StencilState::disabled());
    pass->setProgram(programMgr->load("data/shaders/shadow.vs", "data/shaders/shadow.fs"));
    pass->setParameter(0, new Mat4Parameter("modelViewMatrix", Matrix4x4::identity()));
    pass->setParameter(1, new Mat4Parameter("projectionMatrix", Matrix4x4::identity()));

    return effect;
}

Effect* createDGNSTextureMeshEffect(
    ProgramManager* const programMgr,
    Texture* const diffuseMap,
    Texture* const glowMap,
    Texture* const normalMap,
    Texture* const specularMap,
    const float specularExponent)
{
    GRAPHICS_RUNTIME_ASSERT(programMgr != 0);
    GRAPHICS_RUNTIME_ASSERT(diffuseMap != 0);
    GRAPHICS_RUNTIME_ASSERT(glowMap != 0);
    GRAPHICS_RUNTIME_ASSERT(normalMap != 0);
    GRAPHICS_RUNTIME_ASSERT(specularMap != 0);

    // TODO: needs rasterizer state

    // stencil test passes if the stencil value equals zero
    static StencilState stencilState;
    stencilState.setCompareFunc(StencilState::CompareFunc::Equal);
    stencilState.setReference(0);
    stencilState.setMask(~0);
    stencilState.setWriteMask(~0);
    stencilState.setStencilFailAction(StencilState::Action::Keep);
    stencilState.setDepthFailAction(StencilState::Action::Keep);
    stencilState.setDepthPassAction(StencilState::Action::Keep);
    stencilState.enabled = true;

    Effect* const effect = new Effect("dgnsTextureMeshEffect", 2);

    Technique* const ambientLightTechnique = new Technique("ambientLight", 1);
    effect->setTechnique(0, ambientLightTechnique);

    Pass* pass = new Pass("pass0", 6);
    ambientLightTechnique->setPass(0, pass);
    pass->setBlendState(BlendState::disabled());
    pass->setDepthState(DepthState::lessEqual());
    pass->setRasterizerState(RasterizerState::cullClockwise());
    pass->setStencilState(StencilState::disabled());
    pass->setProgram(programMgr->load("data/shaders/mesh/dgns_texture/ambient_light.vs", "data/shaders/mesh/dgns_texture/ambient_light.fs"));
    pass->setParameter(0, new Mat4Parameter("modelViewMatrix", Matrix4x4::identity()));
    pass->setParameter(1, new Mat4Parameter("projectionMatrix", Matrix4x4::identity()));
    pass->setParameter(2, new Mat3Parameter("normalMatrix", Matrix3x3::identity()));
    pass->setParameter(3, new Vec3Parameter("ambientLightColor", Vector3::zero()));
    pass->setParameter(4, new Sampler2DParameter("diffuseMap", 0, diffuseMap));
    pass->setParameter(5, new Sampler2DParameter("glowMap", 1, glowMap));

    Technique* const pointLightTechnique = new Technique("pointLight", 1);
    effect->setTechnique(1, pointLightTechnique);

    pass = new Pass("pass0", 10);
    pointLightTechnique->setPass(0, pass);
    pass->setBlendState(BlendState::additive());
    pass->setDepthState(DepthState::lessEqualReadOnly());
    pass->setRasterizerState(RasterizerState::cullClockwise());
    pass->setStencilState(&stencilState);
    pass->setProgram(programMgr->load("data/shaders/mesh/dgns_texture/point_light.vs", "data/shaders/mesh/dgns_texture/point_light.fs"));
    pass->setParameter(0, new Mat4Parameter("modelViewMatrix", Matrix4x4::identity()));
    pass->setParameter(1, new Mat4Parameter("projectionMatrix", Matrix4x4::identity()));
    pass->setParameter(2, new Mat3Parameter("normalMatrix", Matrix3x3::identity()));
    pass->setParameter(3, new Vec3Parameter("lightPosition", Vector3::zero()));
    pass->setParameter(4, new Vec3Parameter("lightColor", Vector3::zero()));
    pass->setParameter(5, new FloatParameter("lightRange", 0.0f));
    pass->setParameter(6, new FloatParameter("specularExponent", specularExponent));
    pass->setParameter(7, new Sampler2DParameter("diffuseMap", 0, diffuseMap));
    pass->setParameter(8, new Sampler2DParameter("specularMap", 1, specularMap));
    pass->setParameter(9, new Sampler2DParameter("normalMap", 2, normalMap));

    return effect;
}

Effect* createNoTextureMeshEffect(
    ProgramManager* const programMgr,
    const Vector3& ambientColor,
    const Vector3& diffuseColor,
    const Vector3& glowColor,
    const Vector3& specularColor,
    const float specularExponent)
{
    GRAPHICS_RUNTIME_ASSERT(programMgr != 0);

    // TODO: needs rasterizer state

    // stencil test passes if the stencil value equals zero
    static StencilState stencilState;
    stencilState.setCompareFunc(StencilState::CompareFunc::Equal);
    stencilState.setReference(0);
    stencilState.setMask(~0);
    stencilState.setWriteMask(~0);
    stencilState.setStencilFailAction(StencilState::Action::Keep);
    stencilState.setDepthFailAction(StencilState::Action::Keep);
    stencilState.setDepthPassAction(StencilState::Action::Keep);
    stencilState.enabled = true;

    Effect* const effect = new Effect("noTextureMeshEffect", 2);

    Technique* const ambientLightTechnique = new Technique("ambientLight", 1);
    effect->setTechnique(0, ambientLightTechnique);

    Pass* pass = new Pass("pass0", 6);
    ambientLightTechnique->setPass(0, pass);
    pass->setBlendState(BlendState::disabled());
    pass->setDepthState(DepthState::lessEqual());
    pass->setRasterizerState(RasterizerState::cullClockwise());
    pass->setStencilState(StencilState::disabled());
    pass->setProgram(programMgr->load("data/shaders/mesh/no_texture/ambient_light.vs", "data/shaders/mesh/no_texture/ambient_light.fs"));
    pass->setParameter(0, new Mat4Parameter("modelViewMatrix", Matrix4x4::identity()));
    pass->setParameter(1, new Mat4Parameter("projectionMatrix", Matrix4x4::identity()));
    pass->setParameter(2, new Mat3Parameter("normalMatrix", Matrix3x3::identity()));
    pass->setParameter(3, new Vec3Parameter("ambientLightColor", Vector3::zero()));
    pass->setParameter(4, new Vec3Parameter("ambientColor", ambientColor));
    pass->setParameter(5, new Vec3Parameter("glowColor", glowColor));

    Technique* const pointLightTechnique = new Technique("pointLight", 1);
    effect->setTechnique(1, pointLightTechnique);

    pass = new Pass("pass0", 9);
    pointLightTechnique->setPass(0, pass);
    pass->setBlendState(BlendState::additive());
    pass->setDepthState(DepthState::lessEqualReadOnly());
    pass->setRasterizerState(RasterizerState::cullClockwise());
    pass->setStencilState(&stencilState);
    pass->setProgram(programMgr->load("data/shaders/mesh/no_texture/point_light.vs", "data/shaders/mesh/no_texture/point_light.fs"));
    pass->setParameter(0, new Mat4Parameter("modelViewMatrix", Matrix4x4::identity()));
    pass->setParameter(1, new Mat4Parameter("projectionMatrix", Matrix4x4::identity()));
    pass->setParameter(2, new Mat3Parameter("normalMatrix", Matrix3x3::identity()));
    pass->setParameter(3, new Vec3Parameter("lightPosition", Vector3::zero()));
    pass->setParameter(4, new Vec3Parameter("lightColor", Vector3::zero()));
    pass->setParameter(5, new FloatParameter("lightRange", 0.0f));
    pass->setParameter(6, new Vec3Parameter("diffuseColor", diffuseColor));
    pass->setParameter(7, new Vec3Parameter("specularColor", specularColor));
    pass->setParameter(8, new FloatParameter("specularExponent", specularExponent));

    return effect;
}
