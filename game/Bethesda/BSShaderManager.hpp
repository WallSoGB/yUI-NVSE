#pragma once

#include "BSShaderAccumulator.hpp"
#include "NiDX9Renderer.hpp"
#include "TangentSpaceData.hpp"

class BSShader;

class BSShaderManager {
public:
	enum eSceneGraphEnum {
		BSSM_SSN_WORLD = 0x0,
		BSSM_SSN_UI = 0x1,
		BSSM_SSN_PREVIEW = 0x2,
		BSSM_SSN_UI_LOADING_MENU = 0x3,
		BSSM_SSN_COUNT = 0x4,
	};

	enum eShader {
		BSSM_SHADER_DEFAULT = 0x0,
		BSSM_SHADER_SHADOWLIGHT = 0x1,
		BSSM_SHADER_TALL_GRASS = 0x2,
		BSSM_SHADER_DISTANT_LOD = 0x3,
		BSSM_SHADER_ST_BRANCH = 0x4,
		BSSM_SHADER_ST_FROND = 0x5,
		BSSM_SHADER_ST_LEAF = 0x6,
		BSSM_SHADER_BLOOD_SPLATTER = 0x7,
		BSSM_SHADER_DISTANT_TREE = 0x8,
		BSSM_SHADER_DEBUG = 0x9,
		BSSM_SHADER_SKY = 0xA,
		BSSM_SHADER_HAIR = 0xD,
		BSSM_SHADER_SKIN = 0xE,
		BSSM_SHADER_PARALLAX = 0xF,
		BSSM_SHADER_NiDX9ShaderDeclaration = 0x10,
		BSSM_SHADER_WATER = 0x11,
		BSSM_SHADER_PARTICLE = 0x18,
		BSSM_SHADER_BOLT = 0x19,
		BSSM_SHADER_BEAM = 0x1A,
		BSSM_SHADER_LIGHTING30 = 0x1D,
		BSSM_SHADER_PRECIPITATION = 0x1E,
		BSSM_SHADER_TILE = 0x20,
		BSSM_SHADER_NOLIGHTING = 0x21,
		BSSM_SHADER_VOLUMETRIC_FOG = 0x22,
	};

	enum eLightingPasses {
		BSSM_PASS_NONE = 0x0,
		BSSM_PASS_AMBIENT = 0x1,
		BSSM_PASS_DIFFUSE = 0x2,
		BSSM_PASS_TEXTURE = 0x4,
		BSSM_PASS_SPECULAR = 0x8,
		BSSM_PASS_SHADOW = 0x10,
		BSSM_PASS_CANOPYSHADOW = 0x20,
		BSSM_PASS_OPT = 0x100,
		BSSM_PASS_ALL = BSSM_PASS_AMBIENT | BSSM_PASS_DIFFUSE | BSSM_PASS_TEXTURE | BSSM_PASS_SPECULAR | BSSM_PASS_SHADOW | BSSM_PASS_CANOPYSHADOW | BSSM_PASS_OPT,
	};


	struct ShaderPackage {
		struct RawShader {
			char cFileName[260];
			DWORD shader;
		};

		const char* pcPackagePath;
		DWORD dword4;
		NiTStringMap<RawShader*> kShaders;

		static ShaderPackage* GetInstance() { return *(ShaderPackage**)0x11F9498; }
		RawShader* GetShader(const char* apcShaderName) {
			RawShader* pShader = nullptr;
			kShaders.GetAt(apcShaderName, pShader);
			return pShader;
		}
	};





	static bool* const bIsHDR;
	static UInt32 uiDebugMode;
	static bool bNoMips;
	static bool bHDRMult;
	static Bitfield32* const uiEnabledPasses;
	static bool* const bIsLiteBrite;
	static bool* const bIsInInterior;
	static NiTexturePtr* const spCanopyShadowTexture;
	static float* const fDepthBias;
	static float* const fLODLandDrop;

	static __forceinline ShadowSceneNode* GetShadowSceneNode(UInt32 aeType) {
		return ((ShadowSceneNode**)0x11F91C8)[aeType];
	};

	static __forceinline NiRect<float> GetViewport() { return *(NiRect<float>*)0x11AD840; };

	static BSShaderAccumulator* GetAccumulator() { return (*(BSShaderAccumulatorPtr*)0x11F95EC); }
	static BSShaderAccumulator* GetCurrentAccumulator() { return (*(BSShaderAccumulator**)0x11F95F0); }

	static NiPoint3 GetCullerCameraPos() { return *(NiPoint3*)0x11FA2A0; }
	static NiPoint3 GetCameraPos() { return *(NiPoint3*)0x11F474C; }

	static void SetAccumulator(BSShaderAccumulator* apAccumulator) { *(BSShaderAccumulatorPtr*)0x11F95EC = apAccumulator; }

	static NiDX9Renderer* GetRenderer() { return *(NiD3DRenderer**)0x11F9508; }

	static BSShader* GetShader(eShader aiShaderIndex) { return CdeclCall<BSShader*>(0xB55560, aiShaderIndex); }

	static bool IsUseImageSpaceEffects() { return *(bool*)0x11F91A4; }

