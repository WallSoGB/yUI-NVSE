#pragma once

#include "NiRefObject.hpp"
#include "NiColor.hpp"

class NiAVObject;

NiSmartPointer(NiTexture);
NiSmartPointer(EffectShaderProperty);

class EffectShaderProperty : public NiRefObject {
public:
	EffectShaderProperty();
	~EffectShaderProperty();

	NiTexturePtr	spTexture08;
	NiColorA		kNewFillColor;
	NiColorA		kNewEdgeColor;
	NiColorA		kFillColor;
	NiColorA		kEdgeColor;
	float			fAnimU;
	float			fAnimY;
	float			fEdgeFalloff;
	float			fUnk58;
	D3DBLEND		eSourceBlend;
	D3DBLEND		eDestBlend;
	D3DBLENDOP		eBlendOperation;
	D3DCMPFUNC		eCompareFunc;
	NiTexturePtr	spTexEffect;
	DWORD			uiAlphaRef;

	static void AddRecurse(NiAVObject* apObject, const NiColor& akColor, EffectShaderProperty* apEffect = nullptr);
	static void RemoveRecurse(NiAVObject* apObject);
};

ASSERT_SIZE(EffectShaderProperty, 0x74)