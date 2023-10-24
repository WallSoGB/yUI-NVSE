#pragma once

#include "ImageSpaceTexture.hpp"
#include "ImageSpaceShaderParam.hpp"
#include "ImageSpaceEffectParam.hpp"
#include "BSGraphics.hpp"

class ImageSpaceManager;
class NiScreenGeometry;
class NiDX9Renderer;
class ImageSpaceShader;

class ImageSpaceEffect {
public:
	virtual void Destroy(bool doFree);
	virtual void RenderShader(NiGeometry* apScreenShape, NiDX9Renderer* pkRenderer, ImageSpaceEffectParam* apParam, bool abEndFrame);
	virtual void Setup(ImageSpaceManager* pISManager, ImageSpaceEffectParam* apParam);
	virtual void Shutdown();
	virtual void BorrowTextures(ImageSpaceEffectParam* apParam);
	virtual void ReturnTextures();
	virtual bool IsActive();
	virtual bool UpdateParams(ImageSpaceEffectParam* apParam);

	struct EffectInput {
		int iTexIndex;
		TextureFilterMode iFilterMode;
	};


	bool								bIsActive;
	bool								bParamsChanged;
	NiTArray<ImageSpaceShader*>			kShaders;
	NiTArray<ImageSpaceShaderParam*>	kShaderParams;
	NiTArray<ImageSpaceTexture*>		kTextures;
	NiTArray<EffectInput*>				kShaderInputs;
	NiTArray<UInt32*>					kShaderOutputs;

	void SetTexture(UInt32 aiIndex, ImageSpaceTexture* apTex, TextureFilterMode aiFilterMode) {
		ThisStdCall(0xBA3CB0, this, aiIndex, apTex, aiFilterMode);
	}
};

ASSERT_SIZE(ImageSpaceEffect, 0x58)