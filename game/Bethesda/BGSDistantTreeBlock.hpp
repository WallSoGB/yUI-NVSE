#pragma once
#include "BSSimpleArray.hpp"
#include "BSResizableTriShape.hpp"
#include "BSDistantTreeShaderProperty.hpp"
#include "BSMap.hpp"

struct BGSTerrainNode;

// 0x4C
struct BGSDistantTreeBlock {
	struct InstanceData {
		UInt32		id;
		UInt16		x;
		UInt16		y;
		UInt16		z;
		Float32		fRotZ;
		Float32		fScale;
		UInt32		unk18;
		UInt32		unk1C;
		bool		bHidden;
	};

	struct TreeGroup {
		void*	unk00;
		BSResizableTriShapePtr spGeometry;
		BSSimpleArray<BGSDistantTreeBlock::InstanceData*> Instances;
		UInt32	uiNum;
		bool	bShaderPropertyUpToDate;
	};

	void* pLoadTask;
	BSSimpleArray<BGSDistantTreeBlock::TreeGroup*>		kTreeGroups;
	BSMap<UInt32, BGSDistantTreeBlock::InstanceData*>	kInstanceMap;
	BSMap<UInt32, BGSDistantTreeBlock::TreeGroup*>		kNextGroup;
	BSSimpleArray<UInt32> kUIntArray;
	BGSTerrainNode* pkNode;
	bool bDoneLoading;
	bool bAttached;
	bool bAllVisible;

	void UpdateShaderPropertyRecurse();
	void UpdateShaderProperty(BSDistantTreeShaderProperty* apShaderProp, BGSDistantTreeBlock::TreeGroup* apGroup);
	void HideLOD(UInt32 aID, bool unk3);

};
static_assert(sizeof(BGSDistantTreeBlock) == 0x4C);