#pragma once
#include "TESRegionData.hpp"

// 0xC
class TESRegionDataLandscape : public TESRegionData {
public:
	TESRegionDataLandscape();
	~TESRegionDataLandscape();

	TESTexture* pCanopyShadowTexture;
};
static_assert(sizeof(TESRegionDataLandscape) == 0xC);