#include <CrashLogger.hpp>
#include "TESDataHandler.hpp"
#include <filesystem>

#include <shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")

namespace CrashLogger::Install
{
	extern void __fastcall Process(EXCEPTION_POINTERS* info) {
		try {
			char sanitizedBuffer[MAX_PATH] = {};
			_MESSAGE("\nInstall: %s", SanitizeString(GetRootDirectory(), sanitizedBuffer, sizeof(sanitizedBuffer)));
		}
		catch (...) { 
			_MESSAGE("Failed to print install path."); 
		}
	}
}

namespace CrashLogger::Mods
{
	std::stringstream output;

	extern void Process(EXCEPTION_POINTERS* info)
	try {
		char textBuffer[512];
		if (TESDataHandler::ExtendedPlugins())
			sprintf_s(textBuffer, "Mods:\n  #  |  Index  | %*s%*s | %*s%*s\n", CENTERED_TEXT(80, "Mod"), CENTERED_TEXT(60, "Author"));
		else	
			sprintf_s(textBuffer, "Mods:\n  # | %*s%*s | %*s%*s\n", CENTERED_TEXT(80, "Mod"), CENTERED_TEXT(60, "Author"));
		output << textBuffer;
		UInt32 i = 0;
		for (TESFile* mod : *g_TESDataHandler->GetFileList()) {
			if (!mod)
				continue;

			const auto& author = mod->strAuthor;
			const char* authorName = author.pcString;
			if (!author.usLen || !strcmp(mod->strAuthor.pcString, "DEFAULT"))
				authorName = "";

			if (TESDataHandler::ExtendedPlugins()) {
				if (mod->IsOverlay()) {
					sprintf_s(textBuffer, " %03i |   XXX   | %-80s | %-60s\n", i, mod->GetName(), authorName);
				}
				else if (mod->IsSmallFile()) {
					sprintf_s(textBuffer, " %03i |  FE%03X  | %-80s | %-60s\n", i, mod->GetSmallCompileIndex(), mod->GetName(), authorName);
				}
				else {
					sprintf_s(textBuffer, " %03i |    %02X   | %-80s | %-60s\n", i, mod->GetCompileIndex(), mod->GetName(), authorName);
				}
			}
			else
				sprintf_s(textBuffer, " %02X | %-80s | %-60s\n", i, mod->GetName(), authorName);
			output << textBuffer;
			i++;
		}
		output << '\n';

		char folder_path[MAX_PATH];
		sprintf_s(folder_path, "%s\\data\\nvse\\plugins\\scripts", GetFalloutDirectory().generic_string().c_str());

		if (std::filesystem::exists(folder_path) && std::filesystem::is_directory(folder_path)) {
			sprintf_s(textBuffer, "Script Runners:\n  # | %*s%*s\n", CENTERED_TEXT(80, "Filename"));
			output << textBuffer;

				UInt32 i = 0;
				// Iterate through each entry in the directory
				WIN32_FIND_DATA findFileData;
				HANDLE hFind = INVALID_HANDLE_VALUE;
				char searchPath[MAX_PATH];
				sprintf_s(searchPath, "%s\\*.txt", folder_path);
				hFind = FindFirstFile(searchPath, &findFileData);
				if (hFind != INVALID_HANDLE_VALUE) {
					do {
						_MESSAGE(" %02X | %-80s", i, findFileData.cFileName);
						i++;
					} while (FindNextFile(hFind, &findFileData) != 0);
					FindClose(hFind);
				}
			}
		}
		catch (...) {
			_MESSAGE("\nFailed to print out script runners.");
		}
	}
}