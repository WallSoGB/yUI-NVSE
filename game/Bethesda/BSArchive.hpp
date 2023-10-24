#pragma once

#include "BSDirectoryEntry.hpp"

struct BSArchiveHeader {
	UInt32 uiTag;
	UInt32 uiVersion;
	UInt32 uiHeaderSize;
	UInt32 uiFlag;
	UInt32 uiDirectories;
	UInt32 uiFiles;
	UInt32 uiDirectoryNamesLength;
	UInt32 uiFileNamesLength;
	UInt16 usArchiveType;
};

ASSERT_SIZE(BSArchiveHeader, 0x24);

struct BSArchive : public BSArchiveHeader {
	BSDirectoryEntry* pDirectories;
};

ASSERT_SIZE(BSArchive, 0x28);