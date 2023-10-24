#pragma once
#include "NiNode.hpp"
#include "BSSimpleList.hpp"
#include "BSTempEffectGeometryDecal.hpp"

// 0xB4
class BGSDecalNode : public NiNode
{
public:
	BSSimpleList<NiPointer<BSTempEffectGeometryDecal>>* pkDecals;
	bool bSkinnedNode;
};
static_assert(sizeof(BGSDecalNode) == 0xB4);