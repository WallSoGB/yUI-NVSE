#pragma once

#include "LockFreeMap.hpp"
#include "NiSmartPointer.hpp"
#include "BSTaskManagerThread.hpp"

class IOTask;

class BSTaskManager : public LockFreeMap<__int64, NiPointer<BSTask>> {
public:
	virtual bool	Unk18(void*);
	virtual void*	Unk19(void*);
	virtual bool	Unk20(IOTask* apTask);
	virtual void	Unk21();
	virtual void*	Unk22(void*);

	BYTE byte40;
	DWORD dword44;
	DWORD dword48;
	UInt32 uiThreadCount;
	BSTaskManagerThread** ppThreads;
	void* pvoid54;
	DWORD dword58;
};

ASSERT_SIZE(BSTaskManager, 0x5C);