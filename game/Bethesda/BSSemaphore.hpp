#pragma once

struct BSSemaphore {
	UInt32 uiCount;
	HANDLE hSemaphore;
	UInt32 uiMaxCount;
};