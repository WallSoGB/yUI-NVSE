#pragma once
#include "TESForm.hpp"
#include "TESFullName.hpp"
#include "TESTexture.hpp"

// 34
class TESEyes : public TESForm {
public:
	TESEyes();
	~TESEyes();

	enum EnumEyesFlags : UInt8
	{
		kFlag_Playable = 0x01,
		kFlag_NotMale = 0x02,
		kFlag_NotFemale = 0x04,
	};

	TESFullName		kFullName;	// 18
	TESTexture		kTexture;	// 24

	EEyesFlags		eEyeFlags;	// 30
	UInt8			pad31[3];	// 31
};
static_assert(sizeof(TESEyes) == 0x34);