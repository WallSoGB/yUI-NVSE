#pragma once

#include "ShadowLightShader.hpp"

class NiD3DPass;
class NiD3DVertexShader;
class NiD3DPixelShader;
class NiDX9ShaderDeclaration;

// Unused?
class HairShader : public ShadowLightShader {
public:
	NiD3DPass* passes[2];
	NiD3DVertexShader* vertexShaders1[7];
	NiD3DPixelShader* pixelShaders1[3];
	NiD3DVertexShader* vertexShaders2[7];
	NiD3DPixelShader* pixelShaders2[3];
	NiDX9ShaderDeclaration* shaderDeclarationE4;
	NiDX9ShaderDeclaration* shaderDeclarationE8;
};

ASSERT_SIZE(HairShader, 0xEC)