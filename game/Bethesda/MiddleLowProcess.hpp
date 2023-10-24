#pragma once
#include "LowProcess.hpp"

// 0C8
class MiddleLowProcess : public LowProcess {
public:
	MiddleLowProcess();
	~MiddleLowProcess() override;

	virtual void	SetAnimation(UInt32 newAnimation);

	UInt32				unk0B4;			// 0B4
	ActorValueModifiers	tempModifiers;	// 0B8
};
static_assert(sizeof(MiddleLowProcess) == 0xC8);