#include <main.h>
#include <UserInterface.hpp>
#include <SimpleINILibrary.h>

namespace Patch::B42InjectHideCrosshair
{
	inline bool enable = true;

	void HandleINIs()
	{
		const auto iniPath = GetCurPath() / yUI_INI;
		CSimpleIniA ini;
		ini.SetUnicode();

		if (ini.LoadFile(iniPath.c_str()) == SI_FILE) return;

		enable = ini.GetOrCreate("General", "bPatchB42InjectHideCrosshair", 0, "; hide crosshair based on B42 attach and detach events.");

		ini.SaveFile(iniPath.c_str(), false);
	}

	void XilOn() { MyHUDMainMenu::Get().tileReticleCenter->Set(Tile::kValue_visible, false); }
	void XilOff() { MyHUDMainMenu::Get().tileReticleCenter->Set(Tile::kValue_visible, true); }

	void MainLoopDoOnce()
	{
		RegisterEvent("B42IGO", 0, nullptr, 4);
		SetEventHandler("B42IGO", XilOn);

		RegisterEvent("B42IDx", 0, nullptr, 4);
		SetEventHandler("B42IDx", XilOff);
	}

	extern void Init()
	{
		if (g_nvseInterface->isEditor) return;
		HandleINIs();
		if (!enable) return;
		mainLoopDoOnce.emplace_back(MainLoopDoOnce);
	}
}
