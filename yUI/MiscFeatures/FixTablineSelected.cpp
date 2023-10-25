#include <main.h>
#include <UserInterface.hpp>
#include <SimpleINILibrary.h>

namespace Fix::TablineSelected
{
	inline int enable = 1;

	bool needToFix = false;
	MyTile* tabline = nullptr;

	void MainLoop()
	{
		if (CdeclCall<bool>(0x702360) && Menu::IsVisible(Menu::EnumType::kType_Inventory)) {
			if (needToFix) {
				needToFix = false;
				if (!tabline)
				{
					tabline = &MyInventoryMenu::Get()["GLOW_BRANCH"]["IM_Tabline"];
					return;
				}
				for (const auto iter : *tabline) iter->Set(Tile::kValue_mouseover, 0, false);
			}
		}
		else needToFix = true;
	}

	void HandleINIs()
	{
		const auto iniPath = GetCurPath() / yUI_INI;
		CSimpleIniA ini;
		ini.SetUnicode();

		if (ini.LoadFile(iniPath.c_str()) == SI_FILE) return;

		enable = ini.GetOrCreate("General", "bFixTablineSelected", 1, "; fix the issue where Inventory Menu tabline shows up with buttons already selected");

		ini.SaveFile(iniPath.c_str(), false);
	}

	extern void Init()
	{
		if (g_nvseInterface->isEditor) return;
		HandleINIs();
		if (enable) mainLoop.emplace_back(MainLoop);
	}
}