#pragma once
#include "BSSimpleList.hpp"
#include "BSPointer.hpp"

class BSExtraData;
class TESObjectREFR;

// 0x20
struct BaseExtraList 
{
	virtual ~BaseExtraList();

	bool HasType(UInt32 type) const;
	__forceinline BSExtraData* GetByType(UInt8 type) const { return ThisStdCall<BSExtraData*>(0x410220, this, type); }
	void MarkType(UInt32 type, bool bCleared);
	__forceinline void Remove(BSExtraData* toRemove, bool doFree) { ThisStdCall(0x410020, this, toRemove, doFree); }
	__forceinline void RemoveByType(UInt32 type) { ThisStdCall(0x410140, this, type); }
	__forceinline BSExtraData* Add(BSExtraData* toAdd) { return ThisStdCall<BSExtraData*>(0x40FF60, this, toAdd); }
	__forceinline void RemoveAll(bool doFree) { ThisStdCall(0x40FAE0, this, doFree); }
	bool MarkScriptEvent(UInt32 eventMask, TESForm* eventTarget);
	__forceinline void Copy(BaseExtraList* from) { ThisStdCall(0x411EC0, this, from); }

	BSExtraData*	pkData;						// 004
	UInt8			ucPresenceBitfield[0x15];	// 008 - if a bit is set, then the extralist should contain that extradata
	// bits are numbered starting from the lsb
	UInt8			pad1D[3];					// 01D UInt8 jip flags UInt16 jip perks info

	enum JIPExtraListFlags
	{
		kJIPExtraListFlag_Update3D				= 1 << 0,
		kJIPExtraListFlag_DisableCollision		= 1 << 1,
		kJIPExtraListFlag_AltRefName			= 1 << 2,
		kJIPExtraListFlag_RefrModelPath			= 1 << 3,
		kJIPExtraListFlag_RefNameOrModel		= kJIPExtraListFlag_AltRefName | kJIPExtraListFlag_RefrModelPath,
		kJIPExtraListFlag_NoZPosReset			= 1 << 4,
	};
};
static_assert(sizeof(BaseExtraList) == 0x20);

// 0x20
struct ExtraDataList : public BaseExtraList 
{
	virtual ~ExtraDataList();

	static ExtraDataList* Create(BSExtraData* xBSData = NULL);

	BSSimpleList<BSPointer<TESObjectREFR>*>* GetReflectedRefs(); // walltuh
	void* GetRefractionProperty();
};
static_assert(sizeof(ExtraDataList) == 0x20);

class ExtendDataList : public BSSimpleList<ExtraDataList*>
{
public:
	static ExtendDataList* Create(ExtraDataList* pExtraDataList = nullptr);
	static void Free(ExtendDataList* xData, bool bFreeList = false);
	static bool Add(ExtendDataList* xData, ExtraDataList* xList);
	static bool Remove(ExtendDataList* xData, ExtraDataList* xList, bool bFreeList = false);
	SInt32 AddAt(ExtraDataList* item, SInt32 index);
	void RemoveAll() const;
	ExtraDataList* RemoveNth(SInt32 n);
};