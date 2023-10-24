#pragma once
#include "IMemoryHeap.hpp"

class AbstractHeap : public IMemoryHeap {
public:
	virtual void*	Unk_12(int, int);
	virtual void	Unk_13();
	virtual void	Unk_14(int a1, int a2, int a3);
	virtual void	Unk_15(int a1, int a2, int a3);
	virtual void	Unk_16();
	virtual void	Unk_17(int a2, int a3);

	const char* pName;
	DWORD dword8;
	DWORD dwordC;
	DWORD iPageSize;
	DWORD MemHeapSize;
	DWORD iInitialSize;
	DWORD iCurrentSize;
	DWORD dword20;
	DWORD dword24;
	DWORD dword28;
	DWORD dword2C;
	char* pMemHeap;
	DWORD dword34;
	DWORD dword38;
	DWORD dword3C;
	DWORD dword40;
	DWORD list44[2048];
	DWORD unk2044;
	BYTE list2048[8];
	DWORD dword2050;
	DWORD dword2054;
	DWORD list2058[32];
	_RTL_CRITICAL_SECTION rtl_critical_section20D8;
};
