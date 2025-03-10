#include "TESDataHandler.hpp"

bool TESDataHandler::bHasExtendedPlugins = false;

TESDataHandler* TESDataHandler::GetSingleton() {
	return *(TESDataHandler**)0x11C3F2C;
}

// GAME - 0x45DFC0
BSSimpleList<TESFile*>* TESDataHandler::GetFileList() {
	return &kFiles;
}

uint32_t TESDataHandler::GetCompiledFileCount() const {
	return kCompiledFiles.GetFileCount();
}

TESFile* TESDataHandler::GetCompiledFile(uint32_t auiIndex) const {
	return kCompiledFiles.GetFile(auiIndex);
}

TESFile* TESDataHandler::GetListFile(uint32_t auiIndex) {
	BSSimpleList<TESFile*>* pIter = GetFileList();

	uint32_t i = 0;
	if (auiIndex) {
		while (true) {
			pIter = pIter->GetNext();
			if (!pIter)
				break;

			if (pIter->GetItem() && ++i < auiIndex)
				continue;

			return pIter->GetItem();
		}
	}
	else {
		if (pIter)
			return pIter->GetItem();
	}

	return nullptr;
}

// GAME - 0x462F40
TESFile* TESDataHandler::GetListFile(const char* apFileName) {
	if (!apFileName)
		return nullptr;

	BSSimpleList<TESFile*>* pIter = GetFileList();
	while (pIter && pIter->GetItem()) {
		TESFile* pFile = pIter->GetItem();
		if (pFile && !_stricmp(pFile->GetName(), apFileName))
			return pFile;

		pIter = pIter->GetNext();
	}

	return nullptr;
}

uint32_t TESDataHandler::GetSmallCompiledFileCount() const {
	return kCompiledFiles.GetSmallFileCount();
}

TESFile* TESDataHandler::GetSmallFile(uint32_t auiIndex) const {
	return kCompiledFiles.GetSmallFile(auiIndex);
}

uint32_t TESDataHandler::GetOverlayFileCount() const {
	return kCompiledFiles.GetOverlayFileCount();
}

TESFile* TESDataHandler::GetOverlayFile(uint32_t auiIndex) const {
	return kCompiledFiles.GetOverlayFile(auiIndex);
}

uint32_t CompiledFiles::GetFileCount() const {
	if (TESDataHandler::bHasExtendedPlugins)
		return kNormalFiles.GetSize();

	return uiCompiledFileCount;
}

TESFile* CompiledFiles::GetFile(uint32_t auiIndex) const {
	if (auiIndex >= GetFileCount())
		return nullptr;

	if (TESDataHandler::bHasExtendedPlugins)
		return kNormalFiles.GetAt(auiIndex);

	return pFileArray[auiIndex];
}

uint32_t CompiledFiles::GetSmallFileCount() const {
	if (TESDataHandler::bHasExtendedPlugins)
		return kSmallFiles.GetSize();
	return 0;
}

TESFile* CompiledFiles::GetSmallFile(uint32_t auiIndex) const {
	if (auiIndex >= GetSmallFileCount())
		return nullptr;

	if (TESDataHandler::bHasExtendedPlugins)
		return kSmallFiles.GetAt(auiIndex);
	return nullptr;
}

uint32_t CompiledFiles::GetOverlayFileCount() const {
	if (TESDataHandler::bHasExtendedPlugins)
		return kOverlayFiles.GetSize();
	return 0;
}

TESFile* CompiledFiles::GetOverlayFile(uint32_t auiIndex) const {
	if (auiIndex >= GetOverlayFileCount())
		return nullptr;

	if (TESDataHandler::bHasExtendedPlugins)
		return kOverlayFiles.GetAt(auiIndex);
	return nullptr;
}