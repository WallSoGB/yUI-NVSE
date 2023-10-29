#pragma once
#include "BaseFormComponent.hpp"
#include "BSString.hpp"

// 0xC
class TESTexture : public BaseFormComponent {
public:
	TESTexture();

	virtual UInt32	Unk_04();
	virtual void	GetNormalMap(BSStringT<char>* str);
	virtual char*	GetPathRoot();

	BSStringT<char>	kTexturePath;

	const char*		GetTextureName();
	UInt32			GetTextureNameLength();
};
static_assert(sizeof(TESTexture) == 0xC);