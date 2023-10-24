#pragma once

#include "NiNode.hpp"
#include "BSFaceGenAnimationData.hpp"
#include "BSCullingProcess.hpp"

class Actor;

NiSmartPointer(BSFaceGenNiNode);

class BSFaceGenNiNode : public NiNode {
public:
	BSFaceGenNiNode();
	virtual ~BSFaceGenNiNode();

	BSFaceGenAnimationDataPtr spAnimationData;
	NiMatrix3 BaseRotation;
	bool bForceBaseMorph;
	bool bFixedNormals;
	bool bAnimationUpdate;
	bool bRotatedLastUpdate;
	bool bApplyRotationToParent;
	UInt8 padD9[3];
	float fLastTime;
	bool bUsingLoResHead;
	bool bIAmPlayerCharacter;
	bool isInDialouge;
	bool padE3;
	UInt32 unkE4;
	Actor* pActor;
	UInt8 byteEC;
	UInt8 padED[3];

	static void __fastcall OnVisibleEx(BSFaceGenNiNode* apThis, void*, BSCullingProcess* apCuller);
};

ASSERT_SIZE(BSFaceGenNiNode, 0xF0)