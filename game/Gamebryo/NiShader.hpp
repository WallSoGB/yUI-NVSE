#pragma once

#include "NiRefObject.hpp"
#include "NiFixedString.hpp"
#include "NiRTTI.hpp"
#include "NiGeometry.hpp"

class NiDynamicEffectState;
class NiGeometryBufferData;
class NiSkinInstance;

class NiShader : public NiRefObject {
public:
	NiShader();
	virtual ~NiShader();

	virtual NiRTTI*						GetRTTI();
	virtual NiNode*						IsNiNode();
	virtual BSFadeNode*					IsFadeNode();
	virtual BSMultiBoundNode*			IsMultiBoundNode();
	virtual NiGeometry*					IsGeometry();
	virtual NiTriBasedGeom*				IsTriBasedGeometry();
	virtual NiTriStrips*				IsTriStrips();
	virtual NiTriShape*					IsTriShape();
	virtual BSSegmentedTriShape*		IsSegmentedTriShape();
	virtual BSResizableTriShape*		IsResizableTriShape();
	virtual NiParticles*				IsParticlesGeom();
	virtual NiLines*					IsLinesGeom();
	virtual bhkCollisionObject*			IsBhkNiCollisionObject();
	virtual bhkBlendCollisionObject*	IsBhkBlendCollisionObject();
	virtual bhkRigidBody*				IsBhkRigidBody();
	virtual bhkLimitedHingeConstraint*	IsBhkLimitedHingeConstraint();
	virtual bool						IsInitialized();
	virtual void						Initialize();
	virtual bool						SetupGeometry(NiGeometry* pkGeometry);
	virtual UInt32						PreProcessPipeline(NiGeometry* pkGeometry, const NiSkinInstance* pkSkin, NiGeometryBufferData* pkRendererData, const NiPropertyState* pkState, const NiDynamicEffectState* pkEffects, const NiTransform& kWorld, const NiBound& kWorldBound);
	virtual void						UpdatePipeline(NiGeometry* pkGeometry, const NiSkinInstance* pkSkin, NiGeometryBufferData* pkRendererData, const NiPropertyState* pkState, const NiDynamicEffectState* pkEffects, const NiTransform& kWorld, const NiBound& kWorldBound);
	virtual void						SetupRenderingPass(NiGeometry* pkGeometry, const NiSkinInstance* pkSkin, NiGeometryBufferData* pkRendererData, const NiPropertyState* pkState, const NiDynamicEffectState* pkEffects, const NiTransform& kWorld, const NiBound& kWorldBound);
	virtual UInt32						SetupTransformations(NiGeometry* pkGeometry, const NiSkinInstance* pkSkin, const NiSkinPartition::Partition* pkPartition, NiGeometryBufferData* pkRendererData, const NiPropertyState* pkState, const NiDynamicEffectState* pkEffects, const NiTransform& kWorld, const NiBound& kWorldBound);
	virtual void						Func_25(NiGeometry* geo, const NiSkinInstance* skinInstance, const NiSkinPartition::Partition* skinPartition, NiGeometryBufferData* rendererData, int shaderProperties, int a7, const NiTransform* worldTransform, NiBound* worldBound);
	virtual UInt32						SetupShaderPrograms(NiGeometry* pkGeometry, const NiSkinInstance* pkSkin, const NiSkinPartition::Partition* pkPartition, NiGeometryBufferData* pkRendererData, const NiPropertyState* pkState, const NiDynamicEffectState* pkEffects, const NiTransform& kWorld, const NiBound& kWorldBound);
	virtual NiGeometryBufferData*		PrepareGeometryForRendering(NiGeometry* pkGeometry, const NiSkinPartition::Partition* pkPartition, NiGeometryBufferData* pkRendererData, const NiPropertyState* pkState);
	virtual UInt32						PostRender(NiGeometry* pkGeometry, const NiSkinInstance* pkSkin, const NiSkinPartition::Partition* pkPartition, NiGeometryBufferData* pkRendererData, const NiPropertyState* pkState, const NiDynamicEffectState* pkEffects, const NiTransform& kWorld, const NiBound& kWorldBound);
	virtual UInt32						PostProcessPipeline(NiGeometry* pkGeometry, const NiSkinInstance* pkSkin, NiGeometryBufferData* pkRendererData, const NiPropertyState* pkState, const NiDynamicEffectState* pkEffects, const NiTransform& kWorld, const NiBound& kWorldBound);
	virtual void						SetupTextures(NiPropertyState* pShaderProps);
	virtual void						UpdateConstants(NiPropertyState* pShaderProps);
	virtual void						SetBlendAlpha(NiPropertyState* pShaderProps);
	virtual void						SetTestAlpha(NiPropertyState* pShaderProps);
	virtual void						Func_34(NiPropertyState* pShaderProps, bool bHasAlpha);
	virtual void						Func_35(NiPropertyState* shaderProps);
	virtual int							HasPasses();
	virtual int							EndPass();
	virtual void						StreamCanSkip();
	virtual void						Func_39();
	virtual void						Func_40();
	virtual void						Func_41();
	virtual void						Func_42();
	virtual void						SetShaderConstant();
	virtual void						Func_44();
	virtual void						SetShaderConstantArray();
	virtual void						Func_46();

	NiFixedString	m_kName;
	UInt32			m_uiImplementation;
	bool			m_bInitialized;

	static bool __fastcall InitializeEx(NiShader* apThis);
};

ASSERT_SIZE(NiShader, 0x14);