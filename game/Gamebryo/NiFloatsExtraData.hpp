#pragma once

#include "NiExtraData.hpp"

NiSmartPointer(NiFloatsExtraData);

class NiFloatsExtraData : public NiExtraData {
public:
	NiFloatsExtraData();
	virtual ~NiFloatsExtraData();

	UInt32 m_uiSize;
	float* m_pfValue;

	CREATE_OBJECT(NiFloatsExtraData, 0xA89190)
};

ASSERT_SIZE(NiFloatsExtraData, 0x14)