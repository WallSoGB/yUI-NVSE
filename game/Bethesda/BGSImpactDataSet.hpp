#pragma once
#include "TESForm.hpp"
#include "BGSPreloadable.hpp"

// 0x4C
class BGSImpactDataSet :
	public TESForm,
	public BGSPreloadable
{
public:
	BGSImpactDataSet();
	~BGSImpactDataSet();

	UInt32	impactDatas[12];			// 01C
};
static_assert(sizeof(BGSImpactDataSet) == 0x4C);