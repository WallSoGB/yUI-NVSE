#pragma once
#include "BSNiNode.hpp"
#include "BSMultiBound.hpp"

NiSmartPointer(BSMultiBoundNode);
NiRTTIAddress(BSMultiBoundNode, 0x1202E74);

class BSCullingProcess;
class BSOcclusionPlane;
class BSMultiBoundRoom;

// 0xB4
class BSMultiBoundNode : public BSNiNode
{
public:
	BSMultiBoundNode();
	virtual ~BSMultiBoundNode();

	virtual BSMultiBoundRoom*	GetMultiBoundRoom();
	virtual bool				GetPointWithin(NiPoint3& akPoint);
	virtual UInt32				CheckBound(BSMultiBound*);
	virtual UInt32				CheckBoundAlt(NiBound*);

	BSMultiBoundPtr spMultiBound;
	UInt32			uiCullingMode;

	CREATE_OBJECT(BSMultiBoundNode, 0xC46DF0);

	BSMultiBound* GetMultiBound();
	void SetMultiBound(BSMultiBound* apMultiBound);
	void SetCullingMode(UInt32 aiMode);
	bool VisibleAgainstActiveOccluders(NiPoint3 akViewPoint, BSCullingProcess* apCuller, BSOcclusionPlane* apOccluder);
	static void __fastcall OnVisibleEx(BSMultiBoundNode* apThis, void*, BSCullingProcess* apCuller);
};
static_assert(sizeof(BSMultiBoundNode) == 0xB4);