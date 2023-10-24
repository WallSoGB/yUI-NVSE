#pragma once

#include "NiDX9TextureData.hpp"
#include "NiPalette.hpp"

NiSmartPointer(NiDX9SourceTextureData);

class NiDX9SourceTextureData : public NiDX9TextureData {
public:
	NiDX9SourceTextureData();
	virtual ~NiDX9SourceTextureData();

	bool			m_bReplacementData;
	bool			m_bMipmap;
	UInt32			m_uiFormattedSize;
	NiPalettePtr	m_spPalette;
	UInt32			m_uiLevelsSkipped;
	UInt32			m_uiSourceRevID;
	UInt32			m_uiPalRevID;
};

ASSERT_SIZE(NiDX9SourceTextureData, 0x84);