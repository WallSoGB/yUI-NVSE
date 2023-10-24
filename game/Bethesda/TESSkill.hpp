#pragma once
#include "TESForm.hpp"
#include "TESTexture.hpp"
#include "TESDescription.hpp"

// 60
class TESSkill : public TESForm {
public:
	TESSkill();
	~TESSkill();

	TESDescription	kDescription;
	TESTexture		kTexture;
	UInt32			unk2C;
	UInt32			unk30;
	UInt32			unk34;
	Float32			unk38[2];
	TESDescription	kDesc2[4];
};
static_assert(sizeof(TESSkill) == 0x60);