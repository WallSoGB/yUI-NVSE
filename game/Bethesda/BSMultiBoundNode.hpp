#pragma once

#include "BSNiNode.hpp"
#include "BSMultiBound.hpp"

NiSmartPointer(BSMultiBoundNode);
NiRTTIAddress(BSMultiBoundNode, 0x1202E74);

class BSCullingProcess;
class BSOcclusionPlane;

class BSMultiBoundNode : public BSNiNode {
public:
	BSMultiBoundNode();
	~BSMultiBoundNode();

	BSMultiBoundPtr spMultiBound;
	UInt32 uiCullingMode;

	CREATE_OBJECT(BSMultiBoundNode, 0xC46DF0);

	BSMultiBound* GetMultiBound();
	void SetMultiBound(BSMultiBound* apMultiBound);
	void SetCullingMode(UInt32 aiMode);
	bool VisibleAgainstActiveOccluders(NiPoint3 akViewPoint, BSCullingProcess* apCuller, BSOcclusionPlane* apOccluder);
	static void __fastcall OnVisibleEx(BSMultiBoundNode* apThis, void*, BSCullingProcess* apCuller);
};

ASSERT_SIZE(BSMultiBoundNode, 0xB4);