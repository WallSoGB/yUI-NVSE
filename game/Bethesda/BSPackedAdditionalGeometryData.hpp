#pragma once

#include "NiAdditionalGeometryData.hpp"

NiRTTIAddress(BSPackedAdditionalGeometryData, 0x11F4AAC);

class BSPackedAdditionalGeometryData : public NiAdditionalGeometryData {
public:
	UInt32	m_uiShaderDeclarationIndex;
	DWORD	dword30; // Read from NIF
};
