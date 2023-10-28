#pragma once

// 0x18
class BSTask {
public:
	BSTask();
	enum BS_TASK_STATE {
		BS_TASK_STATE_PENDING = 0x0,
		BS_TASK_STATE_QUEUED = 0x1,
		BS_TASK_STATE_MOVING = 0x2,
		BS_TASK_STATE_RUNNING = 0x3,
		BS_TASK_STATE_FINISHED = 0x4,
		BS_TASK_STATE_COMPLETED = 0x5,
		BS_TASK_STATE_CANCELED = 0x6,
		BS_TASK_STATE_POST_PROCESSING = 0x7,
	};

	virtual			~BSTask();
	virtual void	Run();
	virtual void	AddTask();
	virtual void	Cancel(BS_TASK_STATE aeState, void* arg1);
	virtual bool	GetDescription(const char* apDescription, size_t aiBufferSize);

	BSTask* unk04;
	UInt32 uiRefCount;
	BS_TASK_STATE eState;
#pragma pack(push, 4)
	UInt64 llKey;
#pragma pack(pop)

	static UInt32* GetCounterSingleton();
};
static_assert(sizeof(BSTask) == 0x18);