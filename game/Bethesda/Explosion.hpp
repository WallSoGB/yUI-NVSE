#pragma once
#include "MobileObject.hpp"
#include "BSSoundHandle.hpp"
#include "NiPointLight.hpp"
#include "NonActorMagicCaster.hpp"

class Explosion : public MobileObject
{
public:
	Explosion();
	~Explosion();

	Float32					unk088;
	Float32					unk08C;		// init to 3.0
	Float32					buildTime;
	Float32					radius;
	Float32					ISRadius;
	Float32					unk09C;
	NiRefObject*			object0A0;
	BSSimpleList<UInt32>	list0A4;
	BSSoundHandle*			sound[6];
	NiPointLight*			pointLight;
	TESObjectREFR*			source;
	NiRefObject*			object0CC;
	NiRefObject*			object0D0;
	UInt32					unk0D4;
	UInt8					dontApplyExplosionIMOD;
	UInt8					isUnderwater;
	UInt8					byte0DA;
	UInt8					byte0DB;
	NonActorMagicCaster*	extraCaster;		
	TESObjectWEAP*			weapon;			// 0E0
	UInt32					unk0E4;			// 0E4
	NiPoint3				vec0E8;			// 0E8
	NiPoint3				vec0F4;			// 0F4
	Float32					unk100;

  static NiTPointerList<TESObjectREFR*>* GetWaterReflectedRefs();
};
static_assert(sizeof(Explosion) == 0x104);