#include <main.h>
#include <UserInterface.hpp>
#include <SimpleINILibrary.h>

namespace Patch::B42InjectHideCrosshair
{
	inline bool enable = true;

	void XilOn() { MyHUDMainMenu::Get().pkTileReticleCenter->Set(Tile::kValue_visible, false); }
	void XilOff() { MyHUDMainMenu::Get().pkTileReticleCenter->Set(Tile::kValue_visible, true); }

	void MainLoopDoOnce()
	{
		RegisterEvent("B42IGO", 0, nullptr, 4);
		SetEventHandler("B42IGO", XilOn);

		RegisterEvent("B42IDx", 0, nullptr, 4);
		SetEventHandler("B42IDx", XilOff);
	}

	extern void Init(CSimpleIni& ini)
	{
		if (g_nvseInterface->isEditor) return;
		enable = ini.GetOrCreate("General", "bPatchB42InjectHideCrosshair", 0, "; hide crosshair based on B42 attach and detach events.");
		if (!enable) return;
		mainLoopDoOnce.emplace_back(MainLoopDoOnce);
	}
}