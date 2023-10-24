#pragma once

#include "BSShader.hpp"
#include "NiPoint4.hpp"
#include "NiShaderConstantMapEntry.hpp"

class NiD3DShaderConstantMap;
class BSFogProperty;
class BSShaderPPLightingProperty;

class ShadowLightShader : public BSShader {
public:
	virtual void SetupShadowTexture(RenderPassTypes aeRenderPass, BSShaderPPLightingProperty* apShaderProp);
	virtual void Func_80(); // nullsub
	virtual void InitShaders();
	virtual void InitVertexShaders();
	virtual void InitPixelShaders();
	virtual void CreatePasses();
	virtual void SetToggles(NiGeometry* apGeometry, BSFogProperty* apFogProp, NiMaterialProperty* apMatProp);

	NiDX9ShaderDeclarationPtr	spShaderDeclarationGlowParallaxSkin;
	NiDX9ShaderDeclarationPtr	spShaderDeclarationSkinned;
	NiDX9ShaderDeclarationPtr	spShaderDeclarationModelSpaceNormals;
	NiDX9ShaderDeclarationPtr	spShaderDeclarationLandscape;
	NiD3DShaderConstantMapPtr	spTexEffectPixelConstantMap;
	NiD3DShaderConstantMapPtr	spTexEffectVertexConstantMap;
	NiD3DShaderConstantMapPtr	spPixelConstantMap2;
	NiD3DShaderConstantMapPtr	spVertexConstantMap2;


	__forceinline void SetTexEffectPixelConstantMap(NiD3DShaderConstantMap* apMap) {
		spTexEffectPixelConstantMap = apMap;
	}
	__forceinline NiD3DShaderConstantMap* GetTexEffectPixelConstantMap() {
		return spTexEffectPixelConstantMap;
	}

	__forceinline void SetTexEffectVertexConstantMap(NiD3DShaderConstantMap* apMap) {
		spTexEffectVertexConstantMap = apMap;
	}

	__forceinline NiD3DShaderConstantMap* GetTexEffectVertexConstantMap() {
		return spTexEffectVertexConstantMap;
	}

	static void __fastcall UpdateAmbientColor(ShadowLightShader* apThis, void*, BSShaderPPLightingProperty* pShaderProperty, BSRenderPass* pRenderPass, NiGeometry* pGeometry, NiMaterialProperty* pMaterialProperty);

	static void SetCustomConstant(UInt32 index, float x, float y, float z, float w);

	static __forceinline void SetCameraWorldTranslate(float afX, float afY, float afZ, float afW) {
		NiPoint4* pPos = (NiPoint4*)0x11FA2A0;
		pPos->x = afX;
		pPos->y = afY;
		pPos->z = afZ;
		pPos->w = afW;
	};

	static bool* const bLODNoiseEnabled;
	static bool* const bLODNoiseAniso;
	static float* const fLODNoiseMipBias;

	void SetClamp(NiD3DTextureStage* apTextureStage, BSShaderPPLightingProperty* apShaderProp);
	void SetDiffuseMap(BSShaderPPLightingProperty* apShaderProp, UInt32 auiStageNumber, UInt32 auiTextureNumber);
	void SetNormalMap(BSShaderPPLightingProperty* apShaderProp, UInt32 auiStageNumber, UInt32 auiTextureNumber);
	void SetGlowMap(BSShaderPPLightingProperty* apShaderProp, UInt32 auiStageNumber, UInt32 auiTextureNumber, bool abFallbackTex = true);
	void SetParallaxMap(BSShaderPPLightingProperty* apShaderProp, UInt32 auiStageNumber, UInt32 auiTextureNumber, bool abFallbackTex = true);
	void SetEnvMask(BSShaderPPLightingProperty* apShaderProp, UInt32 auiStageNumber, UInt32 auiTextureNumber);
	void SetCubeMap(BSShaderPPLightingProperty* apShaderProp, UInt32 auiStageNumber, UInt32 auiTextureNumber);
	void SetEffectMap(BSShaderPPLightingProperty* apShaderProp, UInt32 auiStageNumber);
	void SetLandscapeTexture(BSShaderPPLightingProperty* apShaderProp, UInt32 auiStageNumber, bool abSkipNormals);
	void SetShadowMap(UInt32 auiStageNumber);
	void SetLODNoiseMap(UInt32 auiStageNumber);

