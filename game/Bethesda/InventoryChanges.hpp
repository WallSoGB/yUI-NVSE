#pragma once

struct InventoryChanges
{
	ExtendDataList*				extendData;		// 00
	SInt32						countDelta;		// 04
	TESForm*					form;			// 08

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
static_assert(sizeof(InventoryChanges) == 0xC);

struct InventoryChangesList : BSSimpleList<InventoryChanges*>
{
	InventoryChanges* FindForItem(TESForm* item);
	void							Free(bool bFreeList);
	static InventoryChangesList* Create(UInt32 refID, UInt32 count, ExtendDataList* pExtendDataList);
};
static_assert(sizeof(InventoryChangesList) == 0x8);

//typedef std::vector<ExtendDataList*> ExtendDataArray;


struct InventoryItemData
{
	SInt32								count;
	InventoryChanges* entry;

	InventoryItemData(SInt32 count, InventoryChanges* entry) : count(count), entry(entry) {}
};
static_assert(sizeof(InventoryItemData) == 0x08);

typedef std::vector<InventoryChanges*> InventoryChangesArray;

struct AmmoInfo
{
	void* unk00;	// 00
	UInt32	count;	// 04
	TESAmmo* ammo;	// 08
	UInt32	unk0C;	// 0C
	UInt32	unk10;	// 10
	UInt32	unk14;	// 14
	UInt32	unk18;	// 18
	UInt32	unk1C;	// 1C
	UInt32	unk20;	// 20
	UInt32	unk24;	// 24
	UInt32	unk28;	// 28
	UInt32	unk2C;	// 2C
	UInt32	unk30;	// 30
	UInt32	unk34;	// 34
	UInt32	unk38;	// 38
	UInt32	unk3C;	// 3C
	UInt32	unk40;	// 40
	TESObjectWEAP* weapon;	// 44
};

struct WeaponInfo
{
	ExtraDataList** xData;
	UInt32			unk04;
	TESObjectWEAP* weapon;

	ExtraDataList* GetExtraData()
	{
		return xData ? *xData : NULL;
	}
};
