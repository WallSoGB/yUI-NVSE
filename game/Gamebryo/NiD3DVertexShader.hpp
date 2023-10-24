#pragma once

#include "NiD3DShaderProgram.hpp"

NiSmartPointer(NiD3DVertexShader);

class NiD3DVertexShader : public NiD3DShaderProgram {
public:
	NiD3DVertexShader();
	virtual ~NiD3DVertexShader();

	virtual UInt32						GetUsage();
	virtual void						SetUsage(UInt32 uiUsage);
	virtual NiD3DVertexShaderHandle		GetShaderHandle();
	virtual void						SetShaderHandle(NiD3DVertexShaderHandle hShader);
	virtual NiD3DVertexShaderHandle		GetVertexDeclaration();
	virtual void						SetVertexDeclaration(NiD3DVertexShaderHandle hShader);
	virtual bool						GetSoftwareVertexProcessing();
	virtual void						SetSoftwareVertexProcessing(bool bSoftwareVP);
	virtual void						DestroyRendererData();
	virtual void						RecreateRendererData();

	bool						m_bSoftwareVP;
	UInt32						m_uiUsage;
	NiD3DVertexShaderHandle		m_hShader;
	NiD3DVertexDeclaration		m_hDecl;

	static NiD3DVertexShader* Create(NiDX9Renderer* apRenderer);
};

ASSERT_SIZE(NiD3DVertexShader, 0x3C);