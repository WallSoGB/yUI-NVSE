#pragma once
#include "Menu.hpp"

// 10C
class ContainerMenu : public Menu		// 1008
{
public:
	ContainerMenu();
	~ContainerMenu();

	enum Mode
	{
		kNormal = 0x1,
		kPickpocket,
		kTeammate,
		kRockItLauncher
	};

	enum Buttons
	{
		CM_Items_LeftFilterArrow = 0x0,
		CM_ItemsTitle = 0x1,
		CM_Items_RightFilterArrow = 0x2,
		CM_Items_CapsLabel = 0x3,
		CM_Items_InventoryList = 0x4,
		CM_Container_LeftFilterArrow = 0x5,
		CM_ContainerTitle = 0x6,
		CM_Container_RightFilterArrow = 0x7,
		CM_Container_InventoryList = 0x8,
		CM_ArrowIcon = 0x9,
		CM_TakeAllButton = 0xA,
		CM_ExitButton = 0xB,
		CM_ItemIcon = 0xC,
		CM_ItemData = 0xD,
		CM_list_template_container = 0x14,
	};

	enum FilterCategory
	{
		kAllItems,
		kWeapons,
		kArmor,
		kAid,
		kMisc,
		kAmmo,
		kMAX = kAmmo,
	};

	TileImage*			tile028;		// 028
	TileText*			itemsTitle;		// 02C
	TileImage*			tile030;		// 030
	TileText*			tileInventoryWeight;		// 034
	TileImage*			tile038;		// 038
	TileImage*			tile03C;		// 03C
	TileText*			containerTitle;	// 040
	TileImage*			tile044;		// 044
	TileImage*			tile048;		// 048
	TileImage*			tile04C;		// 04C
	TileImage*			takeAllTile;	// 050
	TileImage*			tile054;		// 054
	TileImage*			tile058;		// 058
	TileRect*			tile05C;		// 05C
	TileRect*			tile060;		// 060
	TileRect*			tile064;		// 064
	TileRect*			tile068;		// 068
	TileRect*			tile06C;		// 06C
	TileRect*			tile070;		// 070
	TESObjectREFR*		containerRef;	// 074
	TList<void>			list078;		// 078
	UInt32				mode;			// 080
	UInt32				valueTransfered;// 084
	UInt8				hasPickedPocket;// 088
	UInt8				hasFailedPickpocket;	// 089
	UInt8				pad08A;			// 08A
	UInt8				pad08B;			// 08B
	SInt32				leftFilter;		// 08C
	SInt32				rightFilter;	// 090
	UInt32				menuSoundID;	// 094
	MenuItemEntryList	leftItems;		// 098
	MenuItemEntryList	rightItems;		// 0C8
	MenuItemEntryList*	currentItems;	// 0F8
	UInt32				unk0FC;			// 0FC
	Sound				menuSound;		// 100

	static ContainerMenu*		GetSingleton() { return *reinterpret_cast<ContainerMenu**>(0x11D93F8); }
	static InventoryChanges*	GetSelection() { return *reinterpret_cast<InventoryChanges**>(0x11D93FC); }
	static void					SetSelection(InventoryChanges* entry) { *reinterpret_cast<InventoryChanges**>(0x11D93FC) = entry; }
	__forceinline void 			Refresh(TESForm* form = nullptr) { ThisCall(0x75C280, form); }

};
static_assert(sizeof(ContainerMenu) == 0x10C);