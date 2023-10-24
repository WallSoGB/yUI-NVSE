#pragma once

#include "NiD3DShaderInterface.hpp"
#include "NiD3DShaderDeclaration.hpp"
#include "NiD3DShaderConstantMap.hpp"
#include "NiD3DPass.hpp"
#include "NiPropertyState.hpp"

class NiD3DRenderStateGroup;
class NiD3DShaderConstantMap;

class NiD3DShader : public NiD3DShaderInterface {
public:
	NiD3DShader();
	virtual ~NiD3DShader();

	virtual void ResetPasses();

	bool						m_bUsesNiRenderState;
	bool						m_bUsesNiLightState;
	NiD3DShaderDeclarationPtr	m_spShaderDecl;
	NiD3DRenderStateGroup*		m_pkRenderStateGroup;
	NiD3DShaderConstantMapPtr	m_spPixelConstantMap;
	NiD3DShaderConstantMapPtr	m_spVertexConstantMap;
	UInt32						m_uiCurrentPass;

	static NiD3DPass* m_kPass;
	static NiD3DPass* GetCurrentPass();
	static void SetCurrentPass(NiD3DPass* apPass);
	static void __fastcall SetBlendAlpha_Hook(NiD3DShader* apThis, void*, NiPropertyState* apPropertyState);
	static UInt32 __fastcall SetupTransformationsEx(NiD3DShader* apThis, void*, NiGeometry* pkGeometry, const NiSkinInstance* pkSkin, const NiSkinPartition::Partition* pkPartition, NiGeometryBufferData* pkRendererData, const NiPropertyState* pkState, const NiDynamicEffectState* pkEffects, const NiTransform& kWorld, const NiBound& kWorldBound);

	NiD3DShaderConstantMap* GetPixelConstantMap();
	void SetPixelConstantMap(NiD3DShaderConstantMap* apPixelConstantMap);

	NiD3DShaderConstantMap* GetVertexConstantMap();
	void SetVertexConstantMap(NiD3DShaderConstantMap* apVertexConstantMap);

	void SetPixelShaderConstants(NiGeometry* apGeometry, NiSkinInstance* apSkin, NiSkinPartition::Partition* apPartition, NiGeometryBufferData* apBuffData, NiPropertyState* apState, NiDynamicEffectState* apEffects, NiTransform& akWorld, NiBound& akWorldBound, UInt32 auiPass, bool abGlobal = true);
	void SetVertexShaderConstants(NiGeometry* apGeometry, NiSkinInstance* apSkin, NiSkinPartition::Partition* apPartition, NiGeometryBufferData* apBuffData, NiPropertyState* apState, NiDynamicEffectState* apEffects, NiTransform& akWorld, NiBound& akWorldBound, UInt32 auiPass, bool abGlobal = true);

	void ConfigureTextureStagesEx();

	static bool __fastcall InitializeEx(NiD3DShader* apThis);
};

ASSERT_SIZE(NiD3DShader, 0x3C);