#pragma once

#include "ImageSpaceEffect.hpp"

class DepthOfFieldTextures : public ImageSpaceEffect {
public:
	NiTPrimitiveArray<ImageSpaceTexture> pDOFTextures;
};

class ImageSpaceEffectDepthOfField : public DepthOfFieldTextures {
public:
	float float68;
	float float6C;
	float fStrength;
	DWORD dword74;
	float fUnk78;
	ImageSpaceTexture DOFMask;
	ImageSpaceTexture BufferA[3];

	bool IsStrengthActive() { return fStrength > 0.0f; }

	BSRenderedTexture* GetDOFMask();

	void Toggle(bool bEnable) { *(bool*)0x12023D4 = bEnable; }

	void ClearTexture() { (&DOFMask)->Reset(); }
};

ASSERT_SIZE(ImageSpaceEffectDepthOfField, 0xBC);