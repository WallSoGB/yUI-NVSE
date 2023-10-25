#pragma once
#include "BSExtraData.hpp"
#include "ExtraDataList.hpp"

class TESObjectREFR;
class InventoryChanges;

// 0x10
class ExtraContainerChanges : public BSExtraData {
public:
	ExtraContainerChanges();
	virtual ~ExtraContainerChanges();

//	typedef std::vector<EntryData*> DataArray;
//	typedef std::vector<ExtendDataList*> ExtendDataArray;

	InventoryChanges* data;	// 00C

	EntryData* GetByType(TESForm* type);

	void DebugDump();
	void Cleanup();	// clean up unneeded extra data from each EntryData
	ExtendDataList* Add(TESForm* form, ExtraDataList* dataList = NULL);
	bool Remove(TESForm* form, ExtraDataList* dataList = NULL, bool bFree = false);
	ExtraDataList* SetEquipped(TESForm* obj, bool bEquipped, bool bForce = false);

	// get EntryData and ExtendData for all equipped objects, return num objects equipped
	UInt32 GetAllEquipped(DataArray& outEntryData, ExtendDataArray& outExtendData);

	static ExtraContainerChanges* Create();
	static ExtraContainerChanges* Create(TESObjectREFR* thisObj, UInt32 refID = 0, UInt32 count = 1,
		ExtraContainerChanges::ExtendDataList* pExtendDataList = NULL);
	static ExtraContainerChanges* GetForRef(TESObjectREFR* refr);

	// find the equipped item whose form matches the passed matcher
	struct FoundEquipData {
		TESForm* pForm;
		ExtraDataList* pExtraData;
	};
	FoundEquipData FindEquipped(FormMatcher& matcher) const;

	EntryDataList* GetEntryDataList() const {
		return data ? data->objList : NULL;
	}
};
static_assert(sizeof(ExtraContainerChanges) == 0x10);

//typedef ExtraContainerChanges::DataArray ExtraContainerDataArray;
//typedef ExtraContainerChanges::ExtendDataArray ExtraContainerExtendDataArray;
//typedef ExtraContainerChanges::FoundEquipData EquipData;