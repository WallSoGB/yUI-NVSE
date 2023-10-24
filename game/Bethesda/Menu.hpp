#pragma once

#include "BSSimpleList.hpp"
#include "NiTList.hpp"
#include "BSString.hpp"
#include "NiColor.hpp"

#include "TileMenu.hpp"

class TileMenu;
class Tile;
class TileExtra;


enum SpecialInputCode : UInt32
{
	kInputCode_Backspace	= 0x80000000,
	kInputCode_ArrowLeft	= 0x80000001,
	kInputCode_ArrowRight	= 0x80000002,
	kInputCode_ArrowUp		= 0x80000003,
	kInputCode_ArrowDown	= 0x80000004,
	kInputCode_Home			= 0x80000005,
	kInputCode_End			= 0x80000006,
	kInputCode_Delete		= 0x80000007,
	kInputCode_Enter		= 0x80000008,
	kInputCode_PageUp		= 0x80000009,
	kInputCode_PageDown		= 0x8000000A
};

enum MenuSpecialKeyboardInputCode
{
	kMenu_Enter = -2,
	kMenu_UpArrow = 0x1,
	kMenu_DownArrow = 0x2,
	kMenu_RightArrow = 0x3,
	kMenu_LeftArrow = 0x4,
	kMenu_Space = 0x9,
	kMenu_Tab = 0xA,
	kMenu_ShiftEnter = 0xB,
	kMenu_AltEnter = 0xC,
	kMenu_ShiftLeft = 0xD,
	kMenu_ShiftRight = 0xE,
	kMenu_PageUp = 0xF,
	kMenu_PageDown = 0x10,
};

// 0x28
class Menu
{
public:

	enum EnumType : UInt32
	{
		kMenuType_Min = 0x3E9,
		kMenuType_Message = kMenuType_Min,
		kMenuType_Inventory,
		kMenuType_Stats,
		kMenuType_HUDMain,
		kMenuType_Loading = 0x3EF,
		kMenuType_Container,
		kMenuType_Dialog,
		kMenuType_SleepWait = 0x3F4,
		kMenuType_Start,
		kMenuType_LockPick,
		kMenuType_Quantity = 0x3F8,
		kMenuType_Map = 0x3FF,
		kMenuType_Book = 0x402,
		kMenuType_LevelUp,
		kMenuType_Repair = 0x40B,
		kMenuType_RaceSex,
		kMenuType_Credits = 0x417,
		kMenuType_CharGen,
		kMenuType_TextEdit = 0x41B,
		kMenuType_Barter = 0x41D,
		kMenuType_Surgery,
		kMenuType_Hacking,
		kMenuType_VATS,
		kMenuType_Computers,
		kMenuType_RepairServices,
		kMenuType_Tutorial,
		kMenuType_SpecialBook,
		kMenuType_ItemMod,
		kMenuType_LoveTester = 0x432,
		kMenuType_CompanionWheel,
		kMenuType_TraitSelect,
		kMenuType_Recipe,
		kMenuType_SlotMachine = 0x438,
		kMenuType_Blackjack,
		kMenuType_Roulette,
		kMenuType_Caravan,
		kMenuType_Trait = 0x43C,
		kMenuType_Max = kMenuType_Trait,
	};

	// check 1 at 0xA0B174, 0x70D529, 0x70D592 :: set at 0x712224
	// check 2 at 0x711FF1 :: set 2 at 0xA1D987 (when closes menu), 0xA1DA41
	// check 4 at 0xA1D9EC (when closing menu) :: set at 0x7036A4, 0x71204D
	// check 8 at 0x712194 :: set 8 at 0xA1DB8F (when opening menu), 0x720B39
	enum EnumVisibilityState : UInt32
	{
		kMenuStateIsReady	= 1 << 0,
		kMenuStateIsFadeOut	= 1 << 1,
		kMenuStateIsInit	= 1 << 2,
		kMenuStateIsFadeIn	= 1 << 3,
	};


	Menu() { ThisCall(0xA1C4A0, this); };
	virtual ~Menu() { ThisCall(0xA1C520, this); };

	virtual void	SetTile(UInt32 tileID, Tile* activeTile) {};
	virtual void	HandleClick(UInt32 tileID, Tile* activeTile) {};
	virtual void	HandleUnclick(UInt32 tileID, Tile* activeTile) {};	// buttonID = <id> trait defined in XML
	virtual void	HandleMouseover(UInt32 tileID, Tile* activeTile) {};	//called on mouseover, activeTile is moused-over Tile
	virtual void	HandleUnmouseover(UInt32 tileID, Tile* activeTile) {};
	virtual void	PostDragTileChange(UInt32 tileID, Tile* newTile, Tile* activeTile) {}; // unused by vanilla menus
	virtual void	PreDragTileChange(UInt32 tileID, Tile* oldTile, Tile* activeTile) {}; // unused by vanilla menus
	virtual void	HandleActiveMenuClickHeld(UInt32 tileID, Tile* activeTile) {}; // StartMenu, RaceSexMenu, VATSMenu, BookMenu
	virtual void	OnClickHeld(UInt32 tileID, Tile* activeTile) {}; // unused by vanilla menus
	virtual void	HandleMousewheel(UInt32 tileID, Tile* activeTile) {};
	virtual void	Update() {}; // Called every frame while the menu is active
	virtual bool	HandleKeyboardInput(UInt32 inputChar) { return false; };	//for keyboard shortcuts, return true if handled
	virtual UInt32	GetID() { return 0; };
	virtual bool	HandleSpecialKeyInput(MenuSpecialKeyboardInputCode code, Float32 keyState) { return false; };
	virtual bool	HandleControllerInput(int code, Tile* activeTile) { return false; }; 
	virtual void    OnUpdateUserTrait(int tileVal) {}; // unimplemented by any vanilla menus, called at 0xA1F28E - called when a tilevalue > 10000 is used (any field starting with an underscore like <_XXX></_XXX> is a user trait)
	virtual void	HandleControllerConnectOrDisconnect(bool isControllerConnected) {};

