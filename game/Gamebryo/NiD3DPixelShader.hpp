#pragma once

#include "NiD3DShaderProgram.hpp"

NiSmartPointer(NiD3DPixelShader);

class NiDX9Renderer;

class NiD3DPixelShader : public NiD3DShaderProgram {
public:
	virtual NiD3DPixelShaderHandle	GetShaderHandle();
	virtual void					SetShaderHandle(NiD3DPixelShaderHandle hShader);
	virtual void					DestroyRendererData(NiD3DPixelShaderHandle hShader);
	virtual void					RecreateRendererData();

	NiD3DPixelShaderHandle m_hShader;

	static NiD3DPixelShader* Create(NiDX9Renderer* apRenderer);
};

ASSERT_SIZE(NiD3DPixelShader, 0x30);