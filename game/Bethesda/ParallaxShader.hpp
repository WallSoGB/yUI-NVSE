#pragma once

#include "ShadowLightShader.hpp"

class NiD3DVertexShader;

class ParallaxShader : public ShadowLightShader {
public:
	NiD3DVertexShaderPtr	spVertexShaders[20];
	NiD3DPixelShaderPtr		spPixelShaders[33];

	static void __fastcall SetupTexturesEx(ParallaxShader* apThis, void*, NiPropertyState* apProperties);
};

ASSERT_SIZE(ParallaxShader, 0x160)