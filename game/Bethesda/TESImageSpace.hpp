#pragma once
#include "TESForm.hpp"

// 0x80
class TESImageSpace : public TESForm {
public:
	TESImageSpace();
	~TESImageSpace();

	Float32 traitValues[33];
	UInt32 unk9C[5];
};
static_assert(sizeof(TESImageSpace) == 0xB0);