	void SetLandToggles(BSShaderPPLightingProperty* apShaderProp, UInt32 auiSpecID);
	void UpdateSkinWorldTranspose(NiSkinInstance* apSkinInstance);
	void UpdateTime(BSShaderPPLightingProperty* apShaderProp);
	void UpdateBoundCenter(NiGeometry* pkGeometry);
	void UpdateRefractionStrength(BSShaderPPLightingProperty* apShaderProp);
	void UpdateLODLandParams(BSShaderPPLightingProperty* apShaderProp);
	void UpdateLODTextureParams(BSShaderPPLightingProperty* apShaderProp);


	static void __fastcall UpdateToggles(ShadowLightShader* apThis, void*, RenderPassTypes aeRenderPassType, NiGeometry* apGeo, BSShaderPPLightingProperty* apShaderProp, NiMaterialProperty* apMatProp, BSRenderPass* apRenderPass, NiAlphaProperty* apAlphaProp);
	static void __fastcall SetEmittanceColorForGlowMapMeshes(ShadowLightShader* apThis, void*, NiMaterialProperty* apMatProp);
	static void __fastcall SetAmbientColorForNonGlowMapMeshes(ShadowLightShader* apThis, void*, NiMaterialProperty* apMatProp);

	static bool __fastcall InitializeEx(ShadowLightShader* apThis);
	static void __fastcall RecreateRendererDataEx(ShadowLightShader* apThis);
	static void __fastcall SetRenderPassEx(ShadowLightShader* apThis, void*, RenderPassTypes aeRenderPass);
	static void __fastcall UpdateConstantsEx(ShadowLightShader* apThis, void*, NiPropertyState* apProperties);
	static void __fastcall SetupTexturesEx(ShadowLightShader* apThis, void*, NiPropertyState* apProperties);
	static NiDX9ShaderDeclaration* __fastcall GetShaderDeclarationEx(ShadowLightShader* apThis, void*, NiGeometry* apGeometry, BSShaderProperty* apShaderProp);
	static void __fastcall InitShaderConstantsEx(ShadowLightShader* apThis);
	static void __fastcall ReinitializeEx(ShadowLightShader* apThis);
	static void __fastcall ClearAllTextureStagesEx(ShadowLightShader* apThis);
	static void __fastcall SetupShadowTextureEx(ShadowLightShader* apThis, void*, RenderPassTypes aeRenderPass, BSShaderPPLightingProperty* apShaderProp);
	static void __fastcall InitShadersEx(ShadowLightShader* apThis);
	static void __fastcall InitVertexShadersEx(ShadowLightShader* apThis);
	static void __fastcall InitPixelShadersEx(ShadowLightShader* apThis);
	static bool __fastcall CreatePassesEx(ShadowLightShader* apThis);
	static void __fastcall SetTogglesEx(ShadowLightShader* apThis, void*, NiGeometry* apGeometry, BSFogProperty* apFogProp, NiMaterialProperty* apMatProp);

	static NiD3DVertexShader* GetVertexShader(UInt32 auID);
	static void SetVertexShader(UInt32 auID, NiD3DVertexShader* apShader);

	static NiD3DPixelShader* GetPixelShader(UInt32 auID);
	static void SetPixelShader(UInt32 auID, NiD3DPixelShader* apShader);

	static ShadowLightShader*	GetShader();
	static NiD3DPassPtr*		GetAllPasses();
	static NiD3DPass*			PickPass(RenderPassTypes aeRenderPass);

	enum VertexEntries {
		kVX_WorldViewProjTranspose = 0,
		kVX_WorldTranspose = 1,
		kVX_SkinWorldViewProjTranspose = 2,
		kVX_ShadowProj = 3,
		kVX_ShadowProjData = 4,
		kVX_ShadowProjTransform = 5,
		kVX_LightData = 6,
		kVX_FogParam_ShadowVolumeFatness = 7,
		kVX_FogColor_ShadowVolumeExtrudeDistance = 8,
		kVX_EyePosition = 9,
		kVX_BoneMatrix3 = 10,
		kVX_PrevBoneMatrix3 = 11,
		kVX_SkinWorldTranspose = 12,
		kVX_WorldViewTranspose = 13,
		kVX_SkinWorldViewTranspose = 14,
		kVX_Time = 15,
		kVX_HighDetailRange = 16,
		kVX_BoundCenter = 17,
		kVX_DepthData = 18,
		kVX_PrevWorldViewPT = 19,
		kVX_PrevWorldViewT = 20,
		kVX_LODLandParams = 21,
	};

