#pragma once
#include "TESBoundObject.hpp"
#include "BGSIdleCollection.hpp"

// 0x40
class BGSIdleMarker : public TESBoundObject
{
public:
	BGSIdleCollection kIdleCollection;
};
static_assert(sizeof(BGSIdleMarker) == 0x40);