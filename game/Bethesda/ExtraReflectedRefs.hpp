#pragma once

#include "BSExtraData.hpp"
#include "BSSimpleList.hpp"

class TESObjectREFR;

class ExtraReflectedRefs : public BSExtraData {
public:
	BSSimpleList<TESObjectREFR*> lReflectedRefs;
};