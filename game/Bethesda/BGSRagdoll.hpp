#pragma once
#include "TESForm.hpp"
#include "TESModel.hpp"

// 0x148
class BGSRagdoll :
	public TESForm,
	public TESModel 
{
public:
	BGSRagdoll();
	~BGSRagdoll();

	UInt32	unk030[(0x148 - 0x30) >> 2];	// 030
};
static_assert(sizeof(BGSRagdoll) == 0x148);