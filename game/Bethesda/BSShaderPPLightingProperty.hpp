#pragma once

#include "BSShaderLightingProperty.hpp"
#include "EffectShaderProperty.hpp"
#include "BSShaderTextureSet.hpp"
#include "NiPoint4.hpp"
#include "TangentSpaceData.hpp"
#include "NiBinaryExtraData.hpp"

class NiSourceTexture;
class BSShaderAccumulator;
class Lighting30ShaderProperty;

NiSmartPointer(BSShaderPPLightingProperty);

class BSShaderPPLightingProperty : public BSShaderLightingProperty {
public:
	BSShaderPPLightingProperty();
	virtual ~BSShaderPPLightingProperty();

	virtual void							CopyTo3(Lighting30ShaderProperty* apTarget);
	virtual void							CopyProperties(BSShaderProperty* apTarget);
	virtual void							SetupLandscape(NiGeometry* apGeometry);
	virtual void							Unk_53();
	virtual void							PickClampMode(UInt32 auiMode);
	virtual NiTexturingProperty::ClampMode	GetClampMode();
	virtual void							SetClampMode(NiTexturingProperty::ClampMode aeClamp);
	virtual UInt16							GetLandscapeTextureCount();
	virtual int								GetLandPassCount();
	virtual void							SetTexture(BSTextureSet::TextureSlots aeTextureSlot, UInt32 auiTextureNumber, NiTexture* apTexture);
	virtual NiTexture*						GetTexture(BSTextureSet::TextureSlots aeTextureSlot, UInt32 auiTextureNumber);
	virtual void							Unk_61();
	virtual void							SetDiffuseTexture(int, NiTexture* apTexture);
	virtual void							SetNormalTexture(int, NiTexture* apTexture);
	virtual void							SetGlowMask();
	virtual void							SetSpecular();
	virtual float							GetSpecularFade();
	virtual float							GetEnvMapFade();
	virtual void							AddPassesOld(NiGeometry* apGeometry, UInt32 aeEnabledPasses, WORD* apusPassCount, UInt32 eRenderMode, BSShaderAccumulator* apShaderAccum, NiTListItem<ShadowSceneLight>* a4);
	virtual void							AddPasses(NiGeometry* apGeometry, UInt32 aeEnabledPasses, WORD* apusPassCount, UInt32 eRenderMode, BSShaderAccumulator* apShaderAccum, int a4);

	struct Unk0C4 {
		char cUnk0[10];
	};

	UInt32									unk07C;
	UInt32									unk080;
	NiColorA								kHairTint;
	NiColorA								kLandBlendParams;
	BSShaderTextureSetPtr					spTextureSet;
	UInt16									usLandscapeTextures;
	NiTexturePtr*							ppTextures[6];
	BSShaderPPLightingProperty::Unk0C4*		ptr0C4;
	UInt16									usLandPassCount;
	BSShaderPPLightingProperty::Unk0C4*		pbTextureIsSpecular;
	TangentSpaceDataPtr						spTangentSpaceData;
	SInt8*									pcTexturePercents;
	NiTexturingProperty::ClampMode			eClampMode;
	EffectShaderPropertyPtr					spTexEffectData;
	float									fRefractionStrength;
	UInt32									iRefractionFirePeriod;
	float									fParallaxMaxPasses;
	float									fParallaxScale;
	NiPoint4								kLODTextureParams;
	BSRenderPass*							pDepthPass;

	CREATE_OBJECT(BSShaderPPLightingProperty, 0xB68D50);

	NiTexture* GetDiffuse(UInt32 auID = 0)		{ return ppTextures[BSTextureSet::BSSM_Diffuse][auID]; };
	NiTexture* GetNormal(UInt32 auID = 0);
	NiTexture* GetGlow(UInt32 auID = 0)			{ return ppTextures[BSTextureSet::BSSM_Glow][auID]; };
	NiTexture* GetParallax(UInt32 auID = 0)		{ return ppTextures[BSTextureSet::BSSM_Parallax][auID]; };
	NiTexture* GetCubeMap(UInt32 auID = 0)		{ return ppTextures[BSTextureSet::BSSM_CubeMap][auID]; };
	NiTexture* GetEnvMask(UInt32 auID = 0)		{ return ppTextures[BSTextureSet::BSSM_EnvMask][auID]; };

	static UInt16 __fastcall GetNumberOfPassesEx(BSShaderPPLightingProperty* apThis, void*, NiGeometry* apGeometry);
	Lighting30ShaderProperty* ConvertTo30Shader(NiGeometry* apGeometry);
	static Lighting30ShaderProperty* __fastcall ConvertTo30Shader_Hook(BSShaderPPLightingProperty* apThis, void*, NiGeometry* apGeometry, void*, void*);

	BSShaderProperty::RenderPassList* AddWaterDepthPass(NiGeometry* apGeometry);

	static bool __fastcall SetupGeometryEx(BSShaderPPLightingProperty* apThis, void*, NiGeometry* apGeometry);
	static BSShaderProperty::RenderPassList* __fastcall GetRenderPassesEx(BSShaderPPLightingProperty* apThis, void*, NiGeometry* apGeometry, UInt32 auiEnabledPasses, WORD* pusPassCount, UInt32 aeRenderMode, BSShaderAccumulator* apAccumulator, int a7);
	static void __fastcall GetViewerStringsEx(BSShaderPPLightingProperty* apThis, void*, NiViewerStringsArray* apStrings);

};

ASSERT_SIZE(BSShaderPPLightingProperty, 0x104);