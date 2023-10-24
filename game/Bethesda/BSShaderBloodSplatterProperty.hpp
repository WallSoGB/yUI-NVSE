#pragma once

#include "BSShaderProperty.hpp"

class BSShaderBloodSplatterProperty : public BSShaderProperty {
public:
	NiTexturePtr spTexture[2];
	DWORD dword68;
	DWORD dword6C;

	static __forceinline UInt32 GetShapeCount() { return *(UInt32*)0x11FF0F0; };
	static __forceinline void SetShapeCount(UInt32 uiCount) { *(UInt32*)0x11FF0F0 = uiCount; };
};

ASSERT_SIZE(BSShaderBloodSplatterProperty, 0x70)