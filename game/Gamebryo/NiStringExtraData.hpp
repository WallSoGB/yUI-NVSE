#pragma once

#include "NiExtraData.hpp"

NiSmartPointer(NiStringExtraData);

class NiStringExtraData : public NiExtraData {
public:
	NiStringExtraData();
	~NiStringExtraData();

	NiFixedString m_kString;

	CREATE_OBJECT(NiStringExtraData, 0xA74230)
};

ASSERT_SIZE(NiStringExtraData, 0x10);