#pragma once

#include "BSShaderProperty.hpp"
#include "BSString.hpp"

NiSmartPointer(TileShaderProperty);

class TileShaderProperty : public BSShaderProperty {
public:
	TileShaderProperty();
	~TileShaderProperty();

	NiTexture* srcTexture;
	NiTexture* m_pAlphaTexture;
	NiColorA overlayColor;
	float  fTileAlpha;
	float  unk7C;
	float  unk80;
	float  flt84;
	float  flt88;
	UInt32 unk8C;
	UInt8  byte90;
	bool   m_bRotates;
	bool   m_bHasVtxColors;
	UInt8  byte93;
	BSStringT  texturePath;
	UInt32 unk9C;
	UInt32 unkA0;
	UInt32 unkA4;
	UInt32 unkA8;
	UInt8  unkAC;

	CREATE_OBJECT(TileShaderProperty, 0xBB7EF0)
};;

ASSERT_SIZE(TileShaderProperty, 0xB0);