	enum PixelEntries {
		kPX_EyeDir = 0,
		kPX_AmbientColor = 1,
		kPX_LightColors = 2,
		kPX_EmittanceColor = 3,
		kPX_Toggles = 4,
		kPX_EyePosition = 5,
		kPX_LightDirection = 6,
		kPX_LightPosition0 = 7,
		kPX_LightPosition1 = 8,
		kPX_LightPosition2 = 9,
		kPX_LightPosition3 = 10,
		kPX_HairTint = 15,
		kPX_RefractionParams = 16,
		kPX_FogParams = 17,
		kPX_FogColor = 18,
		kPX_FogPlane = 19,
		kPX_LODTEXPARAMS = 20,
		kPX_STBBColorConstants = 21,
	};

	union Toggles {
		struct {
			float bUseVertexColors;
			float fNormalStrength;
			float fEnvMapScale;
			float fHasMask;
		};

		struct {
			float bUseVertexColors;
			float bUseFog;
			float fSpecularity;
			float fAlphaTestRef;
		};
	};

	static __forceinline NiPoint4* GetConstant(int index) {
		return &((NiPoint4*)0x11FA0C0)[index];
	}

	struct VertexConstants {
		// WorldViewProjTranspose 0
		// SkinWorldViewProjTranspose 1
		// WorldViewTranspose 4
		// SkinWorldViewTranspose 5

		// 8
		static __forceinline D3DMATRIX* const GetWorldTranspose() {
			return (D3DMATRIX*)0x11FECC8;
		}


		// 9
		static D3DMATRIX* const SkinWorldTranspose;

		// 9, map 2
		static __forceinline float* const GetUOffset() {
			return (float*)0x11FD85C;
		}

		// 10, map 2
		static __forceinline float* const GetVOffset() {
			return (float*)0x11FD860;
		}

		// 11, map 2
		static __forceinline float* const GetZScaler() {
			return (float*)0x11FD864;
		}

		// 12
		static __forceinline NiPoint4* const GetHighDetailRange() {
			return GetConstant(34);
		}

		// 13
		static float* const Time;

		// 14 - params, 15 - color
		static __forceinline BSShader::FogProperties* const GetFogParam() {
			return (BSShader::FogProperties*)0x11FA280;
		}

		// 16
		static __forceinline NiPoint4* const GetEyePosition() {
			return (NiPoint4*)0x11FD894;
		}

		// 17
		static __forceinline NiPoint4* const GetDepthData() {
			return (NiPoint4*)0x11FD954;
		}

		// 18
		static __forceinline D3DMATRIX* const GetShadowProj() {
			return (D3DMATRIX*)0x11FD968;
		}

		// 19
		static __forceinline NiPoint4* const GetLODLandParams() {
			return (NiPoint4*)0x11FA0B0;
		}

		// 22
		static __forceinline NiPoint4* const GetShadowProjData() {
			return (NiPoint4*)0x11FD874;
		}

		// 23
		static __forceinline NiPoint4* const GetShadowProjTransform() {
			return (NiPoint4*)0x11FD884;
		}

		// 24
		static __forceinline NiPoint4* const GetBoundCenter() {
			return (NiPoint4*)0x11FD8B4;
		}

		// 25; aka LightDirection
		static __forceinline NiPoint4* const GetLightData() {
			return (NiPoint4*)0x11FD9A8;
		}

		static __forceinline NiPoint4* const GetLightData(UInt32 index) {
			return &((NiPoint4*)0x11FD9A8)[index];
		}

		// 35
		static __forceinline D3DMATRIX* const GetPrevWorldViewPT() {
			return (D3DMATRIX*)0x11FED08;
		}

		// 39
		static __forceinline D3DMATRIX* const GetPrevWorldViewT() {
			return (D3DMATRIX*)0x11FED48;
		}

		// 98
		static float* const GetPrevBoneMatrix3() {
			return (float*)0x11FA580;
		}
	};

