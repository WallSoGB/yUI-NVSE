#pragma once

#include "BSTask.hpp"

enum IO_TASK_PRIORITY {
	IO_TASK_PRIORITY_CRITICAL = 0x0,
	IO_TASK_PRIORITY_VERY_HIGH = 0x1,
	IO_TASK_PRIORITY_HIGH = 0x2,
	IO_TASK_PRIORITY_MID = 0x3,
	IO_TASK_PRIORITY_LOW = 0x4,
	IO_TASK_PRIORITY_VERY_LOW = 0x5,
	IO_TASK_PRIORITY_COUNT = 0x6,
	IO_TASK_PRIORITY_INVALID = 0x7,
	IO_TASK_PRIORITY_HIGHEST = 0x0,
	IO_TASK_PRIORITY_LOWEST = 0x5,
};

class IOTask : public BSTask {
public:
	IOTask();
	~IOTask() { ThisStdCall(0x440640, this); };

	virtual void PostProcess();
	virtual void GenerateKey();
	virtual void Requeue(IO_TASK_PRIORITY aeNewPriority);

	void IncRefCount();
	void DecRefCount();
	bool CompareState(BS_TASK_STATE Comperand, BS_TASK_STATE Exchange);
};