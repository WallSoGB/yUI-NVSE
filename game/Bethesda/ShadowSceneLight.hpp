#pragma once

#include "BSRenderedTexture.hpp"
#include "BSPortalGraph.hpp"
#include "BSSimpleArray.hpp"
#include "NiLight.hpp"
#include "Defines.hpp"
#include "NiCamera.hpp"

class BSShaderAccumulator;
class NiGeometry;
class BSMultiBoundRoom;
class BSPortal;
class BSPortalSharedNode;
class BSCullingProcess;

NiSmartPointer(ShadowSceneLight);

class ShadowSceneLight : public NiRefObject {
public:
	UInt32									unk008;
	float									fLuminance;
	D3DXMATRIX								matrix010;
	D3DXMATRIX								matrix050;
	D3DXMATRIX								matrix090;
	float									fLODDimmer;
	float									fAlpha;
	float									fShadowFadeTime0D8;
	float									fShadowFadeTime0DC;
	NiTPointerList<NiGeometry*>				kGeometryList;
	bool									bIsShadowCasting;
	UInt8									byte0ED;
	NiObjectPtr								spObject0F0;
	bool									bPointLight;
	bool									bAmbientLight;
	NiLightPtr								spLight;
	bool									bDynamicLight;
	NiPoint3								kPointPosition;
	BSRenderedTexturePtr					spShadowRenderTarget;
	UInt16									usFrustumCull;
	NiObjectPtr								spObject114;
	bool									bUnk118;
	float									fUnk11C;
	float									fUnk120;
	bool									bShowDebugTexture;
	NiPointer<NiNode>						spShadowCasterNode;
	NiTPointerList<UInt32>					kList12C;
	NiTListItem<NiGeometry*>*				kGeomListFence;
	NiPointer<NiTriShape>					spFenceObject;
	NiCameraPtr								spShadowMapCamera;
	NiFrustumPlanes							kFrustumPlanes;
	float									clipPlanes[24];
	bool									bUnk208;
	NiPointer<BSShaderAccumulator>			spShadowAccum;
	BSSimpleArray<BSMultiBoundRoom*>		kMultiboundRooms;
	BSSimpleArray<BSPortal*>				kPortals;
	BSSimpleArray<NiNode*>					kProcessedNodes;
	BSPortalGraph*							pPortalGraph;
	UInt32									unk244;
	UInt32									unk248;
	UInt32									unk24C;

	NiLight* GetLight();
	NiNode* GetShadowCasterNode();
	void ToggleShadow(bool bEnableShadow);
	double GetLuminanceAtPoint(NiPoint3 aPoint, NiLight* apIgnore);
	double GetLuminanceToBound(NiBound* apBound);
	bool BoundWithinLightRadius(NiBound* apBound, NiLight* apLight,	float afRadiusScale);
	SInt32 __cdecl SortByLuminance(ShadowSceneLight** appLight1, ShadowSceneLight** appLight2);
	void ParseObjectAddRadius(NiAVObject* apObject);
	void CreateFence();
	void UpdateShadowFadeTimes(float afiTme, bool abNoFade);

	void RemoveGeometry();
	void AccumulateGeometry(BSCullingProcess* apCuller);
	void RenderShadowMap(BSCullingProcess* apCuller);
};

ASSERT_SIZE(ShadowSceneLight, 0x250);