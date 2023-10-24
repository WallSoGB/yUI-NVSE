#pragma once

#include "InterfacedClass.hpp"

class BSThread {
public:
	virtual ~BSThread();
	virtual bool ThreadProc();

	_RTL_CRITICAL_SECTION criticalsection;
	HANDLE createdThread;
	HANDLE creatorThread;
	UInt32 threadID;
	UInt32 creatorThreadID;
	bool bIsInitialised;

	static void __fastcall CreateAndResumeThread_Hook(BSThread* apThis, void*, SIZE_T dwStackSize, const char* apName, bool abSuspended) {
		ThisStdCall(0xAA6430, apThis, dwStackSize, apName, abSuspended);
		SetThreadName(apThis->createdThread, apName);
	}
};

ASSERT_SIZE(BSThread, 0x30);