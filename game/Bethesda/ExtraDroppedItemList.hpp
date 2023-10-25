#pragma once
#include "BSExtraData.hpp"
#include "TESObjectREFR.hpp"

// 0x14
class ExtraDroppedItemList : public BSExtraData
{
public:
	BSSimpleList<TESObjectREFR*> kDroppedItemList;
};
static_assert(sizeof(ExtraDroppedItemList) == 0x14);