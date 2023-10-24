#pragma once
#include "QueuedFile.hpp"
#include "Archive.hpp"

// 0x30
class QueuedFileEntry : public QueuedFile {
public:
	QueuedFileEntry();
	~QueuedFileEntry();

	virtual bool Unk_0B() = 0;

	char* cFileName;
	BSFileEntry* pData;

	static void __fastcall LookupFileInBSA(QueuedFileEntry* apThis, void*, ARCHIVE_TYPE_INDEX aeArchiveTypeIndex);
	static bool __fastcall CreateDescription(QueuedFileEntry* apThis, void*, const char* apDest, size_t auiSize, const char* apTaskName);

	ArchiveFile* OpenBSFile(ARCHIVE_TYPE_INDEX aeArchiveTypeIndex, SInt32 aiArchiveType);
};
static_assert(sizeof(QueuedFileEntry) == 0x30);