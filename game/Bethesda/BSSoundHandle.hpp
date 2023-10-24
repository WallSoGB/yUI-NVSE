#pragma once

// 0xC
struct BSSoundHandle
{
	UInt32	uiSoundID;
	bool	bAssumeSuccess;
	UInt32	uiState;
};
static_assert(sizeof(BSSoundHandle) == 0xC);