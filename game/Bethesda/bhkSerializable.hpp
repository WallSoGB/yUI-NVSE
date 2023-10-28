#pragma once
#include "bhkRefObject.hpp"

class bhkWorld;
class hkSerializableCinfo;

class bhkSerializable : public bhkRefObject {
public:
	bhkSerializable();
	virtual ~bhkSerializable();

	virtual void*	Unk_37();							// 37
	virtual void*	GetWorld();							// 38
	virtual bool	Add(bhkWorld* apWorld);				// 39
	virtual bool	Remove();							// 40
	virtual void	KillCInfo(bool abCreated);			// 41
	virtual UInt32	GetCinfoSize();						// 42
	virtual UInt32	LoadCInfo(NiStream* arStream);		// 43
	virtual void	Init(void*);						// 44
	virtual void*	CreateHavokData(void*);				// 45
	virtual void*	Kill();								// 46
	virtual void*	KillCInfo2(UInt32);					// 47 | Figure out the name
	virtual void*	Unk_48();							// 48

	hkSerializableCinfo* pInfo;
};
static_assert(sizeof(bhkSerializable) == 0x10);