#pragma once
#include "BSFile.hpp"

class Archive;

// 0x160
class ArchiveFile : public BSFile
{
public:
	Archive*	pArchive;
	UInt32		uiOffset;
};
static_assert(sizeof(ArchiveFile) == 0x160);