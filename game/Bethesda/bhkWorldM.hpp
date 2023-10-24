#pragma once

#include "bhkWorld.hpp"

class bhkWorldM : public bhkWorld {
public:
	NiPoint4 WorldTotalSize;
	NiPoint4 BorderSize;
	NiPoint4 broadPhaseSize;
};
