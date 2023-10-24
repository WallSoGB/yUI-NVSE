#pragma once
#include "MobileObject.hpp"
#include "BSSoundHandle.hpp"
#include "NiPointLight.hpp"
#include "NonActorMagicCaster.hpp"

class InventoryChanges;

class Projectile : public MobileObject
{
public:
	Projectile();
	~Projectile();

	BSSimpleList<BGSImpactData*>	impactDataList;		// 0x088
	UInt8					hasImpacted;		// 0x08C
	UInt8					pad091[3];
	NiMatrix33				nimatrix33;			// 0x094
	NiPoint3				nip3;				// 0x0B8	saved separately
	UInt32					unk0C4;				// 0x0C4	saved separately
	UInt32					projFlags;			// 0x0C8
	Float32					speedMult1;			// 0x0CC
	Float32					speedMult2;			// 0x0D0
	Float32					range;				// 0x0D4
	Float32					elapsedTime;		// 0x0D8
	Float32					hitDamage;			// 0x0DC
	Float32					fadeTimePercent;	// 0x0E0
	Float32					detonationTime;		// 0x0E4
	Float32					mineBlinkTimer;		// 0x0E8
	Float32					spreadz;			// 0x0EC
	Float32					spreadx;			// 0x0F0
	Float32					weaponHealthPercent;// set but unused
	TESObjectWEAP*			weapon;				// 0x0F8
	TESObjectREFR*			source;				// 0x0FC
	TESObjectREFR*			target;				// 0x100 live grenade target
	NiPoint3				pt104;				// 0x104
	UInt32					distTravelled;		// 0x110
	void*					light;				// 0x114
	UInt8					byte118;			// 0x118
	UInt8					pad119[3];			// 0x119
	void*					node11C;			// 0x11C
	UInt32					unk120;				// 0x120
	Float32					flt124;				// 0x124
	BSSoundHandle			passPlayerSound;	// 0x128
	BSSoundHandle			countDownSound;		// 0x134
	UInt32					unk140;				// 0x140
	InventoryChanges*		RILContChange;		// 0x144
	UInt8					hasPlayedPassPlayerSound;// 0x148
	UInt8					pad149[3];			// 0x149
	Float32					maxrange;
};
static_assert(sizeof(Projectile) == 0x150);