	static __forceinline NiCamera* GetCamera() { return *(NiCamera**)0x11F917C;	}

	static __forceinline void SetCamera(NiCamera* apCamera) { *(NiCamera**)0x11F917C = apCamera; }

	static __forceinline void SetRenderMode15ShaderAccumulator(BSShaderAccumulator* apAccumulator) { *(BSShaderAccumulatorPtr*)0x11F95F0 = apAccumulator; }

	static __forceinline UInt32 GetShaderModel(bool abPixel) { return abPixel ? *(UInt32*)0x11F91BC : *(UInt32*)0x11F91C0;	}

	static __forceinline bool IsUseRefractionShader() { return *(bool*)0x11F9180; }

	static __forceinline bool CanUseRefractionShader() { return IsUseRefractionShader() && GetShaderModel(false) >= 2; }

	static __forceinline bool IsShadowPass() { return StdCall<bool>(0x5BF7B0); }

	static __forceinline void GetTexture(const char* apFilename, bool abLoadFile, NiPointer<NiTexture>* aspTexture, bool abCheckMips = true, bool abCubeMap = false);

	static void SetShader(NiGeometry* apGeometry, UInt32 aeFadeType, bool abKeepUV = false, bool abNoPrecache = false);
	static void SetShadersRecursively(NiAVObject* apObject, UInt32 aeFadeType, bool abKeepUV = false, bool abNoPrecache = false);
	static void AssignShaders(NiAVObject* apObject, bool abKeepUV = false, bool abNoPrecache = false);

	static UInt32 GetFadeType(NiAVObject* apObject);

	static __forceinline eSceneGraphEnum GetFogIndex() {
		return static_cast<eSceneGraphEnum>(*(UInt8*)0x11F91C4);
	}

	static __forceinline void SetFogIndex(eSceneGraphEnum acIndex) {
		*(UInt8*)0x11F91C4 = acIndex;
	}

	static __forceinline void SetRenderMode(BSShaderAccumulator::etRenderMode auiRenderMode, UInt32 uiLock = 0) {
		static bool bRenderModeLocked = false;
		static BSShaderAccumulator::etRenderMode uiLockedMode = BSShaderAccumulator::BSSM_RENDER_NORMAL;

		if (uiLock == 1)
			bRenderModeLocked = !bRenderModeLocked;

		if (uiLock == 2)
			bRenderModeLocked = false;

		if (bRenderModeLocked)
			auiRenderMode = uiLockedMode;

		CdeclCall(0xB4F450, auiRenderMode);
	}

	static double GetTimer(bool abDelta) {
		return ((float*)0x11F940C)[abDelta];
	}

	static __forceinline void SetTimer(bool abDelta, double afTime) {
		((float*)0x11F940C)[abDelta] = afTime;
	}

	static UInt32 GetShadowMode() {
		return *(UInt32*)0x11F91B0;
	}

	static void ClearShadowAccumCount();
	static BSShaderAccumulator* GetNextShadowAccumulator();

	static bool __cdecl SetLightingPasses(void* paramInfo, void* scriptData, void* thisObj, void* containingObj, void* scriptObj, void* eventList, int, void* opcodeOffsetPtr);

	static void __cdecl SetExternalEmittanceRecurse(NiAVObject* apObject, NiColor* apExternalEmittance);
	static TangentSpaceData* CreateTangentSpaceSimple(NiGeometry* apGeometry);
	static void ProcessQueuedLights();

	static NiSourceTexturePtr GetHideSecretMap() { return *(NiSourceTexturePtr*)0x11F9528; }
	static NiTexture* GetAnisoMap() { return *(NiTexture**)0x11F9530; }
	static NiTexture* GetNormalMap() { return *(NiTexture**)0x11F9510; }
	static NiTexture* GetNormalGlossMap() { return *(NiTexture**)0x11F9518; }
	static NiTexture* GetArmorReflectionCubeMap() { return *(NiTexture**)0x11F95D4; }
	static NiTexture* GetEyeReflectionCubeMap() { return *(NiTexture**)0x11F9544; }
	static NiTexture* GetErrorMap() { return *(NiTexture**)0x11F9514; }
	static NiTexture* GetHeightMap() { return *(NiTexture**)0x11F951C; }
	static NiTexture* GetTexEffectMap() { return *(NiTexture**)0x11F952C; }
	static NiTexture* GetLODNoiseMap() { return *(NiTexture**)0x11F953C; }
	static NiTexture* GetEmptyNoiseMap() { return *(NiTexture**)0x11F9540; }
	static NiTexture* GetAttenuationXYZ() { return *(NiTexture**)0x11F9534; }
	static void SetArmorReflectionCubeMap(NiTexture* apTexture) { *(NiTexture**)0x11F95D4 = apTexture; }
	static void SetEyeReflectionCubeMap(NiTexture* apTexture) { *(NiTexture**)0x11F9544 = apTexture; }
	static __forceinline BSRenderedTexture* GetWaterRefractionTexture() { return *(BSRenderedTexture**)0x11F943C; }
	static __forceinline void SetWaterRefractionTexture(BSRenderedTexture* apTexture) { *(BSRenderedTexture**)0x11F943C = apTexture; }
};