#pragma once

#include "NiPSysData.hpp"

NiSmartPointer(BSStripPSysData);

class BSStripPSysData : public NiPSysData {
public:
	BSStripPSysData();
	~BSStripPSysData();

	DWORD dword7C;
	UInt16 usMaxPointCount;
	float fStartCapSize;
	float fEndCapSize;
	bool bDoZPrePass;

	CREATE_OBJECT(BSStripPSysData, 0xC25CA0)
};

ASSERT_SIZE(BSStripPSysData, 0x90);