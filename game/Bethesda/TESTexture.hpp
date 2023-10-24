#pragma once
#include "BaseFormComponent.hpp"
#include "BSString.hpp"
// Complete

// 0xC
class TESTexture : public BaseFormComponent {
public:
	TESTexture();

	virtual UInt32	Unk_04();
	virtual void	GetNormalMap(BSStringT* str);
	virtual char*	GetPathRoot();

	BSStringT		kTexturePath;

	const char*		GetTextureName();
	UInt32			GetTextureNameLength();
};
static_assert(sizeof(TESTexture) == 0xC);