#pragma once

#include "NiNode.hpp"
#include "ShadowSceneLight.hpp"
#include "BSCompoundFrustum.hpp"
#include "BSCubeMapCamera.hpp"
#include "DList.hpp"
#include "BSFogProperty.hpp"

class BSCullingProcess;

NiSmartPointer(ShadowSceneNode);

class ShadowSceneNode : public NiNode {
public:
	UInt32									unk0AC[2];
	NiTPointerList<ShadowSceneLight*>		lights;
	NiTPointerList<ShadowSceneLight*>		actorShadowCasters;
	NiTPointerList<ShadowSceneLight*>*		unk0CC;
	NiTPointerList<ShadowSceneLight*>*		unk0D0;
	NiTPointerList<ShadowSceneLight*>*		unk0D4;
	ShadowSceneLightPtr						spSceneLight1;
	ShadowSceneLightPtr						spSceneLight2;
	ShadowSceneLight*						pSunLight;		
	NiTPointerList<ShadowSceneLight*>		lLightQueueAdd;
	NiTPointerList<ShadowSceneLight*>		lLightList;
	NiTPointerList<ShadowSceneLight*>		dynamicLights;
	NiTPointerList<NiNode*>					list108;
	NiTPointerList<NiNode*>					list114;
	UInt8									cSceneGraphIndex;
	NiObject*								pObject124;
	NiPointer<BSCubeMapCamera>				spShadowMapCubeCam;
	UInt32									unk12C;
	bool									bDisableLightUpdate;
	bool									bWireframe;
	BSFogPropertyPtr						spFog;
	BSCompoundFrustum						kCompoundFrustum;
	bool									bVisibleUnboundSpace;
	BSPortalGraph*							pBSPortalGraph;
	NiPoint3								kLightingOffset;
	NiPoint3								kCameraPos;
	bool									bAllowLightRemoveQueues;

#if _EDITOR
	void* pObject200;
	NiObject* pObject204;
	NiNode* spDebugNode;
	UInt32 uiDebugFlags;
	NiCameraPtr spFrozenCamera;
	NiCameraPtr spRestoreCamera;
#endif

	static NiPointer<NiCamera>				spRestoreCamera;
	static NiPointer<NiCamera>				spFrozenCamera;

	static ShadowSceneNode* Create();

	static void __fastcall OnVisibleEx(ShadowSceneNode* apThis, void*, BSCullingProcess* apCuller);

	static BSFogProperty* GetFogProperty(UInt32 aeType);

	void DisableLightUpdate(bool abDisable);

	double GetLuminanceAtPoint(NiPoint3 position, int* aiNumberlights, float* afAmbientLum, float* a7, NiLight* apIgnore);

	void SetShadowCastToLight(NiLight* apLight, bool bEnableShadow);

	void PreOnVisible(BSCullingProcess* apCuller);

	ShadowSceneLight* GetShadowCaster();
	ShadowSceneLight* GetNextShadowCaster();
	ShadowSceneLight* AddShadowCaster(NiNode* apCaster);

	void RenderShadowMaps(BSCullingProcess* apCuller);
	void ResetShadowCasters();
	void ClearShadows();

	void ProcessQueuedLights();

	UInt32 AddAllLightsFromNode(NiNode* apNode, float afRadius);

	void BuildSharedCompoundFrustum(NiCamera* apCamera, BSPortal* apPortal);

	void UpdateMultiBoundVisibility(BSMultiBoundNode* apNode, NiPoint3 akViewPoint, BSCullingProcess* apCuller);
	void UpdateRoomAndPortalVisibility(BSMultiBoundRoom* apRoom, NiCamera* apCamera, NiFrustumPlanes* apPlanes, bool abAddIntersection);
};

static_assert(sizeof(ShadowSceneNode) == 0x200);