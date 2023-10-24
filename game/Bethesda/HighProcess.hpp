#pragma once

#include "MiddleHighProcess.hpp"

class NiBSBoneLODController;
class NiBSplineCompTransformInterpolator;
class ProjectileData;
class DetectionEvent;
class Actor;
class bhkShapePhantom;

class HighProcess : public MiddleHighProcess {
public:
	HighProcess();
	~HighProcess();

	enum
	{
		kAnimAction_None = -1,
		kAnimAction_Equip_Weapon,
		kAnimAction_Unequip_Weapon,
		kAnimAction_Attack,
		kAnimAction_Attack_Follow_Through,
		kAnimAction_Attack_Latency,
		kAnimAction_Attack_Throw_Attach,
		kAnimAction_Attack_Throw_Release,
		kAnimAction_Block,
		kAnimAction_Stagger,
		kAnimAction_Reload,
		kAnimAction_Dodge,
		kAnimAction_Wait_For_Lower_Body_Anim,
		kAnimAction_Wait_For_Special_Idle,
		kAnimAction_Force_Script_Anim
	};

	enum
	{
		kSitSleepState_Normal = 0x0,
		kSitSleepState_LoadSitIdle = 0x1,
		kSitSleepState_WantToSit = 0x2,
		kSitSleepState_WaitingForSitAnim = 0x3,
		kSitSleepState_Sitting = 0x4,
		kSitSleepState_WantToStand = 0x5,
		kSitSleepState_LoadingSleepIdle = 0x6,
		kSitSleepState_WantToSleep = 0x7,
		kSitSleepState_WaitingForSleepAnim = 0x8,
		kSitSleepState_Sleeping = 0x9,
		kSitSleepState_WantToWake = 0xA,
	};

	struct ActorValueArray
	{
		struct Value
		{
			UInt8 isModified;
			UInt8 gap01[3];
			float value;
		};

		Value avs[77];
	};

	BSSimpleList<Actor*>* detectedActors;	// 25C
	BSSimpleList<Actor*>* detectingActors;	// 260
	void* ptr264;			// 264
	void* ptr268;			// 268
	void* ptr26C;			// 26C
	UInt32								unk270;				// 270
	BSSimpleList<void*>					combatTargeBSSimpleList274;			// 274
	BSSimpleList<void*>							list27C;			// 27C
	BSSimpleList<void*>							list284;			// 284
	BSSimpleList<void*>							list28C;			// 28C
	float								flt294;				// 294
	float								flt298;				// 298
	UInt32								unk29C;				// 29C
	float								flt2A0;				// 2A0
	UInt32								unk2A4;				// 2A4
	float								flt2A8;				// 2A8
	UInt32								unk2AC;				// 2AC
	float								actorAlpha;				// 2B0
	float								flt2B4;				// 2B4
	float								flt2B8;				// 2B8
	float								flt2BC;				// 2BC
	UInt16								word2C0;			// 2C0
	UInt8								byte2C2;			// 2C2
	UInt8								byte2C3;			// 2C3
	UInt8								byte2C4;			// 2C4
	UInt8								byte2C5;			// 2C5
	UInt8								byte2C6;			// 2C6
	UInt8								byte2C7;			// 2C7
	float								flt2C8;				// 2C8
	UInt32								unk2CC;				// 2CC
	float								flt2D0;				// 2D0
	float								flt2D4;				// 2D4
	float								flt2D8;				// 2D8
	UInt32								unk2DC;				// 2DC
	float								flt2E0;				// 2E0
	NiBSBoneLODController* ptr2E4;			// 2E4
	UInt32								unk2E8;				// 2E8
	SInt16								currentAction;		// 2EC
	UInt8								pad2EE[2];			// 2EE
	BSAnimGroupSequence* currentSequence;	// 2F0
	UInt8 forceFireWeapon;
	UInt8 gap2F5[3];
	float								flt2F8;				// 2F8
	UInt32								unk2FC[5];			// 2FC
	float								flt310;				// 310
	UInt32								unk314[7];			// 314
	float								flt330;				// 330
	float								flt334;				// 334
	float								flt338;				// 338
	float								diveBreath;			// 33C
	UInt32								unk340;				// 340
	float								flt344;				// 344
	UInt8								byte348;			// 348
	UInt8								bWeaponAlertDrawn;	// 349
	UInt8								gap34A;				// 34A
	UInt8								gap34B;				// 34B
	float								fAwarePlayerTimer;	// 34C
	TESIdleForm* idleForm350;		// 350
	UInt32								unk354[4];			// 354
	NiBSplineCompTransformInterpolator** ptr364;			// 364
	UInt32 unk368;
	UInt32 unk36C;
	UInt32 unk370;
	UInt8 isContinuingPackagePCNear;
	UInt8 gap375[3];
	float								flt378;				// 378
	float								flt37C;				// 37C
	UInt32								unk380;				// 380
	float								flt384;				// 384
	float								flt388;				// 388
	BSSimpleList<void*>							list38C;			// 38C
	BSSimpleList<void*>							list394;			// 394
	UInt32								unk39C;				// 39C
	UInt32								unk3A0;				// 3A0
	float								flt3A4;				// 3A4
	UInt32								unk3A8[5];			// 3A8
	float								flt3BC;				// 3BC
	float								flt3C0;				// 3C0
	float								lightAmount;		// 3C4
	float								flt3C8;				// 3C8
	UInt32								unk3CC;				// 3CC
	UInt32								unk3D0;				// 3D0
	ProjectileData* projData;			// 3D4
	UInt32								unk3D8;				// 3D8
	DetectionEvent* detectionEvent;	// 3DC
	UInt32								unk3E0;				// 3E0
	UInt32								unk3E4;				// 3E4
	UInt32								fadeType;			// 3E8
	float								delayTime;			// 3EC
	UInt32								unk3F0;				// 3F0
	UInt32								unk3F4;				// 3F4
	UInt32								unk3F8[3];			// 3F8
	Actor* combatTarget;		// 404
	UInt32								unk408[4];			// 408
	float								flt418;				// 418
	TESObjectREFR* packageTarget;		// 41C
	UInt32								unk420;				// 420
	UInt32								queuedIdleFlags;	// 424
	UInt32								unk428;				// 428
	float								flt42C;				// 42C
	UInt32								unk430;				// 430
	bhkShapePhantom* ptr434;			// 434
	UInt32								unk438;				// 438
	float								unk43C;				// 43C
	float								radsSec440;			// 440
	UInt8								plantedExplosive;	// 444
	UInt8								pad445[3];			// 445
	float								flt448;				// 448
	UInt32								unk44C;				// 44C
	float								flt450;				// 450
	UInt32								unk454[6];			// 454
};
static_assert(sizeof(HighProcess) == 0x46C);