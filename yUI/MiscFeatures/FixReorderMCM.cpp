#include <main.h>

#if 0
#include <SimpleINILibrary.h>

inline int g_FixReorderMCM = 1;

std::unordered_map<std::string, UInt32> g_MCMChildOrder{
	{"MCM_Version", 0}, {"MCM_RGB", 25}, {"MCM_Images", 2}, {"MCM_Return", 3}, {"MCM_Input", 4}, {"MCM_Font", 5},
	{"MCM_Highlight", 6}, {"MCM_PressControl", 7}, {"MCM_Defaults", 8}, {"MCM_Back", 9}, {"MCM_Info", 10},
	{"MCM_ModTitle", 11}, {"MCM_Bracket", 12}, {"MCM_BG", 13}, {"MCM_ModList", 14}, {"MCM_Trigger", 15},
	{"MCM_List", 16}, {"MCM_Scale", 17}, {"MCM_Options", 18}
};

int SortMCMChildren(Tile*	pkTile1, Tile*	pkTile2)
{
	const auto pos1 = g_MCMChildOrder[std::string(tile1->name.CStr())];
	const auto pos2 = g_MCMChildOrder[std::string(tile2->name.CStr())];
	if (pos1 > pos2) return -1;
	if (pos1 < pos2) return 1;
	return 0;
}

std::unordered_map<std::string, UInt32> g_ValueChildOrder{
	{"RGB", 25}, {"toggle_check", 0}, {"toggle", 1}, {"suffix", 2}, {"prefix", 3}, {"text", 4}
};

int SortValueChildren(Tile*	pkTile1, Tile*	pkTile2)
{
	const auto pos1 = g_ValueChildOrder[std::string(tile1->name.CStr())];
	const auto pos2 = g_ValueChildOrder[std::string(tile2->name.CStr())];
	if (pos1 > pos2) return -1;
	if (pos1 < pos2) return 1;
	return 0;
}

bool fixReorderMCM = false;

void FixReorderMCM()
{
	if (StartMenu::GetSingleton())
	{
		if (fixReorderMCM)
		{
			fixReorderMCM = false;
			const auto tileMCM = StartMenu::GetSingleton()->tile->GetChild("MCM");
			if (!tileMCM) return;
			tileMCM->children.Sort(SortMCMChildren);

			const auto tileMCMOptions = tileMCM->GetChild("MCM_Options");

			for (const auto iter : tileMCMOptions->children)
			{
				if (iter->GetValue("_optionID"))
				{
					const auto tileValue = iter->GetChild("value");
					tileValue->children.Sort(SortValueChildren);
				}
			}
		}
	}
	else fixReorderMCM = true;
}

namespace Fix::ReorderMCM
{
	void Init(CSimpleIni& ini)
	{
		if (g_FixReorderMCM) FixReorderMCM();
//		g_FixReorderMCM = ini.GetOrCreate("General", "bFixReorderMCM", 1, "; fix the issues where MCM is incompatible with newest xNVSE features like Get/SetUIFloatAlt commands and inline expressions. This is fixed by reordering MCM's .xml in-code to work with these commands and hooking deprecated commands to work through Get/SetUIFloatAlt.");
		mainLoop.emplace_back(FixReorderMCM);
	}
}

#endif