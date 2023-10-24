#pragma once

#include "NiExtraData.hpp"

NiSmartPointer(NiStringsExtraData);

class NiStringsExtraData : public NiExtraData {
public:
	NiStringsExtraData();
	~NiStringsExtraData();

	UInt32 m_uiSize;
	char** m_ppcValue;

	CREATE_OBJECT(NiStringsExtraData, 0xA94930)
};

ASSERT_SIZE(NiStringsExtraData, 0x14);