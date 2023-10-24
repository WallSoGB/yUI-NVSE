#pragma once
#include "AStarQueue.hpp"

// 0x2058
class AStarSearch {
public:
	struct Unk10
	{
		void*	unk000[2039];
		UInt32	byte1FDC;
	};

	void*		vtable;
	UInt32		scrapHeapBuffer;
	UInt32		unk004;
	UInt32		unk008;
	UInt32		unk00C;
	AStarSearch::Unk10 struct010;
	AStarQueue	struct1FF4;
	UInt32		unk2048;
	AStarNode*	unk204C;
	UInt32		unk2050;
	UInt8		bIsRunningInTasklet;
	UInt8		gap2055[3];
};
static_assert(sizeof(AStarSearch) == 0x2058);