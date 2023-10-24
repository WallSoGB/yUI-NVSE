#pragma once

#include "BSShaderProperty.hpp"
#include "NiPoint4.hpp"

NiSmartPointer(WaterShaderProperty);

class WaterShaderProperty : public BSShaderProperty {
public:
	WaterShaderProperty();
	~WaterShaderProperty();

	struct VarAmounts
	{
		float unk;
		float fWaterReflectivityAmt;
		float fWaterOpacity;
		float fWaterDistortionAmt;
	};

	bool						bIsWading;
	BYTE						bIsLOD;
	bool						bRenderAtWaterLevel;
	bool						bDepth;
	DWORD						dword64;
	DWORD						dword68;
	float						blendRadiusX;
	float						blendRadiusY;
	float						fogPower;
	float						fog78;
	BYTE						byte7C;
	BYTE						byte7D;
	bool						bIsUnderwater;
	bool						bIsUseDefaultWater;
	bool						bReflect;
	bool						bRefract;
	BYTE						UV;
	BYTE						byte83;
	DWORD						uiStencilMask;
	NiColorA					shallowColor;
	NiColorA					deepColor;
	NiColorA					reflectionColor;
	VarAmounts					Vars;
	float						floatC8;
	float						floatCC;
	float						blendRadiusZ;
	float						floatD4;
	NiPoint4					depthData;
	float						floatE8;
	float						floatEC;
	float						floatF0;
	float						floatF4;
	float						floatF8;
	float						floatFC;
	float						fresnelZ;
	float						fresnelW;
	float						float108;
	float						float10C;
	float						float110;
	float						float114;
	float						fWaterFresnelTerm;
	float						fWaterNoise;
	float						fFogAmount;
	float						texScale;
	NiTPointerList<NiLight*>	kLights;
	NiSourceTexturePtr			spNoiseTexture;
	BSRenderedTexturePtr		spDistortionTexture;
	BSRenderedTexturePtr		spReflectionTexture;
	BSRenderedTexturePtr		spRefractionTexture;
	BSRenderedTexturePtr		spDepthTexture;
	NiTexturePtr				spWadingTexture;
	BSRenderPass*				pStencilPass;

	CREATE_OBJECT(WaterShaderProperty, 0xB6AE60);

	BSRenderPass* CreateStencilPass(NiGeometry* apGeo);
	NiSourceTexture* GetNoiseTexture();
};

ASSERT_SIZE(WaterShaderProperty, 0x150);