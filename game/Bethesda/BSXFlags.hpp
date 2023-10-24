#pragma once

#include "NiExtraData.hpp"

NiSmartPointer(BSXFlags);

class BSXFlags : public NiExtraData {
public:
	BSXFlags();
	~BSXFlags();

	UInt32 uiFlags;

	CREATE_OBJECT(BSXFlags, 0xC43190)
};

ASSERT_SIZE(BSXFlags, 0x10)