#pragma once

#include "BSFaceGenKeyframe.hpp"

class BSFaceGenKeyframeMultiple : public BSFaceGenKeyframe {
public:
	float* morphValues;
	UInt32 numMorphs;
};

ASSERT_SIZE(BSFaceGenKeyframeMultiple, 0x14)