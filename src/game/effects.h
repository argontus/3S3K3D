/**
 * @file game/effects.h
 * @author Mika Haarahiltunen
 */

#ifndef GAME_EFFECTS_H_INCLUDED
#define GAME_EFFECTS_H_INCLUDED

class Vector3;

class Effect;
class ProgramManager;
class Texture;

Effect* createExtentsEffect(ProgramManager* programMgr);
Effect* createShadowEffect(ProgramManager* programMgr);

Effect* createParticleEffect(
    ProgramManager* programMgr,
    Texture* particleTexture);

Effect* createDGNSTextureMeshEffect(
    ProgramManager* programMgr,
    Texture* diffuseMap,
    Texture* glowMap,
    Texture* normalMap,
    Texture* specularMap,
    float specularExponent);

Effect* createNoTextureMeshEffect(
    ProgramManager* programMgr,
    const Vector3& ambientColor,
    const Vector3& diffuseColor,
    const Vector3& glowColor,
    const Vector3& specularColor,
    float specularExponent);

#endif // #ifndef GAME_EFFECTS_H_INCLUDED
