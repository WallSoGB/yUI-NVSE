#pragma once
#include "BSExtraData.hpp"
#include "ExtraDataList.hpp"

class TESObjectREFR;
class InventoryChangesList;

// 0x10
class ExtraContainerChanges : public BSExtraData {
public:
	ExtraContainerChanges();
	virtual ~ExtraContainerChanges();

//	typedef std::vector<EntryData*> DataArray;
//	typedef std::vector<ExtendDataList*> ExtendDataArray;

	struct Data
	{
		InventoryChangesList*	inventoryChangesList;	// 000
		TESObjectREFR*			owner;		// 004
		Float32					totalWgCurrent;
		Float32					totalWgLast;
		UInt8					byte10;		// 010	referenced in relation to scripts in container
		UInt8					pad[3];

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
	static_assert(sizeof(Data) == 0x14);

	Data* data;	// 00C

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