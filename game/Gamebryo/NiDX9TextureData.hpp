#pragma once

#include "NiPersistentSrcTextureRendererData.hpp"
//#include "Defines.hpp"
#include "NiTexture.hpp"

class NiDX9Renderer;
class NiDX9SourceTextureData;
class NiDX9RenderedTextureData;
class NiDX9DynamicTextureData;

class NiDX9TextureData : public NiTexture::RendererData {
public:
	NiDX9TextureData();
	virtual ~NiDX9TextureData();

	virtual UInt32						GetLevels();
	virtual D3DBaseTexturePtr			GetD3DTexture();
	virtual void						SetD3DTexture(D3DBaseTexturePtr pkD3DTexture);
	virtual NiDX9RenderedTextureData*	GetAsRenderedTexture();
	virtual NiDX9SourceTextureData*		GetAsSourceTexture();
	virtual NiDX9DynamicTextureData*	GetAsDynamicTexture();
	virtual bool						InitializeFromD3DTexture(D3DBaseTexturePtr pkD3DTexture);

	NiDX9Renderer*		m_pkRenderer;
	D3DBaseTexturePtr	m_pkD3DTexture;
	UInt32				m_uiLevels;

	static NiPixelFormat* FindClosestPixelFormat(const NiTexture::FormatPrefs* kPrefs, NiPixelFormat* const* ppkDestFmts);

	bool SaveTexture(const char* path, D3DXIMAGE_FILEFORMAT aeFormat) {
		return D3DXSaveTextureToFile(path, aeFormat, m_pkD3DTexture, NULL);
	}
};

ASSERT_SIZE(NiDX9TextureData, 0x6C);