#pragma once
#include "TESRegionData.hpp"

class TESRegionGrassObjectList;

// 0xC
class TESRegionDataGrass : public TESRegionData {
public:
	TESRegionDataGrass();
	~TESRegionDataGrass();

	TESRegionGrassObjectList* TESRegionGrassObjectList;
};
static_assert(sizeof(TESRegionDataGrass) == 0xC);