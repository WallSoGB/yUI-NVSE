#pragma once
#include "TESForm.hpp"
#include "BGSPreloadable.hpp"

// 24
class BGSDebris :
	public TESForm,
	public BGSPreloadable
{
	BGSDebris();
	~BGSDebris();

	UInt32			unk01C;
	UInt32			unk020;
};
static_assert(sizeof(BGSDebris) == 0x24);