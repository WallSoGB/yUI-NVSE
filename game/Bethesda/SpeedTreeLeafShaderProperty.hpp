#pragma once

#include "SpeedTreeShaderLightingProperty.hpp"
class SpeedTreeLeafShaderProperty : public SpeedTreeShaderLightingProperty {
public:
	struct LeafData {
		UInt32		unk00;
		UInt32		unk04;
		float*		leafBase; // pointer to float4[48]
	};

	LeafData* leafData;	// 088
};

ASSERT_SIZE(SpeedTreeLeafShaderProperty, 0x8C);