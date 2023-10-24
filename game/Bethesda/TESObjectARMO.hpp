#pragma once
#include "TESBoundObject.hpp"
#include "TESScriptableForm.hpp"
#include "TESEnchantableForm.hpp"
#include "TESValueForm.hpp"
#include "TESWeightForm.hpp"
#include "TESHealthForm.hpp"
#include "TESBipedModelForm.hpp"
#include "BGSDestructibleObjectForm.hpp"
#include "BGSEquipType.hpp"
#include "BGSRepairItemList.hpp"
#include "BGSBipedModelList.hpp"
#include "BGSPickupPutdownSounds.hpp"

class TESObjectARMO : 
	public TESBoundObject,
	public TESFullName,
	public TESScriptableForm,
	public TESEnchantableForm,
	public TESValueForm,
	public TESWeightForm,
	public TESHealthForm,
	public TESBipedModelForm,
	public BGSDestructibleObjectForm,
	public BGSEquipType,
	public BGSRepairItemList,
	public BGSBipedModelList,
	public BGSPickupPutdownSounds
{
public:
	TESObjectARMO();
	~TESObjectARMO();

	UInt16			modifiesVoice;
	Float32			damageThreshold;
	UInt32			armorFlags;
	UInt32			unk184;
	TESObjectARMO*	audioTemplate;
	UInt8			overrideSounds;
	UInt8			pad18D[3];

	UInt32	GetArmorValue(UInt32);
};
static_assert(sizeof(TESObjectARMO) == 0x190);