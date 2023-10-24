#pragma once

#include "BSSemaphore.hpp"

class BSTaskThread {
public:
	virtual void Destroy(bool doFree);
	virtual void ThreadProc();

	HANDLE threadHandle;
	DWORD dword8;
	BSSemaphore semaphore1;
	BSSemaphore semaphore2;
	DWORD dword24;
	DWORD dword28;
	DWORD dword2C;

	static BSTaskThread* __fastcall CreateThreadEx(BSTaskThread* apThis, void*, void*, const char* apName) {
		ThisStdCall(0xC42DD0, apThis, 0, apName);
		SetThreadName(apThis->threadHandle, apName);
		return apThis;
	}
};

ASSERT_SIZE(BSTaskThread, 0x30);