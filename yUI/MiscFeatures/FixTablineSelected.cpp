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
		if (CdeclCall<bool>(0x702360) && Menu::IsVisible(Menu::Type::kType_Inventory)) {
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

	extern void Init(CSimpleIni& ini)
	{
		if (g_nvseInterface->isEditor) return;
		enable = ini.GetOrCreate("General", "bFixTablineSelected", 1, "; fix the issue where Inventory Menu tabline shows up with buttons already selected");
		if (enable) mainLoop.emplace_back(MainLoop);
	}
}