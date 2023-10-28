#pragma once

#include "BSShaderLightingProperty.hpp"
#include "NiSmartPointer.hpp"
#include "TESGrassAreaParam.hpp"
#include "NiPoint4.hpp"

class NiTexture;
class IOTask;
class NiStencilProperty;
class NiGeometryData;
class BSMultiBoundNode;
class TallGrassShaderProperty;

NiSmartPointer(TallGrassObject);

class TallGrassObject : public NiRefObject {
public:
	NiGeometryDataPtr				spGeoData;
	float*							pfUnkDataC;
	DWORD							dword10;
	NiSourceTexturePtr				spTexture;
	NiPropertyPtr					spAlphaPropertyHDR;
	NiPropertyPtr					spAlphaProperty;
	NiPointer<NiStencilProperty>	spStencilProperty;
	NiPointer<IOTask>				spLoadTask;
	DWORD							vertCount28;
	DWORD							vertCount2C;
	bool							bIsStrips;
	bool							bLightFade;
	bool							bCreated;
	bool							byte34;
	UInt16							dword38;
};

struct SomeGrassStructure {
	NiPointer<NiGeometry>				spGrassGeometry;
	NiPointer<BSMultiBoundNode>			spMBNode;
	NiPointer<TallGrassObject>			spGrassObject;
	NiPointer<TallGrassShaderProperty>	spGrassShaderProperty;
	UInt16								usInstanceCount;	// Amount of slots in pInstanceData
	UInt16								usGrassCount;		// Amount of filled slots in pInstanceData
	NiPoint4*							pInstanceData;		// Positions of all grass instances
	void*								dword18;
	GrassParam							Params;
	SInt32								iCellX;
	SInt32								iCellY;
	bool								bLowDetail;
};
ASSERT_SIZE(SomeGrassStructure, 0x48u);

NiSmartPointer(TallGrassShaderProperty);

class TallGrassShaderProperty : public BSShaderLightingProperty {
public:
	SomeGrassStructure*		pGrassStructure;
	NiObjectPtr				spObject80;
	NiPointer<NiTexture>	spTexture;
	BSStringT				sTexturePath;
	int						unk90;
	int						unk98;

	CREATE_OBJECT(TallGrassShaderProperty, 0xB60F50);

	static void __fastcall GetViewerStringsEx(TallGrassShaderProperty* apThis, void*, NiViewerStringsArray* apStrings);

	static BSShaderProperty::RenderPassList* __fastcall GetRenderPassesEx(TallGrassShaderProperty* apThis, void*, NiGeometry* apGeometry, UInt32 auiEnabledPasses, UInt16* pusPassCount, int a5, BSShaderAccumulator* apAccumulator, int a7);
};

ASSERT_SIZE(TallGrassShaderProperty, 0x98)