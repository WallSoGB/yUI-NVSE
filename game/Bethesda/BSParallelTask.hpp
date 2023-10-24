#pragma once

typedef bool(__cdecl* BSParallelTaskCallback)(void*, void*);

struct BSParallelTask {
	BSParallelTask(BSParallelTaskCallback apFunc, void* apArray, UInt32 auiSize);

	BSParallelTaskCallback	pCallBack;
	void*					pArray; // BSSimpleArray
	UInt32					uiSize;
	UInt32					uiPosition;
};