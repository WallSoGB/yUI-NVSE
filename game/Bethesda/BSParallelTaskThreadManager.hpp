#pragma once

#include "BSParallelTaskThread.hpp"
#include "BSParallelTask.hpp"

typedef void(__cdecl* BSParallelTaskThreadCallback)(BSParallelTask* apTask);

class BSParallelTaskThreadManager {
public:
	BSParallelTaskThread**				ppThreads;
	BSParallelTaskThreadCallback		pCallback;
	BSParallelTask*						pTask;
	bool								bActive;

	static BSParallelTaskThreadManager* GetSingleton();

	void AddIteratorTask(BSParallelTask* apTask);
	void AddTask(BSParallelTaskThreadCallback apCallback, BSParallelTask* apTask);

	void Start();
	void RunTask();
	void Release();
};