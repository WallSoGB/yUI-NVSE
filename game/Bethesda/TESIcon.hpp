#pragma once
#include "TESTexture.hpp"
// Complete

// 0xC
class TESIcon : public TESTexture {
public:
	TESIcon();

	void SetPath(const char* newPath) { kTexturePath.Set(newPath); }
};
static_assert(sizeof(TESIcon) == 0xC);