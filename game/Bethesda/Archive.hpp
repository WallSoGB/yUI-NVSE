#pragma once
#include "BSArchive.hpp"
#include "ArchiveFile.hpp"
#include "NiRefObject.hpp"
#include "BSFileEntry.hpp"
#include "BSSimpleList.hpp"

enum ARCHIVE_TYPE {
	ARCHIVE_TYPE_ALL_ = 0xFFFFFFFF,
	ARCHIVE_TYPE_ALL = 0xFFFF,
	ARCHIVE_TYPE_MESHES = 0x1,
	ARCHIVE_TYPE_TEXTURES = 0x2,
	ARCHIVE_TYPE_MENUS = 0x4,
	ARCHIVE_TYPE_SOUNDS = 0x8,
	ARCHIVE_TYPE_VOICES = 0x10,
	ARCHIVE_TYPE_SHADERS = 0x20,
	ARCHIVE_TYPE_TREES = 0x40,
	ARCHIVE_TYPE_FONTS = 0x80,
	ARCHIVE_TYPE_MISC = 0x100,
	ARCHIVE_TYPE_COUNT = 0x9,
};

enum ARCHIVE_TYPE_INDEX {
	ARCHIVE_TYPE_INDEX_MESHES = 0x0,
	ARCHIVE_TYPE_INDEX_TEXTURES = 0x1,
	ARCHIVE_TYPE_INDEX_MENUS = 0x2,
	ARCHIVE_TYPE_INDEX_SOUNDS = 0x3,
	ARCHIVE_TYPE_INDEX_VOICES = 0x4,
	ARCHIVE_TYPE_INDEX_SHADERS = 0x5,
	ARCHIVE_TYPE_INDEX_TREES = 0x6,
	ARCHIVE_TYPE_INDEX_FONTS = 0x7,
	ARCHIVE_TYPE_INDEX_MISC = 0x8,
	ARCHIVE_TYPE_INDEX_COUNT = 0x9,
};

// 0x1D0
class Archive : public BSFile
{
public:
	NiRefObject			kRefObject;
	BSArchive			kArchive;
	FILETIME			kArchiveFileTime;
	UInt32				uiFileNameArrayOffset;
	UInt32				uiLastDirectoryIndex;
	UInt32				uiLastFileIndex;
	CRITICAL_SECTION	kArchiveCriticalSection;
	UInt8				cArchiveFlags;
	UInt32				pDirectoryStringArray;
	UInt32*				pDirectoryStringOffsets;
	const char*			pFileNameStringArray;
	UInt32**			pFileNameStringOffsets;
	UInt32				uiID;
	UInt32				unk6C;

	bool FindDirectory(BSHash* arDirectoryHash, UInt32* aruiDirectoryIndex, const char* apFileName);
	bool FindFileInDirectory(UInt32 auiDirectoryIndex, BSHash* arFileNameHash, UInt32* aruiFileIndex, const char* apFileName, bool abSkipSecondaryArchiveCheck);
	BSFileEntry* GetFileEntryForFile(BSHash* arDirectoryHash, BSHash* arFileNameHash, const char* apFileName);
};
static_assert(sizeof(Archive) == 0x1D0);

namespace ArchiveManager {
	void __cdecl AddToFileList(BSSimpleList<const char*>* apFileNameList, const char* apSearchName, const char* apBaseFilename, ARCHIVE_TYPE aeArchiveType);
	BSHash** __cdecl AddArchiveToFileList(Archive* apArchive, UInt32 aiNumFiles, BSHash** apHashArray, BSHash* arDirectoryHash, BSHash* arSearchHash, BSSimpleList<const char*>* apFileNameList, const char* apBaseFilename);
	
	void __cdecl LoadInvalidationFile(const char* apFileName);
	bool __cdecl InvalidateFile(const char* apFileName);
	void __cdecl InvalidateFileInArchives(BSHash* arDirectoryHash, BSHash* arFileHash, UInt16 aiArchiveTypes);

	Archive* __cdecl GetMasterArchive(ARCHIVE_TYPE_INDEX aeTypeIndex);
	Archive* __cdecl GetArchiveForFile(const char* apFileName, ARCHIVE_TYPE aiArchiveType);

	bool OpenMasterArchives();
	Archive* __cdecl OpenArchive(const char* apArchiveName, UInt16 aiForceArchiveType, bool abInvalidateOtherArchives);

	bool __cdecl FindFile(const char* apFileName, ARCHIVE_TYPE aiArchiveType);

	ArchiveFile* __cdecl GetFile(const char* apFileName, UInt32 aiBufferSize, ARCHIVE_TYPE aeArchiveType);
	ArchiveFile* __cdecl GetArchiveFile(const char* apFileName, UInt32 aiBufferSize, ARCHIVE_TYPE aeArchiveType);
	BSFileEntry* __cdecl GetFileEntryForFile(ARCHIVE_TYPE_INDEX aeArchiveTypeIndex, BSHash* arDirectoryHash, BSHash* arFileNameHash, const char* apFileName);

	ARCHIVE_TYPE __cdecl GetArchiveTypeFromFileName(const char* apFileName);
	ARCHIVE_TYPE __cdecl GetArchiveTypeFromFileExtension(const char* apExtension);

	bool __cdecl GetFileNameForSmallestFileInDirectory(const char* apDirectory, char* apFileName, ARCHIVE_TYPE aeArchiveType);
	bool __cdecl GetRandomFileNameForDirectory(const char* apDirectory, char* apFileName, ARCHIVE_TYPE aeArchiveType);

	const char* __cdecl TrimFileName(const char* apFileName);
}