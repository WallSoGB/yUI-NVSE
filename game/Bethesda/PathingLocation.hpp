#pragma once
#include "NiPoint3.hpp"

class TESObjectCELL;
class TESWorldSpace;
class BGSSaveFormBuffer;

// 0x28
class PathingLocation : public NiPoint3 
{
public:
	virtual void  Write(BGSSaveFormBuffer* apBuffer);
	virtual void  Read(BGSSaveFormBuffer* apBuffer);

	void*			pNavMesh;
	void*			pNavmeshInfoMap;
	TESObjectCELL*	pCell;
	TESWorldSpace*	pWorldSpace;
	UInt32			unk020;
	UInt16			usTriangle;
	UInt8			ucFlags;
	UInt8			ucClientData;
};
static_assert(sizeof(PathingLocation) == 0x28);