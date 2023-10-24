#pragma once

#include "NiLODData.hpp"
#include "NiBound.hpp"

NiSmartPointer(NiScreenLODData);

class NiScreenLODData : public NiLODData {
public:
	NiScreenLODData();
	virtual ~NiScreenLODData();

	NiBound m_kBound;
	NiBound m_kWorldBound;
	UInt32	m_uiNumProportions;
	float*	m_pfProportions;

	CREATE_OBJECT(NiScreenLODData, 0xA95F20)
};

ASSERT_SIZE(NiScreenLODData, 0x30)