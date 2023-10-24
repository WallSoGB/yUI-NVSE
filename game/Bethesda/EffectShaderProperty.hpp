#pragma once

#include "NiRefObject.hpp"
#include "NiColor.hpp"

class NiSourceTexture;

NiSmartPointer(EffectShaderProperty);

class EffectShaderProperty : public NiRefObject {
public:
	EffectShaderProperty();
	~EffectShaderProperty();

	NiSourceTexture* pTexture08;
	NiColorA newFillColor;
	NiColorA newEdgeColor;
	NiColorA fillColor;
	NiColorA edgeColor;
	float fAnimU;
	float fAnimY;
	float fEdgeFalloff;
	float unk58;
	D3DBLEND eSourceBlend;
	D3DBLEND eDestBlend;
	D3DBLENDOP eBlendOperation;
	D3DCMPFUNC eCompareFunc;
	NiSourceTexture* pTexEffect;
	DWORD uiAlphaRef;
};

ASSERT_SIZE(EffectShaderProperty, 0x74)