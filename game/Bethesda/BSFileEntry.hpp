#pragma once

#include "BSHash.hpp"

struct BSFileEntry : public BSHash {
	SInt32 iSize;
	SInt32 iOffset;
};

ASSERT_SIZE(BSFileEntry, 0x10);