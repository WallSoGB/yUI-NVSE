#include <main.h>
#include <Safewrite.hpp>
#include <UserInterface.hpp>

#include <SimpleINILibrary.h>


namespace Patch::MatchedCursor
{
	bool enable = false;

	void __fastcall CursorTileSetStringValue(Tile*	pkTile, void* dummyEDX, Tile::EnumValue tilevalue, char* src, char propagate)
	{
		pkTile->Set(Tile::kValue_zoom, -1, propagate);
		pkTile->Set(Tile::kValue_systemcolor, 1, propagate);
	}

	void __fastcall CursorTileSetIntValue(Tile*	pkTile, void* dummyEDX, Tile::EnumValue tilevalue, int value)
	{
		pkTile->Set(Tile::kValue_visible, value, true);
		ThisCall(0xA0B350, InterfaceManager::GetSingleton()->cursor, 1, 0);
	}

	void Patch(const bool enable)
	{
		if (enable)
		{
			WriteRelCall(0x70B33A, CursorTileSetStringValue);
			WriteRelCall(0x70C727, CursorTileSetIntValue);
		}
		else
		{
			UndoSafeWrite(0x70B33A);
			UndoSafeWrite(0x70C727);
		}
	}

	extern void Init(CSimpleIni& ini)
	{
		if (g_nvseInterface->isEditor) return;
		enable = ini.GetOrCreate("General", "bMatchingCursor", 0, "; match cursor color to HUD color");
		Patch(enable);
	}
}
