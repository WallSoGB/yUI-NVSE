#pragma once

#include "BSShaderProperty.hpp"

NiSmartPointer(VolumetricFogShaderProperty);

// 0x70
class VolumetricFogShaderProperty :
	public BSShaderProperty
{
public:
	VolumetricFogShaderProperty();
	virtual ~VolumetricFogShaderProperty();

	NiColorA kFogProps;

	CREATE_OBJECT(VolumetricFogShaderProperty, 0xBC38C0);

	static BSShaderProperty::RenderPassList* __fastcall GetRenderPassesEx(VolumetricFogShaderProperty* apThis, void*, NiGeometry* apGeometry, UInt32 auiEnabledPasses, UInt16* pusPassCount, int a5, BSShaderAccumulator* apAccumulator, int a7);
};
static_assert(sizeof(VolumetricFogShaderProperty) == 0x70);