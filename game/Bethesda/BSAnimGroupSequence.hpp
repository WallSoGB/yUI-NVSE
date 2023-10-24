#pragma once

#include "NiControllerSequence.hpp"

class TESAnimGroup;

class BSAnimGroupSequence : public NiControllerSequence {
public:
	BSAnimGroupSequence();
	~BSAnimGroupSequence();

	TESAnimGroup* animGroup;	//068
};