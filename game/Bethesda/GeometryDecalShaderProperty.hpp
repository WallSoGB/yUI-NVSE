#pragma once

#include "BSShaderLightingProperty.hpp"

class NiSourceTexture;

class GeometryDecalShaderProperty : public BSShaderLightingProperty {
public:
	NiSourceTexture* pTexture;
	DWORD dword80[21];
};

ASSERT_SIZE(GeometryDecalShaderProperty, 0xD4)