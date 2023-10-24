#pragma once

#include "NiTArray.hpp"
#include "BSSimpleList.hpp"
#include "DetectionTaskData.hpp"
#include "AnimationTaskData.hpp"
#include "PackageUpdateTaskData.hpp"
#include "ActorUpdateTaskData.hpp"
#include "ActorsScriptTaskData.hpp"
#include "MovementTaskData.hpp"
#include "BSTFreeList.hpp"
#include "MobileObjectMessage.hpp"
#include "LockFreeMap.hpp"
#include "NiSmartPointer.hpp"
#include "LipTask.hpp"
#include "BSTempEffectParticle.hpp"
#include "BSSemaphore.hpp"

class MobileObject;
class BSTempEffect;
class MuzzleFlash;
class Actor;

struct ProcessManager 
{
	enum ProcessLevel
	{
		kProcessManagerLevel_High = 0x0,
		kProcessManagerLevel_MidHigh = 0x1,
		kProcessManagerLevel_MidLow = 0x2,
		kProcessManagerLevel_Low = 0x3,
	};

	struct TaskData {
		DetectionTaskData detectionTaskData;
		AnimationTaskData animationTaskData;
		PackageUpdateTaskData packageUpdateTaskData;
		ActorUpdateTaskData actorUpdateTaskData;
		ActorsScriptTaskData actorsScriptTaskData;
		MovementTaskData movementTaskData;
		BSTStaticFreeList<MobileObjectMessage,4096> mobileObjectMessageList;
		bool byte10180;
	};

	struct ProcessLists {
		NiTPrimitiveArray<MobileObject*> objectsNiTArray;
		UInt32 beginOffsets[4];
		UInt32 endOffsets[4];
		UInt32 unk034[4];
	};

	UInt32									unk000;				// 000
	ProcessLists							AllProcessArrays;
	BSSimpleList<UInt32*>*					crimes[5];			// 044
	BSSimpleList<BSTempEffectParticle*>		lTempParticles;			// 058
	BSSimpleList<BSTempEffect*>				lTempEffects;		// 060
	BSSimpleList<MuzzleFlash*>				lMuzzleFlashList;		// 068
	BSSimpleList<void*>						lArrowProjectileList;			// 070
	BSSimpleList<void*>						lTempShouldMoveList;			// 078
	BSSimpleList<Actor*>					lHighActors;			// 080
	Actor*									pNearbyActors[50];	// 088
	UInt32									uiNearbyActorCount;
	float									fCommentOnPlayerActionsTimer;
	float									fCommentOnPlayerKnockingThingsTimer;
	bool									bPlayerInRadiation1;
	bool									bPlayerInRadiation2;
	TaskData								kTaskData;			// 190
	BSSimpleList<UInt32>					list102E4;
	UInt32									unk102EC;
	UInt32									unk102F0;
	UInt32									unk102F4;
	UInt32									unk102F8;
	UInt32									unk102FC;
	BSSpinLock								criticalSection;
	UInt32									unk10320;
	UInt32									unk10324;
	UInt32									unk10328;
	UInt32									unk1032C;
	UInt32									unk10330;
	UInt32									unk10334;
	UInt32									unk10338;
	UInt32									unk1033C;
	UInt32									unk10340;
	UInt32									unk10344;
	UInt32									unk10348;
	UInt32									unk1034C;
	UInt32									unk10350;
	UInt32									unk10354;
	UInt32									unk10358;
	UInt32									unk1035C;
	LockFreeMap<MobileObject*, NiPointer<LipTask>>	lipTaskMap;		// 10360
	bool									bToggleAI;			// 103A0
	bool									bToggleDetection;	// 103A1
	bool									bToggleDetectionStats;	// 103A2
	UInt8									byte103A3;			// 103A3
	UInt32									uiDetectionStats;		// 103A4
	bool									bToggleHighProcess;	// 103A8
	bool									bToggleLowProcess;	// 103A9
	bool									bToggleMidHighProcess;	// 103AA
	bool									bToggleMidLowProcess;	// 103AB
	bool									bToggleAISchedules;	// 103AC
	bool									bShowSubtitle;		// 103AD
	UInt8									byte103AE;			// 103AE
	UInt8									byte103AF;			// 103AF
	UInt32									uiNumberHighActors;		// 103B0
	float									fCrimeUpdateTimer;	// 103B4
	UInt32									uiCrimeNumber;		// 103B8
	float									fRemoveExcessComplexDeadTime;	// 103BC
	BSSemaphore								semaphore103C0;		// 103C0

	__forceinline static ProcessManager* GetSingleton() { return (ProcessManager*)0x11E0E80; }

	__forceinline int GetTotalDetectionValue(Actor* actor, bool arg2 = false) {
		return ThisStdCall<int>(0x973710, this, actor, arg2);
	}
};

ASSERT_SIZE(ProcessManager, 0x103CC);