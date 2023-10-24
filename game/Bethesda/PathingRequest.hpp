#pragma once

#include "NiRefObject.hpp"
#include "NiPoint3.hpp"
#include "PathingLocation.hpp"

class TESForm;
class BGSSaveFormBuffer;

class PathingRequest : public NiRefObject {
public:
	virtual ~PathingRequest();

	virtual void	CopyTo(PathingRequest* apTarget);		// 02
	virtual void	Unk_03();								// 03
	virtual UInt32	GetType();								// 04
	virtual void	PrintDebugText(void*);					// 05
	virtual void	Write(BGSSaveFormBuffer* apBuffer);		// 06
	virtual void	Read(BGSSaveFormBuffer* apBuffer);		// 07
	virtual void	Unk_08();								// 08


	struct ActorData {
		TESForm*	pBaseForm;
		void*		inventoryChanges;
		bool		bIsAlarmed;
	};


	UInt32 unk08;
	PathingLocation start;
	PathingLocation dest;
	PathingRequest::ActorData actorData;
	float fActorRadius;
	float flt6C;
	float goalZDelta;
	float fTargetRadius;
	float fCenterRadius;
	NiPoint3 targetPt;
	float unk88;
	float fGoalAngle;
	float fInitialPathHeading;
	struct PathingAvoidNodeArray* avoidNodeArray;
	bool bCantOpenDoors;
	bool bFaceTargetAtGoal;
	bool byte9A;
	bool bAllowIncompletePath;
	bool byte9C;
	bool bCanSwim;
	bool bCanFly;
	bool byte9F;
	bool bInitialPathHeading;
	bool byteA1;
	bool bCurvedPath;
	bool byteA3;
	bool bIgnoreLocks;
	bool padA5[3];
	UInt32 iSmoothingRetryCount;
	bool byteAC;
	bool padAD[3];
};

ASSERT_SIZE(PathingRequest, 0xB0);