#pragma once

#include "NiShaderConstantMap.hpp"
#include "NiShaderConstantMapEntry.hpp"
#include "NiTArray.hpp"
#include "NiSkinPartition.hpp"
#include "NiTransform.hpp"
#include "NiExtraData.hpp"
#include "NiGPUProgram.hpp"

class NiD3DRenderState;
class NiD3DShaderProgram;
class NiGeometry;
class NiSkinInstance;
class NiGeometryBufferData;
class NiPropertyState;
class NiDynamicEffectState;

NiSmartPointer(NiD3DShaderConstantMap);

class NiD3DShaderConstantMap : public NiShaderConstantMap {
public:
	NiD3DShaderConstantMap();
	virtual ~NiD3DShaderConstantMap();

	virtual NiRTTI						GetRTTI();
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
	virtual NiShaderError				AddPredefinedEntry(const char* pszKey, UInt32 uiExtra, UInt32 uiShaderRegister = 0, const char* pszVariableName = "", UInt32 uiDataSize = 0, UInt32 uiDataStride = 0, void* pvDataSource = 0, bool bCopyData = false);
	virtual NiShaderError				RemoveEntry(const char* pszKey);
	virtual NiShaderConstantMapEntry*	GetEntry(const char* pszKey);
	virtual int							GetEntryAtIndex(UInt32 uiIndex);
	virtual NiShaderError				SetShaderConstants(NiD3DShaderProgram* pkShaderProgram, NiGeometry* pkGeometry, NiSkinInstance* pkSkin, NiSkinPartition::Partition* pkPartition, NiGeometryBufferData* pkBuffData, NiPropertyState* pkState, NiDynamicEffectState* pkEffects, NiTransform& kWorld, NiBound& kWorldBound, UInt32 uiPass, bool bGlobal);
	virtual UInt32						GetEntryIndex(const char* pszKey);
	virtual NiShaderError				InsertEntry_0(NiShaderConstantMapEntry* pkEntry);
	virtual NiShaderError				InsertEntry(NiShaderConstantMapEntry* pkEntry);
	virtual NiShaderError				SetupPredefinedEntry(NiShaderConstantMapEntry* pkEntry);
	virtual NiShaderError				SetDefinedConstant(NiD3DShaderProgram* pkShaderProgram, NiShaderConstantMapEntry* pkEntry, NiGeometry* pkGeometry, const NiSkinInstance* pkSkin, const NiSkinPartition::Partition* pkPartition, NiGeometryBufferData* pkBuffData, const NiPropertyState* pkState, const NiDynamicEffectState* pkEffects, const NiTransform* kWorld, const NiBound* kWorldBound, UInt32 uiPass);
	virtual NiShaderError				SetConstantConstant(NiD3DShaderProgram* pkShaderProgram, NiShaderConstantMapEntry* pkEntry, UInt32 uiPass);
	virtual NiShaderError				SetAttributeConstant(NiD3DShaderProgram* pkShaderProgram, NiShaderConstantMapEntry* pkEntry, NiGeometry* pkGeometry, const NiSkinInstance* pkSkin, const NiSkinPartition::Partition* pkPartition, NiGeometryBufferData* pkBuffData, const NiPropertyState* pkState, const NiDynamicEffectState* pkEffects, const NiTransform* kWorld, const NiBound* kWorldBound, UInt32 uiPass, bool bGlobal, NiExtraData* pkExtraData);
	virtual NiShaderError				SetGlobalConstant(NiD3DShaderProgram* pkShaderProgram, NiShaderConstantMapEntry* pkEntry, UInt32 uiPass);
	virtual NiShaderError				SetOperatorConstant(NiD3DShaderProgram* pkShaderProgram, NiShaderConstantMapEntry* pkEntry, NiGeometry* pkGeometry, const NiSkinInstance* pkSkin, const NiPropertyState* pkState, const NiDynamicEffectState* pkEffects, const NiTransform* kWorld, const NiBound* kWorldBound, UInt32 uiPass);
	virtual NiShaderError				SetupObjectEntry(NiShaderConstantMapEntry* pkEntry);
	virtual NiShaderError				SetObjectConstant(NiD3DShaderProgram* pkShaderProgram, NiShaderConstantMapEntry* pkEntry, NiGeometry* pkGeometry, const NiSkinInstance* pkSkin, const NiSkinPartition::Partition* pkPartition, NiGeometryBufferData* pkBuffData, const NiPropertyState* pkState, const NiDynamicEffectState* pkEffects, const NiTransform* kWorld, const NiBound* kWorldBound, UInt32 uiPass);

	NiTObjectArray<NiShaderConstantMapEntry>	m_aspEntries;
	NiTObjectArray<NiShaderConstantMapEntry>	m_aspEntries2;
	bool										m_bModified;
	NiD3DShaderProgram*							m_pkLastShaderProgram;
	UInt32										m_eLastError;
	D3DDevicePtr								m_pkD3DDevice;
	NiD3DRenderer*								m_pkD3DRenderer;
	NiD3DRenderState*							m_pkD3DRenderState;

	static NiD3DShaderConstantMap* Create(NiDX9Renderer* apRenderer, NiGPUProgram::ProgramType aeType);
	static NiD3DShaderConstantMap* CreatePixelConstantMap(NiDX9Renderer* apRenderer);
	static NiD3DShaderConstantMap* CreateVertexConstantMap(NiDX9Renderer* apRenderer);
};

ASSERT_SIZE(NiD3DShaderConstantMap, 0x44)