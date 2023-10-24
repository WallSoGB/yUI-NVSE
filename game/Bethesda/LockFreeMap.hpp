#pragma once

#include "InterfacedClass.hpp"
#include "BSSpinLock.hpp"

// 40
template<typename _K, class _C>
class LockFreeMap : public InterfacedClass {
public:
	// 0C
	struct Data004 {
		UInt32	unk000;		// 00
		UInt32	unk004;		// 04
		UInt32* unk008;	// 08
	};

	// 24
	struct TLSValue {
		LockFreeMap*	pMap;				// 00
		UInt32			mapData004Unk000;	// 04
		UInt32			mapData004Unk008;	// 08
		UInt32*			mapData004Unk00C;	// 0C	stores first DWord of bucket during lookup, next pointer is data, next flags bit 0 is status ok/found
		UInt32			unk010;				// 10	stores bucketOffset during lookup
		UInt32*			unk014;			// 14	stores pointer to bucket during lookup
		UInt32*			unk018;			// 18
		UInt32			unk01C;				// 1C
		UInt32			unk020;				// 20
	};

	// 10
	struct Data014 {
		// 08
		struct Data008 {
			UInt32		uiThreadID;	// 00 threadID
			TLSValue*	pTLSValue;	// 04 lpTlsValue obtained from AllocateTLSValue of LockFreeMap
		};

		UInt32		uiAlloc;		// Init'd to arg0, count of array at 008
		UInt32		uiTLSDataIndex;	// Init'd by TlsAlloc
		Data008*	ppDat008;		// array of pair of DWord
		UInt32		uiCount;		// Init'd to 0
	};	// most likely an array or a map

	virtual bool	Lookup(_K key, _C* destination);
	virtual void	Unk_03(UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt8 arg4);
	virtual void	Insert(_K* key, void** dataPtr, UInt8 arg3);
	virtual void	EraseKey(_K* ke);
	virtual void	Unk_06(UInt32 arg1, UInt32 arg2);
	virtual void	Unk_07(UInt32 arg);
	virtual void	Unk_08(UInt32 arg1, UInt32 arg2);
	virtual UInt32	CalcBucketIndex(_K key);
	virtual void	FreeKey(void* key);
	virtual void	GenerateKey(void* src);
	virtual void	CopyKeyTo(void* src, void** destPtr);
	virtual void	LKeyGreaterOrEqual(void* lkey, void* rkey);
	virtual void	KeysEqual(void* lkey, void* rkey);
	virtual void	IncQueuedCount();
	virtual void	DecQueuedCount();
	virtual UInt32	GetQueuedCount();

	Data004**	dat004;		// 04 array of arg0 12 bytes elements (uninitialized)
	UInt32		uiNumBuckets;	// 08 Init'd to arg1, count of DWord to allocate in array at 000C
	UInt32**	ppBuckets;		// 0C array of arg1 DWord elements
	UInt32		unk010;			// 10 Init'd to arg2
	Data014*	dat014;		// 14 Init'd to a 16 bytes structure
	UInt32		uiQueuedCount;			// 18
	UInt32		unk01C;			// 1C
	BSSpinLock	Lock;
};
static_assert(sizeof(LockFreeMap<char const*, void*>) == 0x40);

template<class _C>
class LockFreeStringMap : LockFreeMap<char const*, _C> {};

template<class _C>
class LockFreeCaseInsensitiveStringMap : LockFreeStringMap<_C> {};