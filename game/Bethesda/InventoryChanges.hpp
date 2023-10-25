#pragma once
#include "BSSimpleList.hpp"

class ExtraDataList;
class TESBoundObject;

class InventoryEntryData
{
public:

	BSSimpleList<ExtraDataList*>*	pkExtraLists;		// 00
	SInt32							iCountDelta;		// 04
	TESBoundObject*					pkObject;			// 08

	void						Free(bool bFreeList = false);
	void						Cleanup();
	static InventoryChanges*	Create(TESForm* pForm, UInt32 count = 1, ExtendDataList* pExtendDataList = nullptr);
	ExtendDataList*				Add(ExtraDataList* newList);
	bool						Remove(ExtraDataList* toRemove, bool bFree = false);
	bool						HasExtraLeveledItem();
	void						RemoveCannotWear();
	ExtraDataList*				GetEquippedExtra();
	ExtraDataList*				GetCustomExtra(UInt32 whichVal);
	BSExtraData*				GetExtraData(UInt32 whichVal);
	float						CalculateWeaponDamage(float condition, TESForm* ammo);
	float						GetValue();
	bool						HasWeaponMod(UInt32 modEffect) { return ThisStdCall<bool>(0x4BDA70, this, modEffect); }
	UInt32						GetWeaponNumProjectiles(Actor* owner);
	bool						ShouldDisplay();

	UInt8						GetWeaponMod();
	__forceinline Float64		GetHealthPercent(char a1 = 0) { return ThisCall<Float64>(0x4BCDB0, this, a1); };
	Float64						GetHealthPercentAlt(bool axonisFix = false, bool checkDestruction = true);
	bool						GetEquipped();
	ExtraDataList*				GetExtraData() const;
	UInt32						GetClipSize();
	void						Equip(Actor* actor, ExtraDataList* extra = nullptr);

	enum
	{
		kHotkeyMin = 0,
		kHotkey0 = kHotkeyMin,
		kHotkey1,
		kHotkey2,
		kHotkey3,
		kHotkey4,
		kHotkey5,
		kHotkey6,
		kHotkey7,
		kHotkeyMax = kHotkey7,
		kHotkey8,
		kHotkeyStewie = kHotkey8
	};

	void Cleanup();
	static EntryData* Create(UInt32 refID = 0, UInt32 count = 1, ExtraContainerChanges::ExtendDataList* pExtendDataList = NULL);
	static EntryData* Create(TESForm* pForm, UInt32 count = 1, ExtraContainerChanges::ExtendDataList* pExtendDataList = NULL);
	ExtendDataList* Add(ExtraDataList* newList);
	bool Remove(ExtraDataList* toRemove, bool bFree = false);

	bool HasExtraLeveledItem()
	{
		if (!extendData) return false;
		for (auto iter = extendData->Begin(); !iter.End(); ++iter)
			if (iter->HasType(kExtraData_LeveledItem)) return true;
		return false;
	}
};
static_assert(sizeof(InventoryEntryData) == 0xC);

//typedef std::vector<ExtendDataList*> ExtendDataArray;

class InventoryChanges
{
public:
	BSSimpleList<InventoryEntryData*>*	pkEntryList;	// 000
	TESObjectREFR*						pkOwner;		// 004
	Float32								fTotalWgCurrent;
	Float32								fTotalWgLast;	// armor in sse
	UInt8								bChanged;		// 010	referenced in relation to scripts in container
	UInt8								pad[3];

	static Data* Create(TESObjectREFR* owner);

	Float64								GetInventoryWeight();


	void							Cleanup();	// clean up unneeded extra data from each EntryData
	ExtendDataList* Add(TESForm* form, ExtraDataList* dataList = NULL);
	bool							Remove(TESForm* form, ExtraDataList* dataList = NULL, bool bFree = false);
	ExtraDataList* SetEquipped(TESForm* obj, bool bEquipped, bool bForce = false);
	// get EntryData and ExtendData for all equipped objects, return num objects equipped
	UInt32							GetAllEquipped(InventoryChangesArray& outEntryData);

	static ExtraContainerChanges* GetForRef(TESObjectREFR* refr);
};
static_assert(sizeof(InventoryChanges) == 0x14);

struct InventoryItemData
{
	SInt32				count;
	InventoryEntryData*	entry;

	InventoryItemData(SInt32 count, InventoryEntryData* entry) : count(count), entry(entry) {}
};
static_assert(sizeof(InventoryItemData) == 0x08);

typedef std::vector<InventoryChanges*> InventoryChangesArray;