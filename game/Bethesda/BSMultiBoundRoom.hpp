#pragma once

#include "BSMultiBoundNode.hpp"
#include "NiTPointerList.hpp"
#include "BSSimpleArray.hpp"

class BSPortal;
class ShadowSceneLight;
class BSCompoundFrustum;
class BSOcclusionPlane;

NiSmartPointer(BSMultiBoundRoom);

class BSMultiBoundRoom : public BSMultiBoundNode {
public:
	BSMultiBoundRoom();
	virtual ~BSMultiBoundRoom();

	NiTPointerList<BSPortal*>			kPortalList;
	NiTPointerList<BSOcclusionPlane*>	kOccluders;
	BSCompoundFrustum*					pFrustum;
	NiTPointerList<BSMultiBound*>		kJoinedMultiBoundList;
	BSSimpleArray<ShadowSceneLight*>	kLights;

	static void __fastcall OnVisibleEx(BSMultiBoundRoom* apThis, void*, BSCullingProcess* apCuller);

	void SetFrustum(BSCompoundFrustum* apFrustum);
	void RemoveFrustum();
};

ASSERT_SIZE(BSMultiBoundRoom, 0xEC);
