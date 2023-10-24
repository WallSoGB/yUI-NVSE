#pragma once

#include "NiExtraData.hpp"
#include "NiPoint3.hpp"

NiSmartPointer(BSBound);

class BSBound : public NiExtraData {
public:
	BSBound();
	~BSBound();

	NiPoint3 center;
	NiPoint3 extents;

	CREATE_OBJECT(BSBound, 0xC55010)
};

ASSERT_SIZE(BSBound, 0x24)