#pragma once

#include "BSHash.hpp"
#include "BSFileEntry.hpp"

struct BSDirectoryEntry : public BSHash {
	UInt32 uiFiles;
	BSFileEntry* pFiles;
};

ASSERT_SIZE(BSDirectoryEntry, 0x10);