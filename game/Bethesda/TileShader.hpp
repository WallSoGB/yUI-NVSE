#pragma once

#include "BSShader.hpp"

// 0x90
class TileShader : public BSShader
{
public:
	virtual void Func_79();
	virtual void InitVertexShaders();
	virtual void InitPixelShaders();
	virtual bool InitPasses();
	virtual bool Func_83(); // Ret1

	NiD3DPassPtr				spPasses[1];
	NiD3DVertexShaderPtr		spVertexShaders[3];
	NiD3DPixelShaderPtr			spPixelShaders[3];
	NiD3DShaderDeclarationPtr	spShaderDeclarations[2]; // 1 for vertex colors
};
static_assert(sizeof(TileShader) == 0x90);