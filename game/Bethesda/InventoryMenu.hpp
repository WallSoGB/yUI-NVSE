#pragma once
#include "Menu.hpp"
#include "InventoryChanges.hpp"

class InventoryMenu : public Menu		// 1002
{
public:
	InventoryMenu();
	~InventoryMenu() override;

	enum EnumFilter : UInt32
	{
		kWeapons,
		kApparel,
		kAid,
		kMisc,
		kAmmo
	};

	enum InventoryMenuHotkey
	{
		Inv_HotKeyWheel		= 0x5,
		Inv_Equip			= 0x6,
		Inv_Drop			= 0x7,
		Inv_Repair			= 0x8,
		Inv_HotkeyButton	= 0x9,
		Inv_Cancel			= 0xA,
		Inv_ModMenu			= 0x13,
	};

	enum Buttons
	{
		kButton_HotKeyWheel		= 0x5,
		kButton_Equip			= 0x6,
		kButton_Drop			= 0x7,
		kButton_Repair			= 0x8,
		kButton_HotkeyButton	= 0x9,
		kButton_Cancel			= 0xA,
		kButton_ModMenu			= 0x13,
	};


	struct ScrollPos
	{
		SInt32				listIndex;
		SInt32				currentValue;
	};

	union
	{
		Tile				 tiles[23];
		struct
		{
			TileRect*		tileCapsInfo;
			TileRect*		tilePlayerHPInfo;
			TileRect*		tilePlayerDRInfo;
			TileRect*		tilePlayerWGInfo;
			TileImage*		tileInventoryList;
			TileRect*		tileHotKeyWheel;
			TileImage*		tileEquipButton;
			TileImage*		tileDropButton;
			TileImage*		tileRepairButton;
			TileImage*		tileHotkeyButton;
			TileImage*		tileCancelButton;
			TileImage*		tileItemIcon;
			TileRect*		tileItemInfoRect;
			TileRect*		tileTabline;
			TileRect*		tileDAMInfo;
			TileRect*		tileDPSInfo;
			TileRect*		tileStrengthReqInfo;
			TileRect*		tileDamResistInfo;
			TileRect*		tileDamThresholdInfo;
			TileImage*		tileModButton;
			TileImage*		tileItemIconBadge;
			TileRect*		tilePlayerDTInfo;
			TileText*		tileStrReq;
		};
	};

	EFilter					eFilter;					// 084
	ScrollPos				tabScrollPositions[6];	// 088, the scroll index for Weapons, Apparel, Aid, Misc, Ammo and the Keyring
	MenuItemEntryList		itemsList;				// 0B8
	HotKeyWheel				hotkeyWheel;			// 0E8
	BSSimpleList<InventoryChanges*> changedItemsList;		// 11C

	static InventoryMenu*		GetSingleton() { return *reinterpret_cast<InventoryMenu**>(0x11D9EA4); }
	static UInt32				GetMenuID() { return 1002; }
	static InventoryChanges*	GetSelection() { return *reinterpret_cast<InventoryChanges**>(0x11D9EA8); }
	bool						IsKeyringOpen() const;
	static void					RestoreScrollPosition() { CdeclCall(0x7800C0); }
	static bool					ShouldHideItem(InventoryChanges* entry) { return CdeclCall<bool>(0x782620, entry); }
	static SInt32				CompareForSorting(const ListBoxItem<InventoryChanges>* a1, const ListBoxItem<InventoryChanges>* a2)
	{
		return CdeclCall<SInt32>(0x7824E0, a1, a2);
	}
	void						ResetInventorySelectionAndHideDataTile() { ThisCall(0x781B10, this); }
};
static_assert(sizeof(InventoryMenu) == 0x124);