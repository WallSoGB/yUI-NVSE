#pragma once

#include "bhkSerializable.hpp"
#include "hkVector4.hpp"
#include "NiAVObject.hpp"

class TESTrapListener;
class TESWaterListener;
class BGSAcousticSpaceListener;
class bhkEntityListener;

class bhkWorld : public bhkSerializable {
public:
	virtual void Update();
	virtual void PickObject( void* arPickData);
	virtual void Unk_51();
	virtual void AddObjects(NiAVObject* apObject, bool abRecurse, bool abNotify, int aiGroup, bool abForce);
	virtual void Unk_53(void*, NiObjectNET*);
	virtual void SetDebugDisplay(void*, bool abTF);

	NiRefObject* pVisDebug;
	UInt8 bAdded;
	UInt8 bEnabled;
	bool bDebugDisplay;
	UInt8 gap17;
	UInt32 count18;
	UInt32 iBatchRemove;
	TESTrapListener* pTrapListener;
	TESWaterListener* pWaterListener;
	BGSAcousticSpaceListener* pAcousticSpaceListener;
	void** pEntityBatch;
	void* iEntityBatchCount;
	void** pConstraintInstanceBatch;
	void* iConstraintInstanceBatchCount;
	void** pActionBatch;
	void* unk40;
	void* ptr44;
	SInt32 iConstraintInstanceBatchCount;
	void** pEntityRemoveBatch;
	UInt32 iEntityRemoveBatchCount;
	UInt32 unk54;
	UInt32 unk58;
	UInt32 unk5C;
	hkVector4 Origin;
	bhkEntityListener** listenerArray;
	UInt32 numListeners;
	UInt32 unk78;
	UInt32 unk7C;
	UInt32 unk80;
	UInt32 unk84;
	UInt32 unk88;
	UInt32 unk8C;
	UInt32 unk90;
	UInt32 unk94;
	UInt32 unk98;
	UInt32 unk9C;
};

STATIC_ASSERT(sizeof(bhkWorld) == 0xA0);