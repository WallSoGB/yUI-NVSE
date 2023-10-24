#pragma once
#include "TESBoundObject.hpp"
#include "TESFullName.hpp"
#include "TESModelTextureSwap.hpp"
#include "TESIcon.hpp"
#include "BGSMessageIcon.hpp"
#include "TESValueForm.hpp"
#include "BGSClipRoundsForm.hpp"
#include "BGSDestructibleObjectForm.hpp"
#include "BGSPickupPutdownSounds.hpp"
#include "TESScriptableForm.hpp"

class BGSProjectile;
class TESObjectMISC;
class TESAmmoEffect;

// 0xDC
class TESAmmo :
	public TESBoundObject,				// 000
	public TESFullName,					// 030
	public TESModelTextureSwap,			// 03C
	public TESIcon,						// 05C
	public BGSMessageIcon,				// 068	
	public TESValueForm,				// 078
	public BGSClipRoundsForm,			// 080
	public BGSDestructibleObjectForm,	// 088
	public BGSPickupPutdownSounds,		// 090
	public TESScriptableForm			// 09C
{
public:
	TESAmmo();
	~TESAmmo();

	enum eAmmoFlags
	{
		kFlags_IgnoreWeapResistance = 1,
		kFlags_NonPlayable = 2,
	};

	float						speed;					// 0A8	8 bytes makes it DATA
	UInt32						flags;					// 0AC	only 8 bits most likely. 0 is Ignores Normal Weapon Resistance', 1 is Non-Playable
	UInt32						projPerShot;			// 0B0
	BGSProjectile* projectile;			// 0B4
	float						weight;					// 0B8
	TESObjectMISC* casing;				// 0BC
	float						ammoPercentConsumed;	// 0C0
	BSStringT						shortName;				// 0C4
	BSStringT						abbreviation;			// 0CC
	BSSimpleList<TESAmmoEffect*>		effecBSSimpleList;				// 0D4

	bool IsNonPlayable() { return (flags & kFlags_NonPlayable) == kFlags_NonPlayable; }
	bool IsPlayable() { return !IsNonPlayable(); }
	SInt32 GetEffectIndex(TESAmmoEffect* effect);
};
static_assert(sizeof(TESAmmo) == 0xDC);