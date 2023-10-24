#pragma once

#include "BSMultiBoundNode.hpp"
#include "NiTPointerList.hpp"
#include "BSSimpleArray.hpp"
#include "BSPortal.hpp"

class ShadowSceneLight;
class BSCompoundFrustum;

class BSMultiBoundRoom : public BSMultiBoundNode {
public:
	NiTPointerList<BSPortal*>			kPortalList;
	NiTPointerList<UInt32>				lOccluderList;
	BSCompoundFrustum*					pFrustum;
	NiTPointerList<BSMultiBound*>		kJoinedMultiBoundList;
	BSSimpleArray<ShadowSceneLight*>	kLights;

	static void __fastcall OnVisibleEx(BSMultiBoundRoom* apThis, void*, BSCullingProcess* apCuller);
};

ASSERT_SIZE(BSMultiBoundRoom, 0xEC);
