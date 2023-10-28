#pragma once

#include "BSRenderedTexture.hpp"
#include "BSGraphics.hpp"

class ImageSpaceTexture : public BSMemObject {
public:
	ImageSpaceTexture() : spTexture(0), iFilterMode(TEXTURE_FILTER_MODE_DEFAULT), iClampMode(TEXTURE_ADDRESS_MODE_DEFAULT), byte0(false), bIsRenderedTexture(false), bAcquiredTarget(false) { };
	ImageSpaceTexture(TextureFilterMode aeFilter, TextureAddressMode aeClamp) : spTexture(0), iFilterMode(aeFilter), iClampMode(aeClamp), byte0(false), bIsRenderedTexture(false), bAcquiredTarget(false) { };
	~ImageSpaceTexture();

	bool				byte0;
	bool				bIsRenderedTexture;
	bool				bAcquiredTarget;
	NiObjectPtr			spTexture;
	TextureFilterMode	iFilterMode;
	TextureAddressMode	iClampMode;

	BSRenderedTexture*	GetRenderTarget();
	NiTexture*			GetTexture();
	void				SetRenderTarget(BSRenderedTexture* apNewTexture);
	void				SetTexture(NiTexture* apNewTexture);
	void				Reset();
};

ASSERT_SIZE(ImageSpaceTexture, 0x10);