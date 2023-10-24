#pragma once
#include "MagicHitEffect.hpp"
#include "ParticleShaderProperty.hpp"

class EffectShaderProperty;

class MagicShaderHitEffect : public MagicHitEffect {
public:
	MagicShaderHitEffect();
	~MagicShaderHitEffect();

	bool unk28;
	UInt32 unk2C;
	TESEffectShader* effectShader;
	float time34;					// 34	Init'd to float
	BSSimpleArray<NiPointer<ParticleShaderProperty>>	unk38;
	NiNode* shaderNode;
	bool isVisible;
	BSSimpleArray<NiPointer<NiAVObject>> objects;
	float flt60;
	float flt64;
	EffectShaderProperty* effectProperty;
};
static_assert(sizeof(MagicShaderHitEffect) == 0x6C);

/*
// 6C
class MagicShaderHitEffect : public MagicHitEffect
{
public:
MagicShaderHitEffect();
~MagicShaderHitEffect();

UInt8					unk28;						// 28	Init'd to byte, OK for first offset.
UInt8					pad29[3];
UInt32					unk2C;						// 2C	Init'd to DWord
TESEffectShader* effectShader;				// 30	Init'd to *effectShader
float					unk34;						// 34	Init'd to float
BSSimpleArray<NiPointer<ParticleShaderProperty>>	unk38;	// 38	Init'd to BSSimpleArray<NiPointer<ParticleShaderProperty>>
// the remainder is not validated..
void* textureEffectData;		// 48 seen TextureEffectData< BSSahderLightingProperty >, init'd to RefNiObject
};	// Alloc'd to 6C, 68 is RefNiObject, 60 is Init'd to 1.0, 64 also
// 4C is byte, Init'd to 0 for non player, otherwize = Player.1stPersonSkeleton.Flags0030.Bit0 is null
*/