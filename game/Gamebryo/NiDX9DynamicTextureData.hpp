#pragma once
#include "NiDX9TextureData.hpp"

typedef LPDIRECT3DBASETEXTURE9 D3DBaseTexturePtr;

class NiDX9DynamicTextureData : public NiDX9TextureData {
public:
	NiDX9DynamicTextureData();
	virtual ~NiDX9DynamicTextureData();

	D3DBaseTexturePtr	m_pkD3DLockableSysMemTexture;
	bool				m_bTextureLocked;
};
ASSERT_SIZE(NiDX9DynamicTextureData, 0x74);