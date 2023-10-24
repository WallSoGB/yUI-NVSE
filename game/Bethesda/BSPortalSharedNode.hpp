#pragma once

#include "NiNode.hpp"
#include "BSSimpleArray.hpp"
#include "ShadowSceneLight.hpp"

class BSCompoundFrustum;
class BSPortal;
class BSCullingProcess;

class BSPortalSharedNode : public NiNode {
public:
	BSCompoundFrustum* kCompoundFrustum;
	BSSimpleArray<ShadowSceneLight*> kLights;
	BSPortal* apPortal;

	static void __fastcall OnVisibleEx(BSPortalSharedNode* apThis, void*, BSCullingProcess* apCuller);
};

ASSERT_SIZE(BSPortalSharedNode, 0xC4);