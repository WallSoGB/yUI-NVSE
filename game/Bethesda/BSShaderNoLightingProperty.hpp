#pragma once

#include "BSShaderProperty.hpp"

NiSmartPointer(BSShaderNoLightingProperty);

class BSShaderNoLightingProperty : public BSShaderProperty {
public:
	BSShaderNoLightingProperty();
	virtual ~BSShaderNoLightingProperty();

	// Returns 1
	virtual UInt32 Unk_31();
	// 3 = clamp, anything else = wrap
	virtual void PickClampMode(UInt32 aeMode); 
	virtual NiTexturingProperty::ClampMode GetClampMode();
	virtual void SetClampMode(NiTexturingProperty::ClampMode aeMode);

	struct FalloffData {
		float fFalloffStartAngle;
		float fFalloffStopAngle;
		float fFalloffStartOpacity;
		float fFalloffStopOpacity;
	};

	NiTexturePtr					spTexture;
	char*							pcTexturePath;
	UInt16							word68;
	UInt16							word6A;
	NiTexturingProperty::ClampMode	eClampMode;
	FalloffData						kFalloffData;

	CREATE_OBJECT(BSShaderNoLightingProperty, 0xB6FE80);

	void SetTexture(NiTexture* apTexture);
};

ASSERT_SIZE(BSShaderNoLightingProperty, 0x80);