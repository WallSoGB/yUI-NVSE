#pragma once

class MobIterOperator {
public:
	MobIterOperator() { ThisStdCall(0x872E29, this); };
	~MobIterOperator();

	virtual void Operate();

	UInt32 unk04;
};