	struct PixelConstants {
		// 0
		static __forceinline NiPoint4* const GetEyeDir() {
			return (NiPoint4*)0x11FD8A4;
		}

		// 0, map 2
		static __forceinline NiColorA* const GetFillColor() {
			return (NiColorA*)0x11FD8F4;
		}

		// 1
		static __forceinline NiColorA* const GetAmbientColor() {
			return reinterpret_cast<NiColorA*>(GetConstant(0));
		}

		// 1, map 2
		static __forceinline NiColorA* const GetRimColor() {
			return (NiColorA*)0x11FD904;
		}

		// 2
		static __forceinline NiColorA* const GetEmittanceColor() {
			return reinterpret_cast<NiColorA*>(GetConstant(27));
		}

		// 2, map 2
		static __forceinline NiPoint4* const GetVars() {
			return (NiPoint4*)0x11FD914;
		}

		// 3
		static __forceinline NiColorA* const GetLightColors() {
			return reinterpret_cast<NiColorA*>(0x11FA0D0);
		}

		static __forceinline NiColorA* const GetLightColor(int index) {
			ASSERT(index >= 1 && index < 11);
			return reinterpret_cast<NiColorA*>(GetConstant(index));
		}

		// 14 - params, 15 - color
		static __forceinline BSShader::FogProperties* const GetFogParams() {
			return (BSShader::FogProperties*)0x11FA280;
		}

		// 16
		static __forceinline float* const GetFogPlane() {
			return (float*)0x11FA2A0;
		}

		// 18
		static __forceinline NiPoint4* const GetLightPosition() {
			return (NiPoint4*)0x11FD9A8;
		}
		static __forceinline NiPoint4* const GetLightPosition(UInt32 index) {
			ASSERT(index >= 0 && index < 10);
			return &((NiPoint4*)0x11FD9A8)[index];
		}

		// 17
		static __forceinline NiPoint4* const GetEyePosition() {
			return (NiPoint4*)0x11FD894;
		}

		// 27
		static __forceinline Toggles* const GetToggles() {
			return reinterpret_cast<Toggles*>(GetConstant(33));
		}

		// 28
		static __forceinline NiColorA* const GetHairTint() {
			return (NiColorA*)0x11FA090;
		}

		// 29
		static __forceinline NiPoint4* const GetRefractionParams() {
			return (NiPoint4*)0x11FD944;
		}

		// 30
		static __forceinline NiPoint4* const GetSTBBColorConstants() {
			return GetConstant(35);
		}

		// 31
		static __forceinline NiPoint4* const GetLODTEXPARAMS() {
			return (NiPoint4*)0x11FA300;
		}
	};

	__forceinline void SetPixelConstantMapEntry(ShadowLightShader::PixelEntries aeIndex, const char* apEntryName) {
		((NiShaderConstantMapEntryPtr*)0x11FEC30)[aeIndex] = GetPixelConstantMap()->GetEntry(apEntryName);
	};

	static __forceinline void SetPixelConstantMapEntry(ShadowLightShader::PixelEntries aeIndex, NiShaderConstantMapEntry* apEntry) {
		((NiShaderConstantMapEntryPtr*)0x11FEC30)[aeIndex] = apEntry;
	};

	static __forceinline NiShaderConstantMapEntry* GetPixelConstantMapEntry(ShadowLightShader::PixelEntries index) {
		return ((NiShaderConstantMapEntryPtr*)0x11FEC30)[index];
	}

	__forceinline void SetVertexConstantMapEntry(ShadowLightShader::VertexEntries aeIndex, const char* apEntryName) {
		((NiShaderConstantMapEntryPtr*)0x11FEBD8)[aeIndex] = GetVertexConstantMap()->GetEntry(apEntryName);
	};

	static __forceinline void SetVertexConstantMapEntry(ShadowLightShader::VertexEntries aeIndex, NiShaderConstantMapEntry* apEntry) {
		((NiShaderConstantMapEntryPtr*)0x11FEBD8)[aeIndex] = apEntry;
	};

	static __forceinline NiShaderConstantMapEntry* GetVertexConstantMapEntry(ShadowLightShader::VertexEntries index) {
		return ((NiShaderConstantMapEntryPtr*)0x11FEBD8)[index];
	}
};
ASSERT_SIZE(ShadowLightShader, 0x8C)