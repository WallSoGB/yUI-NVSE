#pragma once

#include "BSShaderLightingProperty.hpp"

class SpeedTreeShaderLightingProperty : public BSShaderLightingProperty {
public:
	UInt32	Unk07C[3];	// 07C
};

ASSERT_SIZE(SpeedTreeShaderLightingProperty, 0x88);