	// 0x14
	struct TemplateInstance {
		UInt32		unk00;
		Float32		flt04;
		BSStringT	kTileName;
		Tile*		pTile;
	};

	// 0x14
	struct TemplateData {
		const char*					pcTemplateName;
		TileExtra*					pkTileExtra;
		NiTList<TemplateInstance>	instances;
	};

	TileMenu*					pkRootTile;			// 0x4
	BSSimpleList<TemplateData*>	kMenuTemplates;		// 0x8
	UInt32						unk10;				// 0x10
	UInt32						unk14;				// 0x14
	UInt32						unk18;				// 0x18
	UInt8						byte1C;				// 0x1C
	UInt8						hasList08Data;		// 0x1D
	UInt8						byte1E;				// 0x1E
	UInt8						byte1F;				// 0x1F
	EnumType					eID;				// 0x20
	EnumVisibilityState			eVisibilityState;	// 0x24


	Menu*						HandleMenuInput(UInt32 tileID, Tile* clickedTile);
	__forceinline Tile*			AddTileFromTemplate(Tile* destTile, const char* templateName, UInt32 arg3 = 0)	{ return ThisCall<Tile*>(0xA1DDB0, this, destTile, templateName, arg3); }
	bool						GetTemplateExists(const std::string& templateName) const;

	__forceinline void			RegisterTile(Tile*	pkTile, bool noAppendToMenuStack) { ThisCall(0xA1DC70, this, tile, noAppendToMenuStack); };
	__forceinline void			Open(bool noFadeIn = false) { ThisCall(0xA1DC20, this, noFadeIn); }; // fade in
	__forceinline void			Close() { pkRootTile->Set(Tile::kValue_fadeout, 1); ThisCall(0xA1D910, this); } // fade out


	static bool					IsVisible(const UInt32 menuType);
	bool						IsVisible() const;
	static TileMenu*			GetTileMenu(const UInt32 menuType);
	TileMenu*					GetTileMenu() const;
	static TileMenu*			GetTileMenu(const std::string& componentPath);
	static Menu*				GetMenu(const UInt32 menuType);
	static Menu*				GetMenu(const std::string& componentPath);
	static Menu*				TempMenuByType(const UInt32 menuType);

	__forceinline static void	RefreshItemsList() { StdCall(0x704AF0); }
	static bool					RefreshItemsListForm(TESForm* form = nullptr);
	static void					RefreshItemsListQuick();

	static void  SetTileFade(Tile*	pkTile, bool startToFinish = true, Float32 duration = 0.25)
	{
		tile->SetGradual("_alpha", startToFinish ? 0 : 255.0, !startToFinish ? 0 : 255.0, duration);
	}
};
static_assert(sizeof(Menu) == 0x28);

enum MouseButtonNames
{
	kLeftClick = 0,
	kRightClick
};

enum MenuSoundCode
{
	kUIMenuOK = 0x1,
	kUIMenuCancel = 0x2,
	kUIMenuPrevNext = 0x3,
	kUIMenuFocus = 0x4,
	kUIPopUpQuestNew = 0x8,
	kUIPopUpMessageGeneral = 0xA,
	kUIPopUpMessageGeneral_ = 0x13,
	kUIMenuCancel_ = 0x14,
	kUILevelUp = 0x15,
	kUNIMPLEMENTED_ITMScrollOpen = 0x18,
	kUNIMPLEMENTED_ITMScrollClose = 0x19,
	kUNIMPLEMENTED_ITMBookOpen = 0x1A,
	kUNIMPLEMENTED_ITMBookClose = 0x1B,
	kUIMenuMode = 0x24,
};

struct EventCallbackScripts;

struct HotKeyWheel
{
	TileRect*	parent;
	TileRect*	hotkeys[8];
	UInt8		byte24;
	UInt8		gap25[3];
	UInt32		selectedHotkey;
	UInt32		selectedHotkeyTrait;
	UInt32		selectedTextTrait;

	void SetVisible(bool isVisible) { ThisCall(0x701760, this, isVisible); };
};



struct MenuEntry
{
	String entryText;
	String resultText;
	Script resScript;
	ConditionList conditions;
	BGSNote* displayNote;
	BGSTerminal* subMenu;
	UInt8 entryFlags;
	UInt8 pad75[3];
};
static_assert(sizeof(MenuEntry) == 0x78);



struct BGSSaveLoadFileEntry
{
	char* name;
	UInt8 isInitialised;
	UInt8 isCorrupt;
	UInt8 gap06;
	UInt8 gap07;
	UInt32 saveNumber;
	char* pcName;
	char* pcTitle;
	char* location;
	char* time;
	UInt32 level;
	UInt32 screenshotWidth;
	UInt32 screenshotHeight;
	UInt32 unk28;
	UInt8 unk2C[8];
	UInt32 index;
	UInt32 versionInfo;
	char versionInfoString[64];
};


class NiPointLight;





static BSSimpleArray<StartMenu::UserOption*>* g_settingsMenuOptions = (BSSimpleArray<StartMenu::UserOption*>*)0x11DAB50;
void MenuButton_DownloadsClick();

Tile::Value* StringToTilePath(const std::string& componentPath);