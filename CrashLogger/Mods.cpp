#include <CrashLogger.hpp>
#include "TESDataHandler.hpp"
#include <filesystem>

namespace CrashLogger::Install
{
	std::stringstream output;

	extern void Process(EXCEPTION_POINTERS* info)
	try {
		output << "Install: " << SanitizeString(GetFalloutDirectory().generic_string()) << '\n';
	}
	catch (...) { output << "Failed to print install path." << '\n'; }

	extern std::stringstream& Get() { output.flush(); return output; }
}

namespace CrashLogger::Mods
{
	std::stringstream output;

	extern void Process(EXCEPTION_POINTERS* info)
	try {
		char textBuffer[512];
		if (TESDataHandler::bHasExtendedPlugins)
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

			if (TESDataHandler::bHasExtendedPlugins) {
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
			for (const auto& entry : std::filesystem::directory_iterator(folder_path)) {
				if (entry.path().extension().string()._Equal(".txt")) {
					sprintf_s(textBuffer, " %02X | %-80s\n", i, entry.path().filename().string().c_str());
					output << textBuffer;
					i++;
				}
			}
		}
	}
	catch (...) { output << "Failed to print out mod list." << '\n'; }

	extern std::stringstream& Get() { output.flush(); return output; }
}