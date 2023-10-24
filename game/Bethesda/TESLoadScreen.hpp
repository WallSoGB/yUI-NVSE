#pragma once
#include "TESForm.hpp"
#include "TESTexture.hpp"
#include "TESDescription.hpp"

// 0x3C
class TESLoadScreen : public TESForm, public TESTexture, public TESDescription
{
public:
	TESLoadScreen();
	~TESLoadScreen();

	UInt32	unk2C[(0x3C - 0x2C) >> 2];	// 02C
};
static_assert(sizeof(TESLoadScreen) == 0x3C);