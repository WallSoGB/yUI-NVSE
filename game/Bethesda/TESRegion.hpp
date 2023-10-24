#pragma once
#include "TESForm.hpp"
#include "TESWorldSpace.hpp"
#include "NiPoint3.hpp"
#include "BSSimpleList.hpp"
#include "TESRegionData.hpp"

class TESWeather;

// 0x38
class TESRegion : public TESForm {
public:
	TESRegion();
	~TESRegion();

	struct AreaPointEntry
	{
		float	x;
		float	y;
	};

	struct RegionAreaEntry
	{
		BSSimpleList<AreaPointEntry*>	kPoints;
		UInt32							unk08[2];
		Float32							unk10[4];
		UInt32							uiEdgeFallOff;
		UInt32							uiPointCount;
	};
	typedef BSSimpleList<RegionAreaEntry> RegionAreaEntryList;

	BSSimpleList<TESRegionData*>*	pkDataEntries;	// 18
	BSSimpleList<RegionAreaEntry*>*	pkAreaEntries;	// 1C
	TESWorldSpace*					pkWorldSpace;
	TESWeather*						pkWeather;
	Float32							unk28;
	NiPoint3						kExternalEmittance;
};
static_assert(sizeof(TESRegion) == 0x38);