#include <definitions.h>
#include <SimpleINILibrary.h>

#define INIT_MODULE(mod) namespace mod { extern void Init(CSimpleIni& ini); }

#if 0
INIT_MODULE(ConfigurationMenu)

INIT_MODULE(SortingIcons)

INIT_MODULE(UserInterface::EventLayer)
INIT_MODULE(UserInterface::DynamicCrosshair)
INIT_MODULE(UserInterface::HitMarker)
INIT_MODULE(UserInterface::HitIndicator)
INIT_MODULE(UserInterface::VisualObjectives)
INIT_MODULE(UserInterface::LootMenu)
INIT_MODULE(UserInterface::WeaponHweel)

INIT_MODULE(Fix::DroppedItems)
INIT_MODULE(Fix::TablineSelected)
INIT_MODULE(Fix::ReorderMCM)
INIT_MODULE(Fix::TouchpadScrolling)

INIT_MODULE(Patch::RestoreFO3Spread)
INIT_MODULE(Patch::ArmedUnarmed)
INIT_MODULE(Patch::ExplosionForce)
INIT_MODULE(Patch::MatchedCursor)
INIT_MODULE(Patch::MultiplicativeShots)
INIT_MODULE(Patch::TimeMult)
INIT_MODULE(Patch::CharGenMenuSRemoval)
INIT_MODULE(Patch::B42InjectHideCrosshair)
#endif
void Inits()
{
	const auto iniPath = GetCurPath() / yUI_INI;
	CSimpleIni ini;
	ini.SetUnicode();
	if (ini.LoadFile(iniPath.c_str()) == SI_FILE) Log() << "Failed to open INI";
#if 0
	ConfigurationMenu::Init(ini);
	SortingIcons::Init(ini);

	UserInterface::EventLayer::Init(ini);
	UserInterface::DynamicCrosshair::Init(ini);
	UserInterface::HitMarker::Init(ini);
	UserInterface::HitIndicator::Init(ini);
	UserInterface::VisualObjectives::Init(ini);
	UserInterface::LootMenu::Init(ini);
//	UserInterface::WeaponHweel::Init();

	Fix::DroppedItems::Init(ini);
	Fix::TablineSelected::Init(ini);
//	Fix::ReorderMCM::Init();
	Fix::TouchpadScrolling::Init(ini);

//	Patch::RestoreFO3Spread::Init();
//	Patch::ArmedUnarmed::Init();
	Patch::ExplosionForce::Init(ini);
	Patch::MatchedCursor::Init(ini);
//	Patch::MultiplicativeShots::Init();
	Patch::TimeMult::Init(ini);
	Patch::CharGenMenuSRemoval::Init(ini);
	Patch::B42InjectHideCrosshair::Init(ini);

	ini.SaveFile(iniPath.c_str(), false);
